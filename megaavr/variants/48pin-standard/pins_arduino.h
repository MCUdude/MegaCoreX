/****************************************************|
|               48-PIN STANDARD PINOUT               |
|       https://github.com/MCUdude/MegaCoreX         |
|                                                    |
| COMPATIBLE WITH:                                   |
| ATmega4809                                         |
| ATmega3209                                         |
| ATmega1609                                         |
| ATmega809                                          |
|                                                    |
| Note that this pinout is not directly compatible   |
| with the UNO Wifi Rev2 hardware without performing |
| pinswaps. This pinout is supposed to be as close   |
| to the metal as possible. The only peripherals     |
| that are swapped to other pins by default are the  |
| PWM outputs.                                       |
|                                                    |
|****************************************************/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>
#include "timers.h"

#define DEFAULT_48PIN_PINOUT

#define NUM_DIGITAL_PINS               41
#define NUM_ANALOG_INPUTS              16
#define NUM_RESERVED_PINS              0
#define NUM_INTERNALLY_USED_PINS       0
#define NUM_I2C_PINS                   2  // (SDA / SCL)
#define NUM_SPI_PINS                   3  // (MISO / MOSI / SCK)
#define NUM_TOTAL_FREE_PINS            (NUM_DIGITAL_PINS)
#define NUM_TOTAL_PINS                 (NUM_DIGITAL_PINS)
#define ANALOG_INPUT_OFFSET            22 
#define digitalPinToAnalogInput(p)     ((p < NUM_ANALOG_INPUTS) ? (p) : ((p) >= 22 && (p) <= 33) ? ((p) - ANALOG_INPUT_OFFSET) : ((p) >= 36 && (p) <=39) ? ((p) - 2 - ANALOG_INPUT_OFFSET) : NOT_A_PIN)
#define digitalOrAnalogPinToDigital(p) ((p <= 11) ? ((p) + ANALOG_INPUT_OFFSET) : ((p) <= 15) ? ((p) + ANALOG_INPUT_OFFSET + 2) : (((p) >= 22 && (p) <= 33) || ((p) >= 36 && (p) <= 39)) ? (p) :  NOT_A_PIN)

#if !defined(MILLIS_USE_TIMERB0) || !defined(MILLIS_USE_TIMERB1) || !defined(MILLIS_USE_TIMERB2) || !defined(MILLIS_USE_TIMERB3)
#define MILLIS_USE_TIMERB3
#endif

#define EXTERNAL_NUM_INTERRUPTS     (47)

#define digitalPinHasPWM(p)         (((p) >= 14 && (p) <= 19) || (p) == 38 || (p) == 39)

// SPI 0
// No pinswap enabled by default
#define SPI_INTERFACES_COUNT   1
#define SPI_MUX                (PORTMUX_SPI0_DEFAULT_gc)
#define SPI_MUX_PINSWAP_1      (PORTMUX_SPI0_ALT1_gc)
#define SPI_MUX_PINSWAP_2      (PORTMUX_SPI0_ALT2_gc)
#define PIN_SPI_MOSI           (4)
#define PIN_SPI_MISO           (5)
#define PIN_SPI_SCK            (6)
#define PIN_SPI_SS             (7)
#define PIN_SPI_MOSI_PINSWAP_1 (14)
#define PIN_SPI_MISO_PINSWAP_1 (15)
#define PIN_SPI_SCK_PINSWAP_1  (16)
#define PIN_SPI_SS_PINSWAP_1   (17)
#define PIN_SPI_MOSI_PINSWAP_2 (30)
#define PIN_SPI_MISO_PINSWAP_2 (31)
#define PIN_SPI_SCK_PINSWAP_2  (32)
#define PIN_SPI_SS_PINSWAP_2   (33)
static uint8_t MOSI = PIN_SPI_MOSI;
static uint8_t MISO = PIN_SPI_MISO;
static uint8_t SCK  = PIN_SPI_SCK;
static uint8_t SS   = PIN_SPI_SS;

// TWI 0
// No pinswap enabled by default
#define TWI_MUX                (PORTMUX_TWI0_DEFAULT_gc)
#define TWI_MUX_PINSWAP        (PORTMUX_TWI0_ALT2_gc)
#define PIN_WIRE_SDA           (2)
#define PIN_WIRE_SCL           (3)
#define PIN_WIRE_SDA_PINSWAP_1 (16)
#define PIN_WIRE_SCL_PINSWAP_1 (17)
static uint8_t SDA = PIN_WIRE_SDA;
static uint8_t SCL = PIN_WIRE_SCL;

#define LED_BUILTIN 39

