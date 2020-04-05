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

#define UNO_WIFI_REV2_PINOUT
#define UNO2018_PINOUT

#define NUM_DIGITAL_PINS               20 // (14 on digital headers + 6 on analog headers)
#define NUM_ANALOG_INPUTS              16
#define NUM_RESERVED_PINS              6  // (TOSC1/2, VREF, RESET, DEBUG USART Rx/Tx)
#define NUM_INTERNALLY_USED_PINS       10 // (2 x Chip select + 2 x UART + 4 x IO + LED_BUILTIN + 1 unused pin)
#define NUM_I2C_PINS                   2  // (SDA / SCL)
#define NUM_SPI_PINS                   3  // (MISO / MOSI / SCK)
#define NUM_TOTAL_FREE_PINS            (NUM_DIGITAL_PINS)
#define NUM_TOTAL_PINS                 (NUM_DIGITAL_PINS + NUM_RESERVED_PINS + NUM_INTERNALLY_USED_PINS + NUM_I2C_PINS + NUM_SPI_PINS)
#define ANALOG_INPUT_OFFSET            14
#define digitalPinToAnalogInput(p)     (((p) <= 5 && (p) != 3) ? (p) : ((p) >= 14 && (p) <= 19) ? ((p) - 14) : ((p) == 25) ? ((p) - 19) : ((p) == 39) ? ((p) - 32) : ((p) >= 11 && (p) <= 13) ? ((p) - 3) : ((p) == 8) ? ((p) + 3) : ((p) >= 35 && (p) <= 36) ? ((p) - 23) : ((p) == 6) ? ((p) + 8) : ((p) == 3) ? ((p) + 12) : NOT_A_PIN)
#define digitalOrAnalogPinToDigital(p) (((p) <= 40) ? (p) : NOT_A_PIN)

#define MILLIS_USE_TIMERB3 // Use TCB3 for millis generation

#define EXTERNAL_NUM_INTERRUPTS     (47)

#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 27)

// Timer pin mapping
#define TCA0_PINS PORTMUX_TCA0_PORTB_gc
#define TCB0_PINS PORTMUX_TCB0_bm
#define TCB1_PINS PORTMUX_TCB1_bm
#define TCB2_PINS PORTMUX_TCB2_bm
#define TCB3_PINS 0x00

// SPI 0
// Pinswap enabled by default and no alternative available
#define SPI_INTERFACES_COUNT 1
#define SPI_MUX              (PORTMUX_SPI0_ALT1_gc)
#define PIN_SPI_MISO         (33)
#define PIN_SPI_SCK          (34)
#define PIN_SPI_MOSI         (32)
#define PIN_SPI_SS           (10)
static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

// TWI 0
// No pinswap enabled by default, and no alternative available
#define TWI_MUX              (PORTMUX_TWI0_DEFAULT_gc)
#define PIN_WIRE_SDA         (20)
#define PIN_WIRE_SCL         (21)
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// Uno2 Main USART available on Arduino header pins
// USART1 on mega4809 (alternative pins)
// Mapped to HWSERIAL0 in Serial library
#define HWSERIAL1                       (&USART1)
#define HWSERIAL1_DRE_VECTOR            (USART1_DRE_vect)
#define HWSERIAL1_DRE_VECTOR_NUM        (USART1_DRE_vect_num)
#define HWSERIAL1_RXC_VECTOR            (USART1_RXC_vect)
#define HWSERIAL1_MUX                   (PORTMUX_USART1_ALT1_gc)
#define HWSERIAL1_MUX_PINSWAP_1         (PORTMUX_USART1_DEFAULT_gc)
#define PIN_WIRE_HWSERIAL1_TX           (1)
#define PIN_WIRE_HWSERIAL1_RX           (0)
#define PIN_WIRE_HWSERIAL1_TX_PINSWAP_1 (32)
#define PIN_WIRE_HWSERIAL1_RX_PINSWAP_1 (33)

// Uno2 Debug USART (not available on headers, only via the mEDGB virtual COM port)
// USART3 on mega4809 (alternative pins)
// Mapped to HWSERIAL1 in Serial library
#define HWSERIAL0                       (&USART3)
#define HWSERIAL0_DRE_VECTOR            (USART3_DRE_vect)
#define HWSERIAL0_DRE_VECTOR_NUM        (USART3_DRE_vect_num)
#define HWSERIAL0_RXC_VECTOR            (USART3_RXC_vect)
#define HWSERIAL0_MUX                   (PORTMUX_USART3_ALT1_gc)
#define HWSERIAL0_MUX_PINSWAP_1         (PORTMUX_USART3_DEFAULT_gc)
#define PIN_WIRE_HWSERIAL0_TX           (27)
#define PIN_WIRE_HWSERIAL0_RX           (26)
#define PIN_WIRE_HWSERIAL0_TX_PINSWAP_1 (9)
#define PIN_WIRE_HWSERIAL0_RX_PINSWAP_1 (10)

