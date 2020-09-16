/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>
#include "timers.h"

#define NANO_EVERY_PINOUT
#define NONA4809_PINOUT
#define __AVR_ATmegax09__

// Arduino pin macros
#define PIN_PC5 0
#define PIN_PC4 1
#define PIN_PA0 2
#define PIN_PF5 3
#define PIN_PC6 4
#define PIN_PB2 5
#define PIN_PF4 6
#define PIN_PA1 7
#define PIN_PE3 8
#define PIN_PB0 9
#define PIN_PB1 10
#define PIN_PE0 11
#define PIN_PE1 12
#define PIN_PE2 13
#define PIN_PD3 14
#define PIN_PD2 15
#define PIN_PD1 16
#define PIN_PD0 17
#define PIN_PF2 18
#define PIN_PF3 19
#define PIN_PD4 20
#define PIN_PD5 21
#define PIN_PA2 22
#define PIN_PA3 23
#define PIN_PB5 24
#define PIN_PB4 25
#define PIN_PC3 26
#define PIN_PA5 27
#define PIN_PA4 28
#define PIN_PD6 29
#define PIN_PA6 30
#define PIN_PA7 31
#define PIN_PB3 32
#define PIN_PC7 33
#define PIN_PC0 34
#define PIN_PC1 35
#define PIN_PC2 36
#define PIN_PF0 37
#define PIN_PF1 38
#define PIN_PD7 39
#define PIN_PF6 40

#define PINS_COUNT                     41
#define NUM_DIGITAL_PINS               PINS_COUNT
#define NUM_ANALOG_INPUTS              16
#define NUM_RESERVED_PINS              0
#define NUM_INTERNALLY_USED_PINS       0
#define NUM_I2C_PINS                   2  // (SDA / SCL)
#define NUM_SPI_PINS                   3  // (MISO / MOSI / SCK)
#define NUM_TOTAL_FREE_PINS            NUM_DIGITAL_PINS
#define NUM_TOTAL_PINS                 (NUM_DIGITAL_PINS + NUM_RESERVED_PINS + NUM_INTERNALLY_USED_PINS + NUM_I2C_PINS + NUM_SPI_PINS)
#define ANALOG_INPUT_OFFSET            14
#define LED_BUILTIN                    13
#define EXTERNAL_NUM_INTERRUPTS        47
#define digitalPinToAnalogInput(p)     (((p) == A0) ? (3) : ((p) == A1) ? (2) : ((p) == A2) ? (1): ((p) == A3) ? (0): ((p) == A4) ? (12): ((p) == A5) ? (13): ((p) == A6) ? (4): ((p) == A7) ? (5): ((p) == A8) ? (7): ((p) == A9) ? (10) : ((p) == A10) ? (9): ((p) == A11) ? (8): ((p) == A12) ? (11): ((p) == A13) ? (14): ((p) == A14) ? (15) :((p) == A15) ? (29) : NOT_A_PIN)
#define digitalOrAnalogPinToDigital(p) (((p) <= 40) ? (p) : NOT_A_PIN)

// Timer to use for millis/micros
#define MILLIS_USE_TIMERB3

// PWM pins
#define digitalPinHasPWM(p)            ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 27)

// Timer pin mapping
#define TCA0_PINS PORTMUX_TCA0_PORTB_gc
#define TCB0_PINS PORTMUX_TCB0_bm
#define TCB1_PINS PORTMUX_TCB1_bm
#define TCB2_PINS 0x00
#define TCB3_PINS 0x00

// SPI 0
// Pinswap enabled by default and no alternative available
#define SPI_INTERFACES_COUNT 1
#define SPI_MUX              PORTMUX_SPI0_ALT2_gc
#define PIN_SPI_MISO         PIN_PE1
#define PIN_SPI_SCK          PIN_PE2
#define PIN_SPI_MOSI         PIN_PE0
#define PIN_SPI_SS           PIN_PE3
static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