// USART 0
// No pinswap by default
#define HWSERIAL0 (&USART0)
#define HWSERIAL0_DRE_VECTOR            (USART0_DRE_vect)
#define HWSERIAL0_DRE_VECTOR_NUM        (USART0_DRE_vect_num)
#define HWSERIAL0_RXC_VECTOR            (USART0_RXC_vect)
#define HWSERIAL0_MUX                   (PORTMUX_USART0_DEFAULT_gc)
#define HWSERIAL0_MUX_PINSWAP_1         (PORTMUX_USART0_ALT1_gc)
#define PIN_WIRE_HWSERIAL0_TX           (0)
#define PIN_WIRE_HWSERIAL0_RX           (1)
#define PIN_WIRE_HWSERIAL0_TX_PINSWAP_1 (4)
#define PIN_WIRE_HWSERIAL0_RX_PINSWAP_1 (5)

// USART1
// No pinswap by default
#define HWSERIAL1                       (&USART1)
#define HWSERIAL1_DRE_VECTOR            (USART1_DRE_vect)
#define HWSERIAL1_DRE_VECTOR_NUM        (USART1_DRE_vect_num)
#define HWSERIAL1_RXC_VECTOR            (USART1_RXC_vect)
#define HWSERIAL1_MUX                   (PORTMUX_USART1_DEFAULT_gc)
#define HWSERIAL1_MUX_PINSWAP_1         (PORTMUX_USART1_ALT1_gc)
#define PIN_WIRE_HWSERIAL1_TX           (14)
#define PIN_WIRE_HWSERIAL1_RX           (15)
#define PIN_WIRE_HWSERIAL1_TX_PINSWAP_1 (18)
#define PIN_WIRE_HWSERIAL1_RX_PINSWAP_1 (19)

// USART 2
// No pinswap by default
#define HWSERIAL2 (&USART2)
#define HWSERIAL2_DRE_VECTOR            (USART2_DRE_vect)
#define HWSERIAL2_DRE_VECTOR_NUM        (USART2_DRE_vect_num)
#define HWSERIAL2_RXC_VECTOR            (USART2_RXC_vect)
#define HWSERIAL2_MUX                   (PORTMUX_USART2_DEFAULT_gc)
#define HWSERIAL2_MUX_PINSWAP_1         (PORTMUX_USART2_ALT1_gc)
#define PIN_WIRE_HWSERIAL2_TX           (34)
#define PIN_WIRE_HWSERIAL2_RX           (35)
#define PIN_WIRE_HWSERIAL2_TX_PINSWAP_1 (38)
#define PIN_WIRE_HWSERIAL2_RX_PINSWAP_1 (39)

// USART 3
// No pinswap by default
#define HWSERIAL3                       (&USART3)
#define HWSERIAL3_DRE_VECTOR            (USART3_DRE_vect)
#define HWSERIAL3_DRE_VECTOR_NUM        (USART3_DRE_vect_num)
#define HWSERIAL3_RXC_VECTOR            (USART3_RXC_vect)
#define HWSERIAL3_MUX                   (PORTMUX_USART3_DEFAULT_gc)
#define HWSERIAL3_MUX_PINSWAP_1         (PORTMUX_USART3_ALT1_gc)
#define PIN_WIRE_HWSERIAL3_TX           (8)
#define PIN_WIRE_HWSERIAL3_RX           (9)
#define PIN_WIRE_HWSERIAL3_TX_PINSWAP_1 (12)
#define PIN_WIRE_HWSERIAL3_RX_PINSWAP_1 (13)

#define PIN_A0   (22)
#define PIN_A1   (23)
#define PIN_A2   (24)
#define PIN_A3   (25)
#define PIN_A4   (26)
#define PIN_A5   (27)
#define PIN_A6   (28)
#define PIN_A7   (29)
#define PIN_A8   (30)
#define PIN_A9   (31)
#define PIN_A10  (32)
#define PIN_A11  (33)
#define PIN_A12  (36)
#define PIN_A13  (37)
#define PIN_A14  (38)
#define PIN_A15  (39)

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

#define PINS_COUNT    (41u)


#ifdef ARDUINO_MAIN