// Uno2 Spare USART available on testpoints
// USART0 on mega4809 (alternative pins)
// Mapped to HWSERIAL2 in Serial library
#define HWSERIAL2                       (&USART0)
#define HWSERIAL2_DRE_VECTOR            (USART0_DRE_vect)
#define HWSERIAL2_DRE_VECTOR_NUM        (USART0_DRE_vect_num)
#define HWSERIAL2_RXC_VECTOR            (USART0_RXC_vect)
#define HWSERIAL2_MUX                   (PORTMUX_USART0_ALT1_gc)
#define HWSERIAL2_MUX_PINSWAP_1         (PORTMUX_USART0_DEFAULT_gc)
#define PIN_WIRE_HWSERIAL2_TX           (24)
#define PIN_WIRE_HWSERIAL2_RX           (23)
#define PIN_WIRE_HWSERIAL2_TX_PINSWAP_1 (2)
#define PIN_WIRE_HWSERIAL2_RX_PINSWAP_1 (7)

#define HWSERIAL3_MUX         (PORTMUX_USART2_NONE_gc)

#define LED_BUILTIN 25

#define PIN_A0   (14)
#define PIN_A1   (15)
#define PIN_A2   (16)
#define PIN_A3   (17)
#define PIN_A4   (18)
#define PIN_A5   (19)
#define PIN_A6   (25)
#define PIN_A7   (39)
#define PIN_A8   (11)
#define PIN_A9   (12)
#define PIN_A10  (13)
#define PIN_A11  (8)
#define PIN_A12  (35)
#define PIN_A13  (36)
#define PIN_A14  (6)
#define PIN_A15  (3)

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

#define PINS_COUNT    (40u)

//NINA
#define NINA_GPIO0    (28u)
#define NINA_RESETN   (29u)
#define NINA_ACK      (36u)
#define NINA_CTS      NINA_ACK
#define NINA_RTS      NINA_GPIO0

#define SPIWIFI_SS    (35u)
#define SPIWIFI_ACK   NINA_ACK
#define SPIWIFI_RESET (~NINA_RESETN)

//IMU
#define SPIIMU_SS     (30u)
#define SPIIMU_INT    (31u)

#ifdef ARDUINO_MAIN

// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEGA4809 / ARDUINO
//
//                     (SCL)(SDA) (7)  (2)                 (R)  (3~) (6~)
//                 PA4  PA3  PA2  PA1  PA0  GND  VDD  UPDI PF6  PF5  PF4  PF3
//
//                  48   47   46   45   44   43   42   41   40   39   38   37
//              + ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ +
//        PA5   1|                                                             |36  PF2
//        PA6   2|                                                             |35  PF1 (TOSC2)
//        PA7   3|                                                             |34  PF0 (TOSC1)
//   (9~) PB0   4|                                                             |33  PE3 (8)
//  (10~) PB1   5|                                                             |32  PE2 (13)
//   (5~) PB2   6|                                                             |31  PE1 (12)
//        PB3   7|                          48pin QFN                          |30  PE0 (11~)
//   (Tx) PB4   8|                                                             |29  GND
//   (Rx) PB5   9|                                                             |28  AVDD
//        PC0  10|                                                             |27  PD7 (VREF)
//        PC1  11|                                                             |26  PD6
//        PC2  12|                                                             |25  PD5 (A5)
//               + ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ +
//                  13   14   15   16   17   18   19   20   21   22   23   24
//
//                  PC3  VDD  GND  PC4  PC5  PC6  PC7  PD0  PD1  PD2  PD3  PD4
//                                 (1)  (0)  (4)       (A0) (A1) (A2) (A3) (A4)

//

