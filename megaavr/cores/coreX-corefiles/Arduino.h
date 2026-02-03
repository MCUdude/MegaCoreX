/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

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
*/

#ifndef Arduino_h
#define Arduino_h

#include "api/ArduinoAPI.h"

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#ifdef __cplusplus
extern "C"{
#endif

// Analog reference options
#define INTERNAL0V55    (VREF_ADC0REFSEL_0V55_gc >> VREF_ADC0REFSEL_gp)
#define INTERNAL1V1     (VREF_ADC0REFSEL_1V1_gc >> VREF_ADC0REFSEL_gp)
#define INTERNAL1V5     (VREF_ADC0REFSEL_1V5_gc >> VREF_ADC0REFSEL_gp)
#define INTERNAL2V5     (VREF_ADC0REFSEL_2V5_gc >> VREF_ADC0REFSEL_gp)
#define INTERNAL4V3     (VREF_ADC0REFSEL_4V34_gc >> VREF_ADC0REFSEL_gp)
#define INTERNAL4V34    INTERNAL4V3
#define DEFAULT         ADC_REFSEL_VDDREF_gc
#define INTERNAL        ADC_REFSEL_INTREF_gc
#define VDD             ADC_REFSEL_VDDREF_gc
#define EXTERNAL        ADC_REFSEL_VREFA_gc
#define ADC_TEMPERATURE ADC_MUXPOS_TEMPSENSE_gc
#define VCC_5V0         2
#define VCC_3V3         1
#define VCC_1V8         0

#define interrupts()    sei()
#define noInterrupts()  cli()

// avr-libc defines _NOP() since 1.6.2
#ifndef _NOP
  #define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

/* Allows performing a correction on the CPU value using the signature row
  values indicating oscillator error provided from the device manufacturer */
#define PERFORM_SIGROW_CORRECTION_F_CPU 0

/* Variable containing corrected F_CPU value, after checks for safe operating
  frequency vs supply voltage, oscillator fuse setting and MCLK divider.
  Also includes the correction from signature row values if above #define
  PERFORM_SIGROW_CORRECTION_F_CPU = 1 */
extern uint32_t F_CPU_CORRECTED;

uint16_t clockCyclesPerMicrosecondComp(uint32_t clk);
uint16_t clockCyclesPerMicrosecond();
unsigned long clockCyclesToMicroseconds(unsigned long cycles);
unsigned long microsecondsToClockCycles(unsigned long microseconds);

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.

extern const uint8_t digital_pin_to_port[];
extern const uint8_t digital_pin_to_bit_mask[];
extern const uint8_t digital_pin_to_bit_position[];
extern const uint8_t digital_pin_to_timer[];

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.
//
// These perform slightly better as macros compared to inline functions
//
#define NOT_A_PIN 255
#define NOT_A_PORT 255
#define NOT_AN_INTERRUPT 255

#define PA 0
#define PB 1
#define PC 2
#define PD 3
#define PE 4
#define PF 5
#define NUM_TOTAL_PORTS 6

#define NOT_ON_TIMER 0
#define TIMERA0 1
#define TIMERB0 2
#define TIMERB1 3
#define TIMERB2 4
#define TIMERB3 5

void setup_timers();

#define digitalPinToPort(pin) ( (pin < NUM_TOTAL_PINS) ? digital_pin_to_port[pin] : NOT_A_PIN )
#define digitalPinToBitPosition(pin) ( (pin < NUM_TOTAL_PINS) ? digital_pin_to_bit_position[pin] : NOT_A_PIN )
#define digitalPinToBitMask(pin) ( (pin < NUM_TOTAL_PINS) ? digital_pin_to_bit_mask[pin] : NOT_A_PIN )
#define digitalPinToTimer(pin) ( (pin < NUM_TOTAL_PINS) ? digital_pin_to_timer[pin] : NOT_ON_TIMER )
#define analogPinToBitPosition(pin) ( (digitalOrAnalogPinToDigital(pin) != NOT_A_PIN) ? digital_pin_to_bit_position[digitalOrAnalogPinToDigital(pin)] : NOT_A_PIN )
#define analogPinToBitMask(pin) ( (digitalOrAnalogPinToDigital(pin) != NOT_A_PIN) ? digital_pin_to_bit_mask[digitalOrAnalogPinToDigital(pin)] : NOT_A_PIN )

#define portToPortStruct(port) ( (port < NUM_TOTAL_PORTS) ? ((PORT_t *)&PORTA + port) : NULL)
#define digitalPinToPortStruct(pin) ( (pin < NUM_TOTAL_PINS) ? ((PORT_t *)&PORTA + digitalPinToPort(pin)) : NULL)
#define getPINnCTRLregister(port, bit_pos) ( ((port != NULL) && (bit_pos < NOT_A_PIN)) ? ((volatile uint8_t *)&(port->PIN0CTRL) + bit_pos) : NULL )
#define digitalPinToInterrupt(P) (P)

#define portOutputRegister(P) ( (volatile uint8_t *)( &portToPortStruct(P)->OUT ) )
#define portInputRegister(P) ( (volatile uint8_t *)( &portToPortStruct(P)->IN ) )
#define portModeRegister(P) ( (volatile uint8_t *)( &portToPortStruct(P)->DIR ) )

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include "UART.h"
#include "USBCore.h"
#include "CDC.h"
#include "MSC.h"
#ifdef UNO_WIFI_REV2_328MODE
#include <UNO_compat.h>
#endif
#if defined(HAVE_HWSERIAL0) && defined(HAVE_CDCSERIAL)
#error "Targets with both UART0 and CDC serial not supported"
#endif

enum timers_prescaler_t : uint8_t {
  TCA_DIV1    = 0x00,
  TCA_DIV2    = 0x02,
  TCA_DIV4    = 0x04,
  TCA_DIV8    = 0x06,
  TCA_DIV16   = 0x08,
  TCA_DIV64   = 0x0A,
  TCA_DIV256  = 0x0C,
  TCA_DIV1024 = 0x0E,
  TCB_DIV1    = 0x00,
  TCB_DIV2    = 0x20,
  TCB_CLKTCA  = 0x40,
};

void pwmWrite(pwm_timers_t pwmTimer, uint16_t value, timers_route_t timerRoute = ROUTE_UNTOUCHED);
void pwmPrescaler(pwm_timers_t pwmTimer, timers_prescaler_t prescaler);

// These are used as the second to N argument to pinConfigure(pin, ...)
// Directives are handled in the order they show up on this list, by pin function:
// PIN_DIR      Direction
// PIN_OUT      Output value
// PIN_ISC      Enable and interrupt mode. If interrupts are turned on w/out the ISR, it will trigger dirty reset.
// PIN_PULLUP   Pullups
// PIN_INLVL    Input levels (MVIO parts only - everything else is schmitt trigger only, except on I2C pins acting as I2C with SMBus levels enabled. )
// PIN_INVERT   Invert pin
//
// Systematically named constants can be made by combining those names with the postfixes here
// except for PIN_ISC which is not a non-binary option. Valid values are listed below.
// _SET, _CLR, and _TGL can be used as a postfix on all binary options.
// _TOGGLE and _TGL are interchangeable as well.
// Additional names are defined where they might be easier to remember.
typedef enum : uint16_t
{
 // OUTPUT
  PIN_DIR_SET        = 0x0001,
  PIN_DIRSET         = 0x0001,
  PIN_DIR_OUTPUT     = 0x0001,
  PIN_DIR_OUT        = 0x0001,
 // INPUT
  PIN_DIR_CLR        = 0x0002,
  PIN_DIRCLR         = 0x0002,
  PIN_DIR_INPUT      = 0x0002,
  PIN_DIR_IN         = 0x0002,
 // TOGGLE INPUT/OUTPUT
  PIN_DIR_TGL        = 0x0003,
  PIN_DIRTGL         = 0x0003,
  PIN_DIR_TOGGLE     = 0x0003,
 // HIGH
  PIN_OUT_SET        = 0x0004,
  PIN_OUTSET         = 0x0004,
  PIN_OUT_HIGH       = 0x0004,
 // LOW
  PIN_OUT_CLR        = 0x0008,
  PIN_OUTCLR         = 0x0008,
  PIN_OUT_LOW        = 0x0008,
// CHANGE/TOGGLE
  PIN_OUT_TGL        = 0x000C,
  PIN_OUTTGL         = 0x000C,
  PIN_OUT_TOGGLE     = 0x000C,
//Interrupt disabled but input buffer enabled
  PIN_ISC_ENABLE     = 0x0080,
  PIN_INPUT_ENABLE   = 0x0080,
 // Interrupt on change
  PIN_ISC_CHANGE     = 0x0090,
  PIN_INT_CHANGE     = 0x0090,
// Interrupt on rising edge
  PIN_ISC_RISE       = 0x00A0,
  PIN_INT_RISE       = 0x00A0,
// Interrupt on falling edge
  PIN_ISC_FALL       = 0x00B0,
  PIN_INT_FALL       = 0x00B0,
// Interrupt and input buffer disabled
  PIN_ISC_DISABLE    = 0x00C0,
  PIN_INPUT_DISABLE  = 0x00C0,
// Interrupt enabled with sense on low level
  PIN_ISC_LEVEL      = 0x00D0,
  PIN_INT_LEVEL      = 0x00D0,
// PULLUP ON
  PIN_PULLUP_ON      = 0x0100,
  PIN_PULLUP         = 0x0100,
  PIN_PULLUP_SET     = 0x0100,
// PULLUP OFF
  PIN_PULLUP_OFF     = 0x0200,
  PIN_PULLUP_CLR     = 0x0200,
  PIN_NOPULLUP       = 0x0200,
// PULLUP TOGGLE
  PIN_PULLUP_TGL     = 0x0300,
  PIN_PULLUP_TOGGLE  = 0x0300,
// PIN INVERT ON
  PIN_INVERT_ON      = 0x4000,
  PIN_INVERT_SET     = 0x4000,
// PIN INVERT OFF
  PIN_INVERT_OFF     = 0x8000,
  PIN_INVERT_CLR     = 0x8000,
// PIN_INVERT_TOGGLE
  PIN_INVERT_TGL     = 0xC000,
  PIN_INVERT_TOGGLE  = 0xC000,
} pin_configure_t;

/**
 * @brief Helper functions to catch the last argument in the pincfg recursion loop
 *
 * @param mode Mode parameter
 * @return pin_configure_t
 */

inline pin_configure_t pincfg(const pin_configure_t mode)
{
  return mode;
}

/**
 * @brief Helper functions to catch the nth in the pincfg recursion loop
 *
 * @param digital_pin Arduino pin
 * @param mode First "mode" parameter
 * @param modes Nth "mode" parameter
 * @return uint16_t pin configuration or'ed together
 */
template <typename... MODES>
uint16_t pincfg(const pin_configure_t mode, const MODES&... modes)
{
  return mode | pincfg(modes...);
}


/**
 * @brief Variadic template function for configuring a pin
 *
 * @param digital_pin Arduino pin number
 * @param mode First "mode" parameter
 * @param modes Nth "mode" parameter
 */
template <typename... MODES>
void pinConfigure(const uint8_t digital_pin, const pin_configure_t mode, const MODES&... modes)
{
  // Or-ing together the arguments using recursion
  uint16_t pin_config = pincfg(mode, modes...);

  uint8_t bit_mask = digitalPinToBitMask(digital_pin);
  if(bit_mask == NOT_A_PIN || !pin_config) // Return if digital pin is invalid or the other parameters or out to zero
    return;

  uint8_t bit_pos  = digitalPinToBitPosition(digital_pin);
  volatile uint8_t *portbase = (volatile uint8_t*) digitalPinToPortStruct(digital_pin);

  // Write to selected pin direction register
  uint8_t setting = pin_config & 0x03; // Mask out direction bits (DIR, DIRSET, DIRCLR, DIRTGL)
  if(setting)
    *(portbase + setting) = bit_mask;

  // Write to selected output register
  pin_config >>= 2;
  setting = pin_config & 0x03;
  if(setting)
    *(portbase + 4 + setting) = bit_mask;

  // Return if there is nothing more to configure
  if(!(pin_config & 0x3FFC))
    return;

  uint8_t oldSREG = SREG; // Store SREG
  cli(); // Disable interrupts

  // PINnCTRL register
  pin_config >>= 2;
  uint8_t pinncfg = *(portbase + 0x10 + bit_pos);
  // Input sense configuration (ISC)
  if(pin_config & 0x08)
    pinncfg = (pinncfg & 0xF8) | (pin_config & PORT_ISC_gm);
  // Pullup resistor
  uint8_t temp = pin_config & 0x30;
  if(temp)
  {
    if(temp == 0x30)
      pinncfg ^= PORT_PULLUPEN_bm;    // Toggle pullup
    else if(temp == 0x20)
      pinncfg &= ~(PORT_PULLUPEN_bm); // Clear pullup
    else
      pinncfg |= PORT_PULLUPEN_bm;    // Set pullup
  }
  // Invert pin
  pin_config >>= 8;
  temp = pin_config & 0x0C;
  if(temp)
  {
    if(temp == 0x0C)
      pinncfg ^= PORT_INVEN_bm;    // Toggle invert
    else if(temp == 0x08)
      pinncfg &= ~(PORT_INVEN_bm); // Clear
    else
      pinncfg |= PORT_INVEN_bm;    // Set
  }
  // Write to PINnCTRL register
  *(portbase + 0x10 + bit_pos) = pinncfg;

  // Restore SREG
  SREG = oldSREG;
}

#endif

#include "pins_arduino.h"
#endif