const uint8_t digital_pin_to_port[] = {
  PA, //  0 PA0/USART0_Tx/CLKIN
  PA, //  1 PA1/USART0_Rx
  PA, //  2 PA2/SDA
  PA, //  3 PA3/SCL
  PA, //  4 PA4/MOSI
  PA, //  5 PA5/MISO
  PA, //  6 PA6/SCK
  PA, //  7 PA7/SS/CLKOUT
  PB, //  8 PB0/USART3_Tx
  PB, //  9 PB1/USART3_Rx
  PB, // 10 PB2
  PB, // 11 PB3
  PB, // 12 PB4/TCB2 PWM
  PB, // 13 PB5/TCB3 PWM
  PC, // 14 PC0/USART1_Tx/TCA0 PWM
  PC, // 15 PC1/USART1_Rx/TCA0 PWM
  PC, // 16 PC2/TCA0 PWM
  PC, // 17 PC3/TCA0 PWM
  PC, // 18 PC4/TCA0 PWM
  PC, // 19 PC5/TCA0 PWM
  PC, // 20 PC6
  PC, // 21 PC7
  PD, // 22 PD0/AIN0
  PD, // 23 PD1/AIN1
  PD, // 24 PD2/AIN2
  PD, // 25 PD3/AIN3
  PD, // 26 PD4/AIN4
  PD, // 27 PD5/AIN5
  PD, // 28 PD6/AIN6
  PD, // 29 PD7/AIN7/AREF
  PE, // 30 PE0/AIN8
  PE, // 31 PE1/AIN9
  PE, // 32 PE2/AIN10
  PE, // 33 PE3/AIN11
  PF, // 34 PF0/USART2_Tx/TOSC1
  PF, // 35 PF1/USART2_Rx/TOSC2
  PF, // 36 PF2/AIN12
  PF, // 37 PF3/AIN13
  PF, // 38 PF4/AIN14/TCB0 PWM
  PF, // 39 PF5/AIN15/TCB1 PWM/LED_BUILTIN
  PF  // 40 PF6 RESET
};

/* Use this for accessing PINnCTRL register */
const uint8_t digital_pin_to_bit_position[] = {
  PIN0_bp, //  0 PIN_bp0/USART0_Tx/CLKIN
  PIN1_bp, //  1 PA1/USART0_Rx
  PIN2_bp, //  2 PA2/SDA
  PIN3_bp, //  3 PA3/SCL
  PIN4_bp, //  4 PA4/MOSI
  PIN5_bp, //  5 PA5/MISO
  PIN6_bp, //  6 PA6/SCK
  PIN7_bp, //  7 PA7/SS/CLKOUT
  PIN0_bp, //  8 PB0/USART3_Tx
  PIN1_bp, //  9 PB1/USART3_Rx
  PIN2_bp, // 10 PB2
  PIN3_bp, // 11 PB3
  PIN4_bp, // 12 PB4/TCB2 PWM
  PIN5_bp, // 13 PB5/TCB2 PWM
  PIN0_bp, // 14 PC0/USART1_Tx/TCA0 PWM
  PIN1_bp, // 15 PC1/USART1_Rx/TCA0 PWM
  PIN2_bp, // 16 PC2/TCA0 PWM
  PIN3_bp, // 17 PC3/TCA0 PWM
  PIN4_bp, // 18 PC4/TCA0 PWM
  PIN5_bp, // 19 PC5/TCA0 PWM
  PIN6_bp, // 20 PC6
  PIN7_bp, // 21 PC7
  PIN0_bp, // 22 PD0/AIN0
  PIN1_bp, // 23 PD1/AIN1
  PIN2_bp, // 24 PD2/AIN2
  PIN3_bp, // 25 PD3/AIN3
  PIN4_bp, // 26 PD4/AIN4
  PIN5_bp, // 27 PD5/AIN5
  PIN6_bp, // 28 PD6/AIN6
  PIN7_bp, // 29 PD7/AIN7/AREF
  PIN0_bp, // 30 PE0/AIN8
  PIN1_bp, // 31 PE1/AIN9
  PIN2_bp, // 32 PE2/AIN10
  PIN3_bp, // 33 PE3/AIN11
  PIN0_bp, // 34 PF0/USART2_Tx/TOSC1
  PIN1_bp, // 35 PF1/USART2_Rx/TOSC2
  PIN2_bp, // 36 PF2/AIN12
  PIN3_bp, // 37 PF3/AIN13
  PIN4_bp, // 38 PF4/AIN14/TCB0 PWM
  PIN5_bp, // 39 PF5/AIN15/TCB1 PWM/LED_BUILTIN
  PIN6_bp  // 40 PF6 RESET
};

