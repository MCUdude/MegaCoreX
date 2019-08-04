/*
  UART1.cpp - Hardware serial library for Wiring
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

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#include "Arduino.h"
#include "UART.h"
#include "UART_private.h"

// Each UartClass is defined in its own file, sine the linker pulls
// in the entire file when any element inside is used. --gc-sections can
// additionally cause unused symbols to be dropped, but ISRs have the
// "used" attribute so are never dropped and they keep the
// UartClass instance in as well. Putting each instance in its own
// file prevents the linker from pulling in any unused instances in the
// first place.

#if defined(HAVE_HWSERIAL1)

#if defined(HWSERIAL1_RXC_VECTOR)
ISR(HWSERIAL1_RXC_VECTOR)
{
  Serial1._rx_complete_irq();
}
#else
#error "Don't know what the Data Received interrupt vector is called for Serial1"
#endif

#if defined(HWSERIAL1_DRE_VECTOR)
ISR(HWSERIAL1_DRE_VECTOR)
{
  Serial1._tx_data_empty_irq();
}
#else
#error "Don't know what the Data Register Empty interrupt vector is called for Serial1"
#endif

#if defined(HWSERIAL1)
  UartClass Serial1(HWSERIAL1, PIN_WIRE_HWSERIAL1_RX, PIN_WIRE_HWSERIAL1_TX, PIN_WIRE_HWSERIAL1_RX_PINSWAP_1, PIN_WIRE_HWSERIAL1_TX_PINSWAP_1, HWSERIAL1_MUX, HWSERIAL1_MUX_PINSWAP_1);
#endif

// Function that can be weakly referenced by serialEventRun to prevent
// pulling in this file if it's not otherwise used.
bool Serial1_available() {
  return Serial1.available();
}

#endif // HAVE_HWSERIAL1