// TWI 0
// No pinswap enabled by default, and no alternative available
#define TWI_MUX              PORTMUX_TWI0_DEFAULT_gc
#define PIN_WIRE_SDA         PIN_PA2
#define PIN_WIRE_SCL         PIN_PA3
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// Nano Every debug USART (Serial)
// USART3 on mega4809
// Maps to alternative pins by default
// Mapped to HWSERIAL0 in Serial library
#define HWSERIAL0                       &USART3
#define HWSERIAL0_DRE_VECTOR            USART3_DRE_vect
#define HWSERIAL0_DRE_VECTOR_NUM        USART3_DRE_vect_num
#define HWSERIAL0_RXC_VECTOR            USART3_RXC_vect
#define HWSERIAL0_MUX                   PORTMUX_USART3_ALT1_gc
#define HWSERIAL0_MUX_PINSWAP_1         PORTMUX_USART3_DEFAULT_gc
#define PIN_HWSERIAL0_TX                PIN_PB4
#define PIN_HWSERIAL0_RX                PIN_PB5
#define PIN_HWSERIAL0_TX_PINSWAP_1      PIN_PB0
#define PIN_HWSERIAL0_RX_PINSWAP_1      PIN_PB1
#define PIN_HWSERIAL0_XCK_PINSWAP_1     PIN_PB2
#define PIN_HWSERIAL0_XDIR_PINSWAP_1    PIN_PB3

// Nano every USART (Serial1)
// USART1 on mega4809
// Maps to alternative pins by default
// Mapped to HWSERIAL1 in Serial library
#define HWSERIAL1                       &USART1
#define HWSERIAL1_DRE_VECTOR            USART1_DRE_vect
#define HWSERIAL1_DRE_VECTOR_NUM        USART1_DRE_vect_num
#define HWSERIAL1_RXC_VECTOR            USART1_RXC_vect
#define HWSERIAL1_MUX                   PORTMUX_USART1_ALT1_gc
#define HWSERIAL1_MUX_PINSWAP_1         PORTMUX_USART1_DEFAULT_gc
#define PIN_HWSERIAL1_TX                PIN_PC4
#define PIN_HWSERIAL1_RX                PIN_PC5
#define PIN_HWSERIAL1_XCK               PIN_PC6
#define PIN_HWSERIAL1_XDIR              PIN_PC7
#define PIN_HWSERIAL1_TX_PINSWAP_1      PIN_PC0
#define PIN_HWSERIAL1_RX_PINSWAP_1      PIN_PC1
#define PIN_HWSERIAL1_XCK_PINSWAP_1     PIN_PC2
#define PIN_HWSERIAL1_XDIR_PINSWAP_1    PIN_PC3

// Nano Every USART (Serial2)
// USART0 on mega4809
// Maps to default pins by default
// Mapped to HWSERIAL2 in Serial library
#define HWSERIAL2                       &USART0
#define HWSERIAL2_DRE_VECTOR            USART0_DRE_vect
#define HWSERIAL2_DRE_VECTOR_NUM        USART0_DRE_vect_num
#define HWSERIAL2_RXC_VECTOR            USART0_RXC_vect
#define HWSERIAL2_MUX                   PORTMUX_USART0_DEFAULT_gc
#define HWSERIAL2_MUX_PINSWAP_1         PORTMUX_USART0_ALT1_gc
#define PIN_HWSERIAL2_TX                PIN_PA0
#define PIN_HWSERIAL2_RX                PIN_PA1
#define PIN_HWSERIAL2_XCK               PIN_PA2
#define PIN_HWSERIAL2_XDIR              PIN_PA3
#define PIN_HWSERIAL2_TX_PINSWAP_1      PIN_PA4
#define PIN_HWSERIAL2_RX_PINSWAP_1      PIN_PA5
#define PIN_HWSERIAL2_XCK_PINSWAP_1     PIN_PA6
#define PIN_HWSERIAL2_XDIR_PINSWAP_1    PIN_PA7

// Nano Every USART (Serial3)
// USART2 on mega4809
// Maps to alternative pins by default
// Mapped to HWSERIAL3 in Serial library
#define HWSERIAL3                       &USART2
#define HWSERIAL3_DRE_VECTOR            USART2_DRE_vect
#define HWSERIAL3_DRE_VECTOR_NUM        USART2_DRE_vect_num
#define HWSERIAL3_RXC_VECTOR            USART2_RXC_vect
#define HWSERIAL3_MUX                   PORTMUX_USART2_ALT1_gc
#define HWSERIAL3_MUX_PINSWAP_1         PORTMUX_USART2_DEFAULT_gc
#define PIN_HWSERIAL3_TX                PIN_PF4
#define PIN_HWSERIAL3_RX                PIN_PF5
#define PIN_HWSERIAL3_XCK               PIN_PF6
#define PIN_HWSERIAL3_TX_PINSWAP_1      PIN_PF0
#define PIN_HWSERIAL3_RX_PINSWAP_1      PIN_PF1
#define PIN_HWSERIAL3_XCK_PINSWAP_1     PIN_PF2
#define PIN_HWSERIAL3_XDIR_PINSWAP_1    PIN_PF3

