/****************************************************|
|               32-PIN STANDARD PINOUT               |
|       https://github.com/MCUdude/MegaCoreX         |
|                                                    |
| COMPATIBLE WITH:                                   |
| ATmega4808                                         |
| ATmega3208                                         |
| ATmega1608                                         |
| ATmega808                                          |
|                                                    |
| Note that PWM output pins are swapped by default   |
|                                                    |
|****************************************************/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>
#include "timers.h"

#define MEGACOREX_DEFAULT_32PIN_PINOUT
#define __AVR_ATmegax08__

// Arduino pin macros
#define PIN_PA0 0
#define PIN_PA1 1
#define PIN_PA2 2
#define PIN_PA3 3
#define PIN_PA4 4
#define PIN_PA5 5
#define PIN_PA6 6
#define PIN_PA7 7
#define PIN_PC0 8
#define PIN_PC1 9
#define PIN_PC2 10
#define PIN_PC3 11
#define PIN_PD0 12
#define PIN_PD1 13
#define PIN_PD2 14
#define PIN_PD3 15
#define PIN_PD4 16
#define PIN_PD5 17
#define PIN_PD6 18
#define PIN_PD7 19
#define PIN_PF0 20
#define PIN_PF1 21
#define PIN_PF2 22
#define PIN_PF3 23
#define PIN_PF4 24
#define PIN_PF5 25
#define PIN_PF6 26

#define PINS_COUNT                     27
#define NUM_DIGITAL_PINS               PINS_COUNT
#define NUM_ANALOG_INPUTS              12
#define NUM_RESERVED_PINS              0
#define NUM_INTERNALLY_USED_PINS       0
#define NUM_I2C_PINS                   2
#define NUM_SPI_PINS                   3
#define NUM_TOTAL_FREE_PINS            PINS_COUNT
#define NUM_TOTAL_PINS                 PINS_COUNT
#define ANALOG_INPUT_OFFSET            12
#define LED_BUILTIN                    PIN_PA7
#define EXTERNAL_NUM_INTERRUPTS        47
#define digitalPinToAnalogInput(p)     ((p < 8) ? (p) : ((p) < 12) ? ((p) + 4) : ((p) < 20) ? ((p) - 12) : ((p) >= 22 && (p) <=25) ? ((p) - 10) : NOT_A_PIN)
#define digitalOrAnalogPinToDigital(p) ((p < 8) ? ((p) + ANALOG_INPUT_OFFSET) : ((p) >= 8 && (p) <= 11) ? ((p) + ANALOG_INPUT_OFFSET + 2) : (((p) >= 12 && (p) <= 19) || ((p) >= 22 && (p) <= 25)) ? (p) : NOT_A_PIN)

#if !defined(MILLIS_USE_TIMERB0) || !defined(MILLIS_USE_TIMERB1) || !defined(MILLIS_USE_TIMERB2)
#define MILLIS_USE_TIMERB2 // Use TCB2 if nothing else if defined
#endif

// PWM pins
#if defined(MILLIS_USE_TIMERB0)
  #define digitalPinHasPWM(p)  (((p) == PIN_PD0) || ((p) == PIN_PD1) || ((p) == PIN_PD1) || ((p) == PIN_PD3) || \
                                ((p) == PIN_PD4) || ((p) == PIN_PD5) || ((p) == PIN_PA3) || ((p) == PIN_PC0))
#elif defined(MILLIS_USE_TIMERB1)
  #define digitalPinHasPWM(p)  (((p) == PIN_PD0) || ((p) == PIN_PD1) || ((p) == PIN_PD1) || ((p) == PIN_PD3) || \
                                ((p) == PIN_PD4) || ((p) == PIN_PD5) || ((p) == PIN_PA2) || ((p) == PIN_PC0))
#else // default to MILLIS_USE_TIMERB2
  #define digitalPinHasPWM(p)  (((p) == PIN_PD0) || ((p) == PIN_PD1) || ((p) == PIN_PD1) || ((p) == PIN_PD3) || \
                                ((p) == PIN_PD4) || ((p) == PIN_PD5) || ((p) == PIN_PA2) || ((p) == PIN_PA3))
#endif

