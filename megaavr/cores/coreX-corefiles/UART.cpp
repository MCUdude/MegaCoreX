/*
  UART.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Created: 09.11.2017 07:29:09
  Author: M44307
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <util/atomic.h>
#include <avr/io.h>
#include "Arduino.h"

#include "UART.h"
#include "UART_private.h"

// this next line disables the entire UART.cpp,
// this is so I can support Attiny series and any other chip without a uart
#if defined(HAVE_HWSERIAL0) || defined(HAVE_HWSERIAL1) || defined(HAVE_HWSERIAL2) || defined(HAVE_HWSERIAL3)

// SerialEvent functions are weak, so when the user doesn't define them,
// the linker just sets their address to 0 (which is checked below).
// The Serialx_available is just a wrapper around Serialx.available(),
// but we can refer to it weakly so we don't pull in the entire
// UART instance if the user doesn't also refer to it.
#if defined(HAVE_HWSERIAL0)
void serialEvent() __attribute__((weak));
bool Serial0_available() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL1)
void serialEvent1() __attribute__((weak));
bool Serial1_available() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL2)
void serialEvent2() __attribute__((weak));
bool Serial2_available() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL3)
void serialEvent3() __attribute__((weak));
bool Serial3_available() __attribute__((weak));
#endif

void serialEventRun(void)
{
#if defined(HAVE_HWSERIAL0)
    if (Serial0_available && serialEvent && Serial0_available()) serialEvent();
#endif
#if defined(HAVE_HWSERIAL1)
    if (Serial1_available && serialEvent1 && Serial1_available()) serialEvent1();
#endif
#if defined(HAVE_HWSERIAL2)
    if (Serial2_available && serialEvent2 && Serial2_available()) serialEvent2();
#endif
#if defined(HAVE_HWSERIAL3)
    if (Serial3_available && serialEvent3 && Serial3_available()) serialEvent3();
#endif
}

// macro to guard critical sections when needed for large RX and TX buffer sizes
#if (SERIAL_RX_BUFFER_SIZE > 256)
#define RX_BUFFER_ATOMIC ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#else
#define RX_BUFFER_ATOMIC
#endif
#if (SERIAL_TX_BUFFER_SIZE > 256)
#define TX_BUFFER_ATOMIC ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#else
#define TX_BUFFER_ATOMIC
#endif

// Actual interrupt handlers //////////////////////////////////////////////////////////////

void UartClass::_tx_data_empty_irq(void)
{
    // There must be more data in the output
    // buffer. Send the next byte
    unsigned char c = _tx_buffer[_tx_buffer_tail];
    _tx_buffer_tail = (_tx_buffer_tail + 1) % SERIAL_TX_BUFFER_SIZE;

    // clear the TXCIF flag -- "can be cleared by writing a one to its bit
    // location". This makes sure flush() won't return until the bytes
    // actually got written
    (*_hwserial_module).STATUS = USART_TXCIF_bm;

    (*_hwserial_module).TXDATAL = c;

    if (_tx_buffer_head == _tx_buffer_tail) {
        // Buffer empty, so disable "data register empty" interrupt
        (*_hwserial_module).CTRLA &= (~USART_DREIE_bm);
    }
}

// To invoke data empty "interrupt" via a call, use this method
void UartClass::_tx_data_empty_soft(void) {
    if ( !(SREG & CPU_I_bm) ) {
       // Interrupts are disabled globally, so the code here is an ATOMIC_BLOCK
       // We'll have to poll the "data register empty" flag ourselves.
       // Call the handler only if data register is empty and we know the buffer is non-empty

       if (((*_hwserial_module).CTRLA & USART_DREIE_bm) && ((*_hwserial_module).STATUS & USART_DREIF_bm)) {
	  _tx_data_empty_irq();
       }
    }
    // In case interrupts are enabled, the interrupt routine will be invoked by itself
}

// Public Methods //////////////////////////////////////////////////////////////

// Invoke this function before 'begin' to define the pins used
bool UartClass::pins(uint8_t tx, uint8_t rx)
{
    for (_pin_set = 0; _pin_set < SERIAL_PIN_SETS; ++_pin_set) {
	if (tx == _hw_set[_pin_set].tx_pin && rx == _hw_set[_pin_set].rx_pin) {
	    // We are good, this set of pins is supported
	    return true;
	}
    }
    _pin_set = 0; // Default to standard
    return false;
}

void UartClass::begin(unsigned long baud, uint16_t config)
{
    // Make sure no transmissions are ongoing and USART is disabled in case begin() is called by accident
    // without first calling end()
    if(_written) {
        this->end();
    }

    struct UartPinSet *set = &_hw_set[_pin_set];
    int32_t baud_setting = 0;

    //Make sure global interrupts are disabled during initialization
    uint8_t oldSREG = SREG;
    cli();

    baud_setting = (((8 * F_CPU_CORRECTED) / baud) + 1) / 2;
    // Disable CLK2X
    (*_hwserial_module).CTRLB &= (~USART_RXMODE_CLK2X_gc);
    (*_hwserial_module).CTRLB |= USART_RXMODE_NORMAL_gc;

    _written = false;
    _tx_buffer_head = _tx_buffer_tail; // just in case someone invoked write() before begin()

    // Let PORTMUX point to alternative UART pins as requested
    PORTMUX.USARTROUTEA = set->mux |
			  (PORTMUX.USARTROUTEA & ~_hw_set[1].mux);

    // Set pin state for swapped UART pins
    pinMode(set->rx_pin, INPUT_PULLUP);
    digitalWrite(set->tx_pin, HIGH);
    pinMode(set->tx_pin, OUTPUT);

    int8_t sigrow_val = SIGROW.OSC16ERR5V;
    baud_setting *= (1024 + sigrow_val);
    baud_setting /= (1024 - abs(sigrow_val));

    // assign the baud_setting, a.k.a. BAUD (USART Baud Rate Register)
    (*_hwserial_module).BAUD = (int16_t) baud_setting;

    // Set USART mode of operation
    (*_hwserial_module).CTRLC = config;

    // Enable transmitter and receiver
    (*_hwserial_module).CTRLB |= (USART_RXEN_bm | USART_TXEN_bm);

    (*_hwserial_module).CTRLA |= USART_RXCIE_bm;

    // Restore SREG content
    SREG = oldSREG;
}

void UartClass::end()
{
    // wait for transmission of outgoing data
    flush();

    // Disable receiver and transmitter as well as the RX complete and
    // data register empty interrupts.
    (*_hwserial_module).CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
    (*_hwserial_module).CTRLA &= ~(USART_RXCIE_bm | USART_DREIE_bm);

    // clear any received data (no need for atomic since interrupts are now disabled)
    _rx_buffer_head = _rx_buffer_tail;

    // Note: Does not change output pins
    _written = false;
}

int UartClass::available(void)
{
    int n;
    RX_BUFFER_ATOMIC {
	n = ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
    }
    return n;
}

int UartClass::peek(void)
{
    int c;

    RX_BUFFER_ATOMIC {
	if (_rx_buffer_head == _rx_buffer_tail) {
	    c = -1;
	} else {
	    c = _rx_buffer[_rx_buffer_tail];
	}
    }
    return c;
}

int UartClass::read(void)
{
    int c;

    RX_BUFFER_ATOMIC {
	// if the head isn't ahead of the tail, we don't have any characters
	if (_rx_buffer_head == _rx_buffer_tail) {
	    c = -1;
	} else {
	    c = _rx_buffer[_rx_buffer_tail];
	    _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
	}
    }
    return c;
}

int UartClass::availableForWrite(void)
{
    tx_buffer_index_t head;
    tx_buffer_index_t tail;

    TX_BUFFER_ATOMIC {
	head = _tx_buffer_tail;
	tail = _tx_buffer_tail;
    }
    if (head >= tail) return SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
    return tail - head - 1;
}

void UartClass::flush()
{
    // If we have never written a byte, no need to flush. This special
    // case is needed since there is no way to force the TXCIF (transmit
    // complete) bit to 1 during initialization
    if (!_written) {
        return;
    }

    // Spin until the data-register-empty-interrupt is disabled and TX complete interrupt flag is raised
    while ( ((*_hwserial_module).CTRLA & USART_DREIE_bm) || (!((*_hwserial_module).STATUS & USART_TXCIF_bm)) ) {

	// If interrupts are globally disabled or the and DR empty interrupt is disabled,
	// poll the "data register empty" interrupt flag to prevent deadlock
	_tx_data_empty_soft();
    }
    // If we get here, nothing is queued anymore (DREIE is disabled) and
    // the hardware finished transmission (TXCIF is set).
}

size_t UartClass::write(uint8_t c)
{
    _written = true;

    // If the buffer and the data register is empty, just write the byte
    // to the data register and be done. This shortcut helps
    // significantly improve the effective data rate at high (>
    // 500kbit/s) bit rates, where interrupt overhead becomes a slowdown.
    // Note also that USART_DREIE_bm always will be clear if the buffer is
    // empty.
    if ( !((*_hwserial_module).CTRLA & USART_DREIE_bm) && ((*_hwserial_module).STATUS & USART_DREIF_bm) ) {
	(*_hwserial_module).TXDATAL = c;
        (*_hwserial_module).STATUS = USART_TXCIF_bm;

        return 1;
    }

    // Note that while head for tx is not changed by the tx interrupt, head needs to be atomic
    // if someone happens to use serial write in another interrupt, so prepare for that
    for (;;) {
	TX_BUFFER_ATOMIC {
	    tx_buffer_index_t nexthead = (_tx_buffer_head + 1) % SERIAL_TX_BUFFER_SIZE;
	    if (nexthead != _tx_buffer_tail) {
		// There is room in the buffer
		_tx_buffer[_tx_buffer_head] = c;
		_tx_buffer_head = nexthead;
		// Enable data "register empty interrupt" if it was not already
		(*_hwserial_module).CTRLA |= USART_DREIE_bm;
		return 1;
	    }
	}

	// The output buffer is full, so there's nothing for it other than to
	// wait for the interrupt handler to empty it a bit (or emulate interrupts)
	// Note that USART_DREIE_bm must be set at this time
	_tx_data_empty_soft();
    }
}

#endif // whole file
