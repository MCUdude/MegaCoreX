/*
  wiring_analog.c - analog input and output
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

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

  Modified 28 September 2010 by Mark Sproul
*/

#include "Arduino.h"
#include "pins_arduino.h"
#include "wiring_private.h"

void analogReference(uint8_t mode)
{
  switch (mode)
  {
    case EXTERNAL:
    case VDD:
      ADC0.CTRLC = (ADC0.CTRLC & ~(ADC_REFSEL_gm)) | mode | ADC_SAMPCAP_bm; // Per datasheet, recommended SAMPCAP=1 at ref > 1v - we don't *KNOW* the external reference will be >1v, but it's probably more likely...
      // VREF.CTRLA does not need to be reconfigured, as the voltage references only supply their specified voltage when requested to do so by the ADC.
      break;
    case INTERNAL0V55:
      VREF.CTRLA = VREF.CTRLA & ~(VREF_ADC0REFSEL_gm);                          // These bits are all 0 for 0.55v reference, so no need to do the mode << VREF_ADC0REFSEL_gp here;
      ADC0.CTRLC = (ADC0.CTRLC & ~(ADC_REFSEL_gm | ADC_SAMPCAP_bm)) | INTERNAL; // Per datasheet, recommended SAMPCAP=0 at ref < 1v
      break;
    case INTERNAL1V1:
    case INTERNAL2V5:
    case INTERNAL4V34:
    case INTERNAL1V5:
      VREF.CTRLA = (VREF.CTRLA & ~(VREF_ADC0REFSEL_gm)) | (mode << VREF_ADC0REFSEL_gp);
      ADC0.CTRLC = (ADC0.CTRLC & ~(ADC_REFSEL_gm)) | INTERNAL | ADC_SAMPCAP_bm; // Per datasheet, recommended SAMPCAP=1 at ref > 1v
      break;
    default:
      ADC0.CTRLC = (ADC0.CTRLC & ~(ADC_REFSEL_gm)) | VDD | ADC_SAMPCAP_bm; // Per datasheet, recommended SAMPCAP=1 at ref > 1v - we don't *KNOW* the external reference will be >1v, but it's probably more likely...
  }
}

int analogRead(uint8_t pin)
{
  pin = digitalPinToAnalogInput(pin);
  if (pin > NUM_ANALOG_INPUTS)
    return NOT_A_PIN;

#if defined(ADC0)
  /* Reference should be already set up */
  /* Select channel */
  ADC0.MUXPOS = (pin << ADC_MUXPOS_gp);

  /* Start conversion */
  ADC0.COMMAND = ADC_STCONV_bm;

  /* Wait for result ready */
  while (!(ADC0.INTFLAGS & ADC_RESRDY_bm))
    ;

  /* Combine two bytes */
  return ADC0.RES;

#else /* No ADC, return 0 */
  return 0;
#endif
}