// Timer pin mapping
#define TCA0_PINS PORTMUX_TCA0_PORTD_gc // TCA0 output on PD[0:5]
#define TCB0_PINS 0x00                  // TCB0 output on PA2 instead of PF4
#define TCB1_PINS 0x00                  // TCB1 output on PA3 instead of PF5
#define TCB2_PINS 0x00                  // TCB2 output on PC0 instead of PB4

// SPI 0
// No pinswap enabled by default
// Pinswap 2 not available
#define SPI_INTERFACES_COUNT   1
#define SPI_MUX                PORTMUX_SPI0_DEFAULT_gc
#define SPI_MUX_PINSWAP_1      PORTMUX_SPI0_ALT1_gc
#define PIN_SPI_MISO           PIN_PA5
#define PIN_SPI_SCK            PIN_PA6
#define PIN_SPI_MOSI           PIN_PA4
#define PIN_SPI_SS             PIN_PA7
#define PIN_SPI_MISO_PINSWAP_1 PIN_PC1
#define PIN_SPI_SCK_PINSWAP_1  PIN_PC2
#define PIN_SPI_MOSI_PINSWAP_1 PIN_PC0
#define PIN_SPI_SS_PINSWAP_1   PIN_PC3
static const uint8_t SS   =    PIN_SPI_SS;
static const uint8_t MOSI =    PIN_SPI_MOSI;
static const uint8_t MISO =    PIN_SPI_MISO;
static const uint8_t SCK  =    PIN_SPI_SCK;

// TWI 0
// No pinswap enabled by default
#define TWI_MUX                PORTMUX_TWI0_DEFAULT_gc
#define TWI_MUX_PINSWAP        PORTMUX_TWI0_ALT2_gc
#define PIN_WIRE_SDA           PIN_PA2
#define PIN_WIRE_SCL           PIN_PA3
#define PIN_WIRE_SDA_PINSWAP_1 PIN_PC2
#define PIN_WIRE_SCL_PINSWAP_1 PIN_PC3
static const uint8_t SDA =     PIN_WIRE_SDA;
static const uint8_t SCL =     PIN_WIRE_SCL;

// USART 0
// No pinswap enabled by default
#define HWSERIAL0                       &USART0
#define HWSERIAL0_DRE_VECTOR            USART0_DRE_vect
#define HWSERIAL0_DRE_VECTOR_NUM        USART0_DRE_vect_num
#define HWSERIAL0_RXC_VECTOR            USART0_RXC_vect
#define HWSERIAL0_MUX                   PORTMUX_USART0_DEFAULT_gc
#define HWSERIAL0_MUX_PINSWAP_1         PORTMUX_USART0_ALT1_gc
#define PIN_HWSERIAL0_TX                PIN_PA0
#define PIN_HWSERIAL0_RX                PIN_PA1
#define PIN_HWSERIAL0_XCK               PIN_PA2
#define PIN_HWSERIAL0_XDIR              PIN_PA3
#define PIN_HWSERIAL0_TX_PINSWAP_1      PIN_PA4
#define PIN_HWSERIAL0_RX_PINSWAP_1      PIN_PA5
#define PIN_HWSERIAL0_XCK_PINSWAP_1     PIN_PA6
#define PIN_HWSERIAL0_XDIR_PINSWAP_1    PIN_PA7

// USART1
// No pinswap available
#define HWSERIAL1                       &USART1
#define HWSERIAL1_DRE_VECTOR            USART1_DRE_vect
#define HWSERIAL1_DRE_VECTOR_NUM        USART1_DRE_vect_num
#define HWSERIAL1_RXC_VECTOR            USART1_RXC_vect
#define HWSERIAL1_MUX                   PORTMUX_USART1_DEFAULT_gc
#define HWSERIAL1_MUX_PINSWAP_1         PORTMUX_USART1_DEFAULT_gc
#define PIN_HWSERIAL1_TX                PIN_PC0
#define PIN_HWSERIAL1_RX                PIN_PC1
#define PIN_HWSERIAL1_XCK               PIN_PC2
#define PIN_HWSERIAL1_XDIR              PIN_PC3
#define PIN_HWSERIAL1_TX_PINSWAP_1      PIN_HWSERIAL1_TX
#define PIN_HWSERIAL1_RX_PINSWAP_1      PIN_HWSERIAL1_RX