// Analog pins
#define PIN_A0   PIN_PD3 // AIN3
#define PIN_A1   PIN_PD2 // AIN2
#define PIN_A2   PIN_PD1 // AIN1
#define PIN_A3   PIN_PD0 // AIN0
#define PIN_A4   PIN_PF2 // AIN12
#define PIN_A5   PIN_PF3 // AIN13
#define PIN_A6   PIN_PD4 // AIN4
#define PIN_A7   PIN_PD5 // AIN5
#define PIN_A8   PIN_PD7 // AIN7
#define PIN_A9   PIN_PE2 // AIN10
#define PIN_A10  PIN_PE1 // AIN9
#define PIN_A11  PIN_PE0 // AIN8
#define PIN_A12  PIN_PE3 // AIN11
#define PIN_A13  PIN_PF4 // AIN14
#define PIN_A14  PIN_PF5 // AIN15
#define PIN_A15  PIN_PD6 // AIN6
static const uint8_t A0  = PIN_A0;
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;
static const uint8_t A4  = PIN_A4;
static const uint8_t A5  = PIN_A5;
static const uint8_t A6  = PIN_A6;
static const uint8_t A7  = PIN_A7;
static const uint8_t A8  = PIN_A8;
static const uint8_t A9  = PIN_A9;
static const uint8_t A10 = PIN_A10;
static const uint8_t A11 = PIN_A11;
static const uint8_t A12 = PIN_A12;
static const uint8_t A13 = PIN_A13;
static const uint8_t A14 = PIN_A14;
static const uint8_t A15 = PIN_A15;

#ifdef ARDUINO_MAIN

const uint8_t digital_pin_to_port[] = {
  PC, // 0 PC5/USART1_Rx_alt
  PC, // 1 PC4/USART1_Tx_alt
  PA, // 2 PA0/USART0_Tx
  PF, // 3 PF5/USART2_Rx_alt/AIN6
  PC, // 4 PC6
  PB, // 5 PB2
  PF, // 6 PF4/USART2_Tx_alt/AIN14
  PA, // 7 PA1/USART0_Rx
  PE, // 8 PE3/AIN11
  PB, // 9 PB0/USART3_Tx
  PB, // 10 PB1/USART3_Rx
  PE, // 11 PE0/AIN8
  PE, // 12 PE1/AIN9
  PE, // 13 PE2/AIN10/LED_BUILTIN
  PD, // 14 PD3/AIN3
  PD, // 15 PD2/AIN2
  PD, // 16 PD1/AIN1
  PD, // 17 PD0/AIN0
  PF, // 18 PF2/AIN12
  PF, // 19 PF3/AIN13
  PD, // 20 PD4/AIN4
  PD, // 21 PD5/AIN5
  PA, // 22 PA2/TWI_SDA
  PA, // 23 PA3/TWI_SCL
  PB, // 24 PB5/USART3_Rx_alt
  PB, // 25 PB4/USART3_Tx_alt
  PC, // 26 PC3
  PA, // 27 PA5/USART0_Rx_alt
  PA, // 28 PA4/USART0_Tx_alt
  PD, // 29 PD6/AIN6
  PA, // 30 PA6
  PA, // 31 PA7
  PB, // 32 PB3
  PC, // 33 PC7
  PC, // 34 PC0/USART1_Tx
  PC, // 35 PC1/USART1_Rx
  PC, // 36 PC2
  PF, // 37 PF0/USART2_Tx
  PF, // 38 PF1/USART2_Rx
  PD, // 39 PD7/VREF/AIN7
  PF  // 40 PF6/RESET
};