// analogReadResolution() has two legal values you can pass it, 8 or 10.
// According to the datasheet, you can clock the ADC faster if you set it to 8.
// Like the pinswap functions, if the user passes bogus values, we set it to the default and return false.
uint8_t analogReadResolution(uint8_t res)
{
  if (res==8)
  {
    ADC0.CTRLA |= ADC_RESSEL_bm;
    return 1;
  }
  // If argument wasn't 8, we'll be putting it to default value either way
  ADC0.CTRLA &= ~ADC_RESSEL_bm;
  return (res == 10); // Only return true if the value passed was the valid option, 10.
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
void analogWrite(uint8_t pin, int val)
{
  uint8_t bit_pos = digitalPinToBitPosition(pin);
  if (bit_pos == NOT_A_PIN)
    return;

  // We need to make sure the PWM output is enabled for those pins
  // that support it, as we turn it off when digitally reading or
  // writing with them.  Also, make sure the pin is in output mode
  // for consistently with Wiring, which doesn't require a pinMode
  // call for the analog output pins.
  pinMode(pin, OUTPUT);

  if (val <= 0)
  { /* if zero or negative drive digital low */
    digitalWrite(pin, LOW);
  }
  else if (val >= 255)
  { /* if max or greater drive digital high */
    digitalWrite(pin, HIGH);
  }
  else
  { /* handle pwm to generate analog value */

    /* Get timer */
    uint8_t digital_pin_timer = digitalPinToTimer(pin);

    uint8_t *timer_cmp_out;
    TCB_t *timer_B;

    /* Find out Port and Pin to correctly handle port mux, and timer. */
    switch (digital_pin_timer)
    {
      case TIMERA0:
        /* Split mode, 2x3 8 bit registers. (chapter 19.7) */
        if (bit_pos >= 3)
        {
          timer_cmp_out = ((uint8_t *)(&TCA0.SPLIT.HCMP0)) + 2 * (bit_pos - 3);
          ++bit_pos; /* Upper 3 bits are shifted by 1 */
        }
        else
        {
          /* Calculate correct compare buffer register */
          timer_cmp_out = ((uint8_t *)(&TCA0.SPLIT.LCMP0)) + 2 * bit_pos;
        }

        /* Configure duty cycle for correct compare channel */
        (*timer_cmp_out) = val;

        /* Enable output on pin */
        TCA0.SPLIT.CTRLB |= (1 << (TCA_SPLIT_LCMP0EN_bp + bit_pos));
        break;

      case TIMERB0:
      case TIMERB1:
      case TIMERB2:
      case TIMERB3:

        /* Get pointer to timer, TIMERB0 order definition in Arduino.h*/
        //assert (((TIMERB0 - TIMERB3) == 2));
        timer_B = ((TCB_t *)&TCB0 + (digital_pin_timer - TIMERB0));

        /* set duty cycle */
        timer_B->CCMPH = val;

        /* Enable Timer Output */
        timer_B->CTRLB |= (TCB_CCMPEN_bm);

        break;

        /* If non timer pin, or unknown timer definition. */
        /* do a digital write */

      case NOT_ON_TIMER:
      default:
        if (val < 128)
        {
          digitalWrite(pin, LOW);
        }
        else
        {
          digitalWrite(pin, HIGH);
        }
        break;
    }
  }
}

// Set PWM repeat frequency for all PWM outputs with
// hardware support.
// The argument is the desired frequency in kHz. A
// best effort will be made to find something that matches.
//
void analogWriteFrequency(uint8_t kHz)
{
  static const byte index2setting[] = {
#if F_CPU > 1000000L
#if F_CPU > 2000000L
#if F_CPU > 4000000L
#if F_CPU > 8000000L
    TCA_SPLIT_ENABLE_bm | TCA_SPLIT_CLKSEL_DIV64_gc, // ~1 kHz PWM, ~250kHz clock
#endif
    TCA_SPLIT_ENABLE_bm | TCA_SPLIT_CLKSEL_DIV16_gc, // ~2 kHz is not possible, use 4
#endif
    TCA_SPLIT_ENABLE_bm | TCA_SPLIT_CLKSEL_DIV16_gc, // ~4 kHz PWM, ~1MHz clock
#endif
    TCA_SPLIT_ENABLE_bm | TCA_SPLIT_CLKSEL_DIV8_gc, // ~8 kHz PWM, ~2MHz clock
#endif
    TCA_SPLIT_ENABLE_bm | TCA_SPLIT_CLKSEL_DIV4_gc, // ~16 kHz PWM, ~4MHz clock
    TCA_SPLIT_ENABLE_bm | TCA_SPLIT_CLKSEL_DIV2_gc, // ~32 kHz PWM, ~8MHz clock
    TCA_SPLIT_ENABLE_bm | TCA_SPLIT_CLKSEL_DIV1_gc  // ~64 kHz PWM, ~16MHz clock
  };
  uint8_t index = 0;

  while (kHz > 1)
  { // find approximate match
    kHz >>= 1;
    if (++index >= sizeof(index2setting) - 1) break;
  }
  TCA0.SPLIT.CTRLA = index2setting[index];

  // note that this setting also influences Tone.cpp
}