// USART 2
// No pinswap enabled by default
#define HWSERIAL2                       &USART2
#define HWSERIAL2_DRE_VECTOR            USART2_DRE_vect
#define HWSERIAL2_DRE_VECTOR_NUM        USART2_DRE_vect_num
#define HWSERIAL2_RXC_VECTOR            USART2_RXC_vect
#define HWSERIAL2_MUX                   PORTMUX_USART2_DEFAULT_gc
#define HWSERIAL2_MUX_PINSWAP_1         PORTMUX_USART2_ALT1_gc
#define PIN_HWSERIAL2_TX                PIN_PF0
#define PIN_HWSERIAL2_RX                PIN_PF1
#define PIN_HWSERIAL2_XCK               PIN_PF2
#define PIN_HWSERIAL2_XDIR              PIN_PF3
#define PIN_HWSERIAL2_TX_PINSWAP_1      PIN_PF4
#define PIN_HWSERIAL2_RX_PINSWAP_1      PIN_PF5
#define PIN_HWSERIAL2_XCK_PINSWAP_1     PIN_PF6

// Analog pins
#define PIN_A0   PIN_PD0
#define PIN_A1   PIN_PD1
#define PIN_A2   PIN_PD2
#define PIN_A3   PIN_PD3
#define PIN_A4   PIN_PD4
#define PIN_A5   PIN_PD5
#define PIN_A6   PIN_PD6
#define PIN_A7   PIN_PD7
#define PIN_A8   PIN_PF2
#define PIN_A9   PIN_PF3
#define PIN_A10  PIN_PF4
#define PIN_A11  PIN_PF5
#define PIN_A12  PIN_PF2
#define PIN_A13  PIN_PF3
#define PIN_A14  PIN_PF4
#define PIN_A15  PIN_PF5
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
  PA, //  0 PA0/USART0_Tx/CLKIN
  PA, //  1 PA1/USART0_Rx
  PA, //  2 PA2/SDA
  PA, //  3 PA3/SCL
  PA, //  4 PA4/MOSI
  PA, //  5 PA5/MISO
  PA, //  6 PA6/SCK
  PA, //  7 PA7/SS/CLKOUT/LED_BUILTIN
  PC, //  8 PC0/USART1_Tx
  PC, //  9 PC1/USART1_Rx
  PC, // 10 PC2
  PC, // 11 PC3
  PD, // 12 PD0/AIN0
  PD, // 13 PD1/AIN1
  PD, // 14 PD2/AIN2
  PD, // 15 PD3/AIN3
  PD, // 16 PD4/AIN4
  PD, // 17 PD5/AIN5
  PD, // 18 PD6/AIN6
  PD, // 19 PD7/AIN7/AREF
  PF, // 20 PF0/USART2_Tx/TOSC1
  PF, // 21 PF1/USART2_Rx/TOSC2
  PF, // 22 PF2/AIN12
  PF, // 23 PF3/AIN13
  PF, // 24 PF4/AIN14/TCB0 PWM
  PF, // 25 PF5/AIN15/TCB1 PWM
  PF  // 26 PF6 RESET
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
  PIN7_bp, //  7 PA7/SS/CLKOUT/LED_BUILTIN
  PIN0_bp, //  8 PC0/USART1_Tx
  PIN1_bp, //  9 PC1/USART1_Rx
  PIN2_bp, // 10 PC2
  PIN3_bp, // 11 PC3
  PIN0_bp, // 12 PD0/AIN0
  PIN1_bp, // 13 PD1/AIN1
  PIN2_bp, // 14 PD2/AIN2
  PIN3_bp, // 15 PD3/AIN3
  PIN4_bp, // 16 PD4/AIN4
  PIN5_bp, // 17 PD5/AIN5
  PIN6_bp, // 18 PD6/AIN6
  PIN7_bp, // 19 PD7/AIN7/AREF
  PIN0_bp, // 20 PF0/USART2_Tx/TOSC1
  PIN1_bp, // 21 PF1/USART2_Rx/TOSC2
  PIN2_bp, // 22 PF2/AIN12
  PIN3_bp, // 23 PF3/AIN13
  PIN4_bp, // 24 PF4/AIN14/TCB0 PWM
  PIN5_bp, // 25 PF5/AIN15/TCB1 PWM
  PIN6_bp  // 26 PF6 RESET
};