/* Use this for accessing PINnCTRL register */
const uint8_t digital_pin_to_bit_position[] = {
  PIN5_bp,  // 0  PC5/USART1_Rx_alt
  PIN4_bp,  // 1  PC4/USART1_Tx_alt
  PIN0_bp,  // 2  PA0/USART0_Tx
  PIN5_bp,  // 3  PF5/USART2_Rx_alt/AIN15
  PIN6_bp,  // 4  PC6
  PIN2_bp,  // 5  PB2
  PIN4_bp,  // 6  PF4/USART2_Tx_alt/AIN15
  PIN1_bp,  // 7  PA1/USART0_Rx
  PIN3_bp,  // 8  PE3/AIN11
  PIN0_bp,  // 9  PB0/USART3_Tx
  PIN1_bp,  // 10 PB1/USART3_Rx
  PIN0_bp,  // 11 PE0/AIN8
  PIN1_bp,  // 12 PE1/AIN9
  PIN2_bp,  // 13 PE2/AIN10/LED_BUILTIN
  PIN3_bp,  // 14 PD3/AIN3
  PIN2_bp,  // 15 PD2/AIN2
  PIN1_bp,  // 16 PD1/AIN1
  PIN0_bp,  // 17 PD0/AIN0
  PIN2_bp,  // 18 PF2/AIN12
  PIN3_bp,  // 19 PF3/AIN13
  PIN4_bp,  // 20 PD4/AIN4
  PIN5_bp,  // 21 PD5/AIN5
  PIN2_bp,  // 22 PA2/TWI_SDA
  PIN3_bp,  // 23 PA3/TWI_SCL
  PIN5_bp,  // 24 PB5/USART3_Rx_alt
  PIN4_bp,  // 25 PB4/USART3_Tx_alt
  PIN3_bp,  // 26 PC3
  PIN5_bp,  // 27 PA5/USART0_Rx_alt
  PIN4_bp,  // 28 PA4/USART0_Tx_alt
  PIN6_bp,  // 29 PD6/AIN6
  PIN6_bp,  // 30 PA6
  PIN7_bp,  // 31 PA7
  PIN3_bp,  // 32 PB3
  PIN7_bp,  // 33 PC7
  PIN0_bp,  // 34 PC0/USART1_Tx
  PIN1_bp,  // 35 PC1/USART1_Rx
  PIN2_bp,  // 36 PC2
  PIN0_bp,  // 37 PF0/USART2_Tx
  PIN1_bp,  // 38 PF1/USART2_Rx
  PIN7_bp,  // 39 PD7/VREF/AIN7
  PIN6_bp,  // 40 PF6/RESET
};

/* Use this for accessing PINnCTRL register */
const uint8_t digital_pin_to_bit_mask[] = {
  PIN5_bm,  // 0  PC5/USART1_Rx_alt
  PIN4_bm,  // 1  PC4/USART1_Tx_alt
  PIN0_bm,  // 2  PA0/USART0_Tx
  PIN5_bm,  // 3  PF5/USART2_Rx_alt/AIN15
  PIN6_bm,  // 4  PC6
  PIN2_bm,  // 5  PB2
  PIN4_bm,  // 6  PF4/USART2_Tx_alt/AIN14
  PIN1_bm,  // 7  PA1/USART0_Rx
  PIN3_bm,  // 8  PE3/AIN11
  PIN0_bm,  // 9  PB0/USART3_Tx
  PIN1_bm,  // 10 PB1/USART3_Rx
  PIN0_bm,  // 11 PE0/AIN8
  PIN1_bm,  // 12 PE1/AIN9
  PIN2_bm,  // 13 PE2/AIN10/LED_BUILTIN
  PIN3_bm,  // 14 PD3/AIN3
  PIN2_bm,  // 15 PD2/AIN2
  PIN1_bm,  // 16 PD1/AIN1
  PIN0_bm,  // 17 PD0/AIN0
  PIN2_bm,  // 18 PF2/AIN12
  PIN3_bm,  // 19 PF3/AIN13
  PIN4_bm,  // 20 PD4/AIN4
  PIN5_bm,  // 21 PD5/AIN5
  PIN2_bm,  // 22 PA2/TWI_SDA
  PIN3_bm,  // 23 PA3/TWI_SCL
  PIN5_bm,  // 24 PB5/USART3_Rx_alt
  PIN4_bm,  // 25 PB4/USART3_Tx_alt
  PIN3_bm,  // 26 PC3
  PIN5_bm,  // 27 PA5/USART0_Rx_alt
  PIN4_bm,  // 28 PA4/USART0_Tx_alt
  PIN6_bm,  // 29 PD6/AIN6
  PIN6_bm,  // 30 PA6
  PIN7_bm,  // 31 PA7
  PIN3_bm,  // 32 PB3
  PIN7_bm,  // 33 PC7
  PIN0_bm,  // 34 PC0/USART1_Tx
  PIN1_bm,  // 35 PC1/USART1_Rx
  PIN2_bm,  // 36 PC2
  PIN0_bm,  // 37 PF0/USART2_Tx
  PIN1_bm,  // 38 PF1/USART2_Rx
  PIN7_bm,  // 39 PD7/VREF/AIN7
  PIN6_bm,  // 40 PF6/RESET
};