const uint8_t digital_pin_to_port[] = {
  PC, // 0 PC5/USART1_Rx
  PC, // 1 PC4/USART1_Tx
  PA, // 2 PA0
  PF, // 3 PF5
  PC, // 4 PC6
  PB, // 5 PB2
  PF, // 6 PF4
  PA, // 7 PA1
  PE, // 8 PE3
  PB, // 9 PB0
  PB, // 10 PB1
  PE, // 11 PE0
  PE, // 12 PE1
  PE, // 13 PE2
  PD, // 14 PD0/AI0
  PD, // 15 PD1AI1
  PD, // 16 PD2/AI2
  PD, // 17 PD3/AI3
  PD, // 18 PD4/AI4
  PD, // 19 PD5/AI5
  PA, // 20 PA2/TWI_SDA
  PA, // 21 PA3/TWI_SCL
  PC, // 22 PC3
  PA, // 23 PA5/NINA TX
  PA, // 24 PA4/NINA RX
  PD, // 25 PD6/LED_BUILTIN
  PB, // 26 PB5/USART3_Rx
  PB, // 27 PB4/USART3_Tx
  PA, // 28 PA6/NINA GPIO0
  PA, // 29 PA7/NINA RST
  PB, // 30 PB3/IMU CS
  PC, // 31 PC7/IMU INT
  PC, // 32 PC0/MOSI
  PC, // 33 PC1/MISO
  PC, // 34 PC2/SCK
  PF, // 35 PF2/NINA CS
  PF, // 36 PF3/NINA ACK
  PF, // 37 PF0 TOSC 1
  PF, // 38 PF1 TOSC 2
  PD, // 39 PD7 VREF
  PF  // 40 PF6 RESET
};

/* Use this for accessing PINnCTRL register */
const uint8_t digital_pin_to_bit_position[] = {
  PIN5_bp, // 0 PC5/USART1_Rx
  PIN4_bp, // 1 PC4/USART1_Tx
  PIN0_bp, // 2 PA0
  PIN5_bp, // 3 PF5
  PIN6_bp, // 4 PC6
  PIN2_bp, // 5 PB2
  PIN4_bp, // 6 PF4
  PIN1_bp, // 7 PA1
  PIN3_bp, // 8 PE3
  PIN0_bp, // 9 PB0
  PIN1_bp, // 10 PB1
  PIN0_bp, // 11 PE0
  PIN1_bp, // 12 PE1
  PIN2_bp, // 13 PE2
  PIN0_bp, // 14 PD0/AI0
  PIN1_bp, // 15 PD1AI1
  PIN2_bp, // 16 PD2/AI2
  PIN3_bp, // 17 PD3/AI3
  PIN4_bp, // 18 PD4/AI4
  PIN5_bp, // 19 PD5/AI5
  PIN2_bp, // 20 PA2/TWI_SDA
  PIN3_bp, // 21 PA3/TWI_SCL
  PIN3_bp, // 22 PC3
  PIN5_bp, // 23 PA5/NINA TX
  PIN4_bp, // 24 PA4/NINA RX
  PIN6_bp, // 25 PD6/LED_BUILTIN
  PIN5_bp, // 26 PB5/USART3_Rx
  PIN4_bp, // 27 PB4/USART3_Tx
  PIN6_bp, // 28 PA6/NINA GPIO0
  PIN7_bp, // 29 PA7/NINA RST
  PIN3_bp, // 30 PB3/IMU CS
  PIN7_bp, // 31 PC7/IMU INT
  PIN0_bp, // 32 PC0/MOSI
  PIN1_bp, // 33 PC1/MISO
  PIN2_bp, // 34 PC2/SCK
  PIN2_bp, // 35 PF2/NINA CS
  PIN3_bp, // 36 PF3/NINA ACK
  PIN0_bp, // 37 PF0 TOSC 1
  PIN1_bp, // 38 PF1 TOSC 2
  PIN7_bp, // 39 PD7 VREF
  PIN6_bp  // 40 PF6 RESET
};

/* Use this for accessing PINnCTRL register */
const uint8_t digital_pin_to_bit_mask[] = {
  PIN5_bm, // 0 PC5/USART1_Rx
  PIN4_bm, // 1 PC4/USART1_Tx
  PIN0_bm, // 2 PA0
  PIN5_bm, // 3 PF5
  PIN6_bm, // 4 PC6
  PIN2_bm, // 5 PB2
  PIN4_bm, // 6 PF4
  PIN1_bm, // 7 PA1
  PIN3_bm, // 8 PE3
  PIN0_bm, // 9 PB0
  PIN1_bm, // 10 PB1
  PIN0_bm, // 11 PE0
  PIN1_bm, // 12 PE1
  PIN2_bm, // 13 PE2
  PIN0_bm, // 14 PD0/AI0
  PIN1_bm, // 15 PD1/AI1
  PIN2_bm, // 16 PD2/AI2
  PIN3_bm, // 17 PD3/AI3
  PIN4_bm, // 18 PD4/AI4
  PIN5_bm, // 19 PD5/AI5
  PIN2_bm, // 20 PA2/TWI_SDA
  PIN3_bm, // 21 PA3/TWI_SCL
  PIN3_bm, // 22 PC3
  PIN5_bm, // 23 PA5/NINA TX
  PIN4_bm, // 24 PA4/NINA RX
  PIN6_bm, // 25 PD6/LED_BUILTIN
  PIN5_bm, // 26 PB5/USART3_Rx
  PIN4_bm, // 27 PB4/USART3_Tx
  PIN6_bm, // 28 PA6/NINA GPIO0
  PIN7_bm, // 29 PA7/NINA RST
  PIN3_bm, // 30 PB3/IMU CS
  PIN7_bm, // 31 PC7/IMU INT
  PIN0_bm, // 32 PC0/MOSI
  PIN1_bm, // 33 PC1/MISO
  PIN2_bm, // 34 PC2/SCK
  PIN2_bm, // 35 PF2/NINA CS
  PIN3_bm, // 36 PF3/NINA ACK
  PIN0_bm, // 37 PF0 TOSC 1
  PIN1_bm, // 38 PF1 TOSC 2
  PIN7_bm, // 39 PD7 VREF
  PIN6_bm  // 40 PF6 RESET
};