/* Use this for accessing PINnCTRL register */
const uint8_t digital_pin_to_bit_mask[] = {
  PIN0_bm, //  0 PA0/USART0_Tx/CLKIN
  PIN1_bm, //  1 PA1/USART0_Rx
  PIN2_bm, //  2 PA2/SDA
  PIN3_bm, //  3 PA3/SCL
  PIN4_bm, //  4 PA4/MOSI
  PIN5_bm, //  5 PA5/MISO
  PIN6_bm, //  6 PA6/SCK
  PIN7_bm, //  7 PA7/SS/CLKOUT/LED_BUILTIN
  PIN0_bm, //  8 PC0/USART1_Tx
  PIN1_bm, //  9 PC1/USART1_Rx
  PIN2_bm, // 10 PC2
  PIN3_bm, // 11 PC3
  PIN0_bm, // 12 PD0/AIN0
  PIN1_bm, // 13 PD1/AIN1
  PIN2_bm, // 14 PD2/AIN2
  PIN3_bm, // 15 PD3/AIN3
  PIN4_bm, // 16 PD4/AIN4
  PIN5_bm, // 17 PD5/AIN5
  PIN6_bm, // 18 PD6/AIN6
  PIN7_bm, // 19 PD7/AIN7/AREF
  PIN0_bm, // 20 PF0/USART2_Tx/TOSC1
  PIN1_bm, // 21 PF1/USART2_Rx/TOSC2
  PIN2_bm, // 22 PF2/AIN12
  PIN3_bm, // 23 PF3/AIN13
  PIN4_bm, // 24 PF4/AIN14/TCB0 PWM
  PIN5_bm, // 25 PF5/AIN15/TCB1 PWM
  PIN6_bm  // 26 PF6 RESET
};

const uint8_t digital_pin_to_timer[] = {
  NOT_ON_TIMER, //  0 PA0/USART0_Tx/CLKIN
  NOT_ON_TIMER, //  1 PA1/USART0_Rx
#if !defined(MILLIS_USE_TIMERB0)
  TIMERB0,      //  2 PA2/SDA
#else
  NOT_ON_TIMER, //  2 PA2/SDA
#endif
#if !defined(MILLIS_USE_TIMERB1)
  TIMERB1,      //  3 PA3/SCL
#else
  NOT_ON_TIMER, //  3 PA3/SCL
#endif
  NOT_ON_TIMER, //  4 PA4/MOSI
  NOT_ON_TIMER, //  5 PA5/MISO
  NOT_ON_TIMER, //  6 PA6/SCK
  NOT_ON_TIMER, //  7 PA7/SS/CLKOUT/LED_BUILTIN
#if !defined(MILLIS_USE_TIMERB2)
  TIMERB2,      //  8 PC0/USART1_Tx
#else
  NOT_ON_TIMER, //  8 PC0/USART1_Tx
#endif
  NOT_ON_TIMER, //  9 PC1/USART1_Rx
  NOT_ON_TIMER, // 10 PC2/
  NOT_ON_TIMER, // 11 PC3/
  TIMERA0,      // 12 PD0/AIN0
  TIMERA0,      // 13 PD1/AIN1
  TIMERA0,      // 14 PD2/AIN2
  TIMERA0,      // 15 PD3/AIN3
  TIMERA0,      // 16 PD4/AIN4
  TIMERA0,      // 17 PD5/AIN5
  NOT_ON_TIMER, // 18 PD6/AIN6
  NOT_ON_TIMER, // 19 PD7/AIN7/AREF
  NOT_ON_TIMER, // 20 PF0/USART2_Tx/TOSC1
  NOT_ON_TIMER, // 21 PF1/USART2_Rx/TOSC2
  NOT_ON_TIMER, // 22 PF2/AIN12
  NOT_ON_TIMER, // 23 PF3/AIN13
  NOT_ON_TIMER, // 24 PF4/AIN14
  NOT_ON_TIMER, // 25 PF5/AIN15
  NOT_ON_TIMER  // 26 PF6 RESET
};

#endif

void initVariant() __attribute__((weak));
void initVariant() { }

#endif