/* Use this for accessing PINnCTRL register */
const uint8_t digital_pin_to_bit_mask[] = {
  PIN0_bm, //  0 PIN_bp0/USART0_Tx/CLKIN
  PIN1_bm, //  1 PA1/USART0_Rx
  PIN2_bm, //  2 PA2/SDA
  PIN3_bm, //  3 PA3/SCL
  PIN4_bm, //  4 PA4/MOSI
  PIN5_bm, //  5 PA5/MISO
  PIN6_bm, //  6 PA6/SCK
  PIN7_bm, //  7 PA7/SS/CLKOUT
  PIN0_bm, //  8 PB0/USART3_Tx
  PIN1_bm, //  9 PB1/USART3_Rx
  PIN2_bm, // 10 PB2
  PIN3_bm, // 11 PB3
  PIN4_bm, // 12 PB4/TCB2 PWM
  PIN5_bm, // 13 PB5/TCB3 PWM
  PIN0_bm, // 14 PC0/USART1_Tx/TCA0 PWM
  PIN1_bm, // 15 PC1/USART1_Rx/TCA0 PWM
  PIN2_bm, // 16 PC2/TCA0 PWM
  PIN3_bm, // 17 PC3/TCA0 PWM
  PIN4_bm, // 18 PC4/TCA0 PWM
  PIN5_bm, // 19 PC5/TCA0 PWM
  PIN6_bm, // 20 PC6
  PIN7_bm, // 21 PC7
  PIN0_bm, // 22 PD0/AIN0
  PIN1_bm, // 23 PD1/AIN1
  PIN2_bm, // 24 PD2/AIN2
  PIN3_bm, // 25 PD3/AIN3
  PIN4_bm, // 26 PD4/AIN4
  PIN5_bm, // 27 PD5/AIN5
  PIN6_bm, // 28 PD6/AIN6
  PIN7_bm, // 29 PD7/AIN7/AREF
  PIN0_bm, // 30 PE0/AIN8
  PIN1_bm, // 31 PE1/AIN9
  PIN2_bm, // 32 PE2/AIN10
  PIN3_bm, // 33 PE3/AIN11
  PIN0_bm, // 34 PF0/USART2_Tx/TOSC1
  PIN1_bm, // 35 PF1/USART2_Rx/TOSC2
  PIN2_bm, // 36 PF2/AIN12
  PIN3_bm, // 37 PF3/AIN13
  PIN4_bm, // 38 PF4/AIN14/TCB0 PWM
  PIN5_bm, // 39 PF5/AIN15/TCB1 PWM/LED_BUILTIN
  PIN6_bm  // 40 PF6 RESET
};

const uint8_t digital_pin_to_timer[] = {
  NOT_ON_TIMER, //  0 PA0/USART0_Tx/CLKIN
  NOT_ON_TIMER, //  1 PA1/USART0_Rx
  NOT_ON_TIMER, //  2 PA2/SDA
  NOT_ON_TIMER, //  3 PA3/SCL
  NOT_ON_TIMER, //  4 PA4/MOSI
  NOT_ON_TIMER, //  5 PA5/MISO
  NOT_ON_TIMER, //  6 PA6/SCK
  NOT_ON_TIMER, //  7 PA7/SS/CLKOUT
  NOT_ON_TIMER, //  8 PB0/USART3_Tx
  NOT_ON_TIMER, //  9 PB1/USART3_Rx
  NOT_ON_TIMER, // 10 PB2
  NOT_ON_TIMER, // 11 PB3
  TIMERB2,      // 12 PB4/TCB2 PWM
  TIMERB3,      // 13 PB5/TCB3 PWM
  TIMERA0,      // 14 PC0/USART1_Tx/TCA0 PWM
  TIMERA0,      // 15 PC1/USART1_Rx/TCA0 PWM
  TIMERA0,      // 16 PC2/TCA0 PWM
  TIMERA0,      // 17 PC3/TCA0 PWM
  TIMERA0,      // 18 PC4/TCA0 PWM
  TIMERA0,      // 19 PC5/TCA0 PWM
  NOT_ON_TIMER, // 20 PC6
  NOT_ON_TIMER, // 21 PC7
  NOT_ON_TIMER, // 22 PD0/AIN0
  NOT_ON_TIMER, // 23 PD1/AIN1
  NOT_ON_TIMER, // 24 PD2/AIN2
  NOT_ON_TIMER, // 25 PD3/AIN3
  NOT_ON_TIMER, // 26 PD4/AIN4
  NOT_ON_TIMER, // 27 PD5/AIN5
  NOT_ON_TIMER, // 28 PD6/AIN6
  NOT_ON_TIMER, // 29 PD7/AIN7/AREF
  NOT_ON_TIMER, // 30 PE0/AIN8
  NOT_ON_TIMER, // 31 PE1/AIN9
  NOT_ON_TIMER, // 32 PE2/AIN10
  NOT_ON_TIMER, // 33 PE3/AIN11
  NOT_ON_TIMER, // 34 PF0/USART2_Tx/TOSC1
  NOT_ON_TIMER, // 35 PF1/USART2_Rx/TOSC2
  NOT_ON_TIMER, // 36 PF2/AIN12
  NOT_ON_TIMER, // 37 PF3/AIN13
  TIMERB0,      // 38 PF4/AIN14/TCB0 PWM
  TIMERB1,      // 39 PF5/AIN15/TCB1 PWM/LED_BUILTIN
  NOT_ON_TIMER  // 40 PF6 RESET
};


#endif

#endif