const uint8_t digital_pin_to_timer[] = {
  NOT_ON_TIMER, // 0 PC5/USART1_Rx
  NOT_ON_TIMER, // 1 PC4/USART1_Tx
  NOT_ON_TIMER, // 2 PA0
  TIMERB1,      // 3 PF5
  NOT_ON_TIMER, // 4 PC6
  TIMERA0,      // 5 PB2
  TIMERB0,      // 6 PF4
  NOT_ON_TIMER, // 7 PA1
  NOT_ON_TIMER, // 8 PE3
  TIMERA0,      // 9 PB0
  TIMERA0,      // 10 PB1
  NOT_ON_TIMER, // 11 PE0
  NOT_ON_TIMER, // 12 PE1
  NOT_ON_TIMER, // 13 PE2
  NOT_ON_TIMER, // 14 PD0/AI0
  NOT_ON_TIMER, // 15 PD1AI1
  NOT_ON_TIMER, // 16 PD2/AI2
  NOT_ON_TIMER, // 17 PD3/AI3
  NOT_ON_TIMER, // 18 PD4/AI4
  NOT_ON_TIMER, // 19 PD5/AI5
  NOT_ON_TIMER, // 20 PA2/TWI_SDA
  NOT_ON_TIMER, // 21 PA3/TWI_SCL
  NOT_ON_TIMER, // 22 PC3
  NOT_ON_TIMER, // 23 PA5/NINA TX
  NOT_ON_TIMER, // 24 PA4/NINA RX
  NOT_ON_TIMER, // 25 PD6/LED_BUILTIN
  NOT_ON_TIMER, // 26 PB5/USART3_Rx
#ifdef MILLIS_USE_TIMERB2
  NOT_ON_TIMER, // 27 PB4/USART3_Tx
#else
  TIMERB2,      // 27 PB4/USART3_Tx/TCB2 PWM
#endif
  NOT_ON_TIMER, // 28 PA6/NINA GPIO0
  NOT_ON_TIMER, // 29 PA7/NINA RST
  NOT_ON_TIMER, // 30 PB3/IMU CS
  NOT_ON_TIMER, // 31 PC7/IMU INT
  NOT_ON_TIMER, // 32 PC0/MOSI
  NOT_ON_TIMER, // 33 PC1/MISO
  NOT_ON_TIMER, // 34 PC2/SCK
  NOT_ON_TIMER, // 35 PF2/NINA CS
  NOT_ON_TIMER, // 36 PF3/NINA ACK
  NOT_ON_TIMER, // 37 PF0 TOSC 1
  NOT_ON_TIMER, // 38 PF1 TOSC 2
  NOT_ON_TIMER, // 39 PD7 VREF
  NOT_ON_TIMER  // 40 PF6 RESET
};


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
#define SERIAL_PORT_HARDWARE_OPEN Serial2
#define SerialNina                Serial2

void initVariant() __attribute__((weak));
void initVariant() {
  // NINA - SPI boot
  pinMode(NINA_GPIO0, OUTPUT);
  digitalWrite(NINA_GPIO0, HIGH);

  // disable the NINA
  pinMode(NINA_RESETN, OUTPUT);
  digitalWrite(NINA_RESETN, HIGH);

  // NINA SS HIGH by default
  pinMode(SPIWIFI_SS, OUTPUT);
  digitalWrite(SPIWIFI_SS, HIGH);

  // IMU SS HIGH by default
  pinMode(SPIIMU_SS, OUTPUT);
  digitalWrite(SPIIMU_SS, HIGH);
}

#endif
