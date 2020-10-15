/*
  Copyright (c) 2018 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

/*
 * Defines for 16 bit timers used with Servo library
 *
 */

#ifndef __SERVO_TIMERS_H__
#define __SERVO_TIMERS_H__

#if !defined(SERVO_USE_TIMERB0) || !defined(SERVO_USE_TIMERB1) || !defined(SERVO_USE_TIMERB2) || !defined(SERVO_USE_TIMERB3)
  #if defined(__AVR_ATmega808__) || defined(__AVR_ATmega1608__)  \
   || defined(__AVR_ATmega3208__) || defined(__AVR_ATmega4808__) \
   || defined(NANO_EVERY_PINOUT) || defined(UNO_WIFI_REV2_PINOUT)
    #define SERVO_USE_TIMERB1
  #elif defined(__AVR_ATmega809__) || defined(__AVR_ATmega1609__) || defined(__AVR_ATmega3209__) || defined(__AVR_ATmega4809__)
    #define SERVO_USE_TIMERB3
  #else
    #error "No timers allowed for Servo"
  #endif
#endif

__attribute__ ((used)) static volatile TCB_t* _timer =
#if defined(SERVO_USE_TIMERB0)
  &TCB0;
#endif
#if defined(SERVO_USE_TIMERB1)
  &TCB1;
#endif
#if defined(SERVO_USE_TIMERB2)
  &TCB2;
#endif
#if defined(SERVO_USE_TIMERB3)
  &TCB3;
#endif

typedef enum {
  timer0,
  _Nbr_16timers
} timer16_Sequence_t;


#endif  /* __SERVO_TIMERS_H__ */