const uint8_t digital_pin_to_timer[] = {
  NOT_ON_TIMER,  // 0  PC5/USART1_Rx_alt
  NOT_ON_TIMER,  // 1  PC4/USART1_Tx_alt
  NOT_ON_TIMER,  // 2  PA0/USART0_Tx
  TIMERB1,       // 3  PF5/USART2_Rx_alt/AIN15
  NOT_ON_TIMER,  // 4  PC6
  TIMERA0,       // 5  PB2
  TIMERB0,       // 6  PF4/USART2_Tx_alt/AIN14
  NOT_ON_TIMER,  // 7  PA1/USART0_Rx
  NOT_ON_TIMER,  // 8  PE3/AIN11
  TIMERA0,       // 9  PB0/USART3_Tx
  TIMERA0,       // 10 PB1/USART3_Rx
  NOT_ON_TIMER,  // 11 PE0/AIN8
  NOT_ON_TIMER,  // 12 PE1/AIN9
  NOT_ON_TIMER,  // 13 PE2/AIN10/LED_BUILTIN
  NOT_ON_TIMER,  // 14 PD3/AIN3
  NOT_ON_TIMER,  // 15 PD2/AIN2
  NOT_ON_TIMER,  // 16 PD1/AIN1
  NOT_ON_TIMER,  // 17 PD0/AIN0
  NOT_ON_TIMER,  // 18 PF2/AIN12
  NOT_ON_TIMER,  // 19 PF3/AIN13
  NOT_ON_TIMER,  // 20 PD4/AIN4
  NOT_ON_TIMER,  // 21 PD5/AIN5
  NOT_ON_TIMER,  // 22 PA2/TWI_SDA
  NOT_ON_TIMER,  // 23 PA3/TWI_SCL
  NOT_ON_TIMER,  // 24 PB5/USART3_Rx
  NOT_ON_TIMER,  // 25 PB4/USART3_Tx
  NOT_ON_TIMER,  // 26 PC3
  NOT_ON_TIMER,  // 27 PA5/USART0_Rx_alt
  NOT_ON_TIMER,  // 28 PA4/USART0_Tx_alt
  NOT_ON_TIMER,  // 29 PD6/AIN6
  NOT_ON_TIMER,  // 30 PA6
  NOT_ON_TIMER,  // 31 PA7
  NOT_ON_TIMER,  // 32 PB3
  NOT_ON_TIMER,  // 33 PC7
  NOT_ON_TIMER,  // 34 PC0/USART1_Tx
  NOT_ON_TIMER,  // 35 PC1/USART1_Rx
  NOT_ON_TIMER,  // 36 PC2
  NOT_ON_TIMER,  // 37 PF0/USART2_Tx
  NOT_ON_TIMER,  // 38 PF1/USART2_Rx
  NOT_ON_TIMER,  // 39 PD7/VREF/AIN7
  NOT_ON_TIMER,  // 40 PF6/RESET
};

//const uint8_t analog_pin_to_channel[] = { 3, 2, 1, 0, 12, 13, 4, 5 , 7, 10, 9, 8, 11, 14, 15};

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR       Serial
#define SERIAL_PORT_HARDWARE      Serial1
#define SERIAL_PORT_USBVIRTUAL    Serial

void initVariant() __attribute__((weak));
void initVariant() { }

#endif
