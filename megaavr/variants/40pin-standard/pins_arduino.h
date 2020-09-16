/****************************************************|
|               40-PIN STANDARD PINOUT               |
|       https://github.com/MCUdude/MegaCoreX         |
|                                                    |
| COMPATIBLE WITH:                                   |
| ATmega4809                                         |
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

#define MEGACOREX_DEFAULT_40PIN_PINOUT
#define __AVR_ATmegax09__

// Pin macros
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
#define PIN_PC4 12
#define PIN_PC5 13
#define PIN_PD0 14
#define PIN_PD1 15
#define PIN_PD2 16
#define PIN_PD3 17
#define PIN_PD4 18
#define PIN_PD5 19
#define PIN_PD6 20
#define PIN_PD7 21
#define PIN_PE0 22
#define PIN_PE1 23
#define PIN_PE2 24
#define PIN_PE3 25
#define PIN_PF0 26
#define PIN_PF1 27
#define PIN_PF2 28
#define PIN_PF3 29
#define PIN_PF4 30
#define PIN_PF5 31
#define PIN_PF6 32

#define PINS_COUNT                     33
#define NUM_DIGITAL_PINS               PINS_COUNT
#define NUM_ANALOG_INPUTS              16
#define NUM_RESERVED_PINS              0
#define NUM_INTERNALLY_USED_PINS       0
#define NUM_I2C_PINS                   2
#define NUM_SPI_PINS                   3
#define NUM_TOTAL_FREE_PINS            PINS_COUNT
#define NUM_TOTAL_PINS                 PINS_COUNT
#define ANALOG_INPUT_OFFSET            14
#define LED_BUILTIN                    PIN_PA7
#define EXTERNAL_NUM_INTERRUPTS        47
#define digitalPinToAnalogInput(p)     ((p < NUM_ANALOG_INPUTS) ? (p) : ((p) >= PIN_PD0 && (p) <= PIN_PE3) ? ((p) - ANALOG_INPUT_OFFSET) : ((p) >= PIN_PF2 && (p) <= PIN_PF5) ? ((p) - 2 - ANALOG_INPUT_OFFSET) : NOT_A_PIN)
#define digitalOrAnalogPinToDigital(p) ((p <= 11) ? ((p) + ANALOG_INPUT_OFFSET) : ((p) <= 15) ? ((p) + ANALOG_INPUT_OFFSET + 2) : (((p) >= 26 && (p) <= 31)) ? (p) :  NOT_A_PIN)

// Timer to use for millis/micros
#if !defined(MILLIS_USE_TIMERB0) || !defined(MILLIS_USE_TIMERB1) || !defined(MILLIS_USE_TIMERB2) || !defined(MILLIS_USE_TIMERB3)
#define MILLIS_USE_TIMERB2 // Use TCB2 for millis generation
#endif

// PWM pins
#if defined(MILLIS_USE_TIMERB0)
  #define digitalPinHasPWM(p)  (((p) == PIN_PC0) || ((p) == PIN_PC1) || ((p) == PIN_PC2) || ((p) == PIN_PC3) || \
                                ((p) == PIN_PC4) || ((p) == PIN_PC5) || ((p) == PIN_PF5))
#elif defined(MILLIS_USE_TIMERB1)
  #define digitalPinHasPWM(p)  (((p) == PIN_PC0) || ((p) == PIN_PC1) || ((p) == PIN_PC2) || ((p) == PIN_PC3) || \
                                ((p) == PIN_PC4) || ((p) == PIN_PC5) || ((p) == PIN_PF4))
#elif defined(MILLIS_USE_TIMERB2)
  #define digitalPinHasPWM(p)  (((p) == PIN_PC0) || ((p) == PIN_PC1) || ((p) == PIN_PC2) || ((p) == PIN_PC3) || \
                                ((p) == PIN_PC4) || ((p) == PIN_PC5) || ((p) == PIN_PF4) || ((p) == PIN_PF5))
#else // default to MILLIS_USE_TIMERB3
  #define digitalPinHasPWM(p)  (((p) == PIN_PC0) || ((p) == PIN_PC1) || ((p) == PIN_PC2) || ((p) == PIN_PC3) || \
                                ((p) == PIN_PC4) || ((p) == PIN_PC5) || ((p) == PIN_PF4) || ((p) == PIN_PF5))
#endif

// Timer pin swaps
#define TCA0_PINS PORTMUX_TCA0_PORTC_gc // TCA0 output on PC[0:5]
#define TCB0_PINS PORTMUX_TCB0_bm       // TCB0 output on PF4 instead of PA2
#define TCB1_PINS PORTMUX_TCB1_bm       // TCB1 output on PF5 instead of PA3
#define TCB2_PINS PORTMUX_TCB2_bm       // TCB2 output on PB4 instead of PC0
#define TCB3_PINS 0x00                  // TCB3 output on PB5 instead of PC1

// SPI 0
// No pinswap enabled by default
// Pinswap 2 not available
#define SPI_INTERFACES_COUNT   1
#define SPI_MUX                PORTMUX_SPI0_DEFAULT_gc
#define SPI_MUX_PINSWAP_1      PORTMUX_SPI0_ALT1_gc
#define SPI_MUX_PINSWAP_2      PORTMUX_SPI0_ALT2_gc
#define PIN_SPI_MISO           PIN_PA5
#define PIN_SPI_SCK            PIN_PA6
#define PIN_SPI_MOSI           PIN_PA4
#define PIN_SPI_SS             PIN_PA7
#define PIN_SPI_MISO_PINSWAP_1 PIN_PC1
#define PIN_SPI_SCK_PINSWAP_1  PIN_PC2
#define PIN_SPI_MOSI_PINSWAP_1 PIN_PC0
#define PIN_SPI_SS_PINSWAP_1   PIN_PC3
#define PIN_SPI_MISO_PINSWAP_2 PIN_PE1
#define PIN_SPI_SCK_PINSWAP_2  PIN_PE2
#define PIN_SPI_MOSI_PINSWAP_2 PIN_PE0
#define PIN_SPI_SS_PINSWAP_2   PIN_PE3
static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

// TWI 0
// No pinswap enabled by default
#define TWI_MUX                PORTMUX_TWI0_DEFAULT_gc
#define TWI_MUX_PINSWAP        PORTMUX_TWI0_ALT2_gc
#define PIN_WIRE_SDA           PIN_PA2
#define PIN_WIRE_SCL           PIN_PA3
#define PIN_WIRE_SDA_PINSWAP_1 PIN_PC2
#define PIN_WIRE_SCL_PINSWAP_1 PIN_PC3
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// USART 0
// No pinswap by default
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
// No pinswap by default
#define HWSERIAL1                       &USART1
#define HWSERIAL1_DRE_VECTOR            USART1_DRE_vect
#define HWSERIAL1_DRE_VECTOR_NUM        USART1_DRE_vect_num
#define HWSERIAL1_RXC_VECTOR            USART1_RXC_vect
#define HWSERIAL1_MUX                   PORTMUX_USART1_DEFAULT_gc
#define HWSERIAL1_MUX_PINSWAP_1         PORTMUX_USART1_ALT1_gc
#define PIN_HWSERIAL1_TX                PIN_PC0
#define PIN_HWSERIAL1_RX                PIN_PC1
#define PIN_HWSERIAL1_XCK               PIN_PC2
#define PIN_HWSERIAL1_XDIR              PIN_PC3
#define PIN_HWSERIAL1_TX_PINSWAP_1      PIN_PC4
#define PIN_HWSERIAL1_RX_PINSWAP_1      PIN_PC5

// USART 2
// No pinswap by default
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
#define PIN_A8   PIN_PE0
#define PIN_A9   PIN_PE1
#define PIN_A10  PIN_PE2
#define PIN_A11  PIN_PE3
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
  PC, // 12 PC4
  PC, // 13 PC5
  PD, // 14 PD0/AIN0
  PD, // 15 PD1/AIN1
  PD, // 16 PD2/AIN2
  PD, // 17 PD3/AIN3
  PD, // 18 PD4/AIN4
  PD, // 19 PD5/AIN5
  PD, // 20 PD6/AIN6
  PD, // 21 PD7/AIN7/AREF
  PE, // 22 PE0/AIN8
  PE, // 23 PE1/AIN9
  PE, // 24 PE2/AIN10
  PE, // 25 PE3/AIN11
  PF, // 26 PF0/USART2_Tx/TOSC1
  PF, // 27 PF1/USART2_Rx/TOSC2
  PF, // 28 PF2/AIN12
  PF, // 29 PF3/AIN13
  PF, // 30 PF4/AIN14
  PF, // 31 PF5/AIN15
  PF  // 32 PF6 RESET
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
  PIN4_bp, // 12 PC4
  PIN5_bp, // 13 PC5
  PIN0_bp, // 14 PD0/AIN0
  PIN1_bp, // 15 PD1/AIN1
  PIN2_bp, // 16 PD2/AIN2
  PIN3_bp, // 17 PD3/AIN3
  PIN4_bp, // 18 PD4/AIN4
  PIN5_bp, // 19 PD5/AIN5
  PIN6_bp, // 20 PD6/AIN6
  PIN7_bp, // 21 PD7/AIN7/AREF
  PIN0_bp, // 22 PE0/AIN8
  PIN1_bp, // 23 PE1/AIN9
  PIN2_bp, // 24 PE2/AIN10
  PIN3_bp, // 25 PE3/AIN11
  PIN0_bp, // 26 PF0/USART2_Tx/TOSC1
  PIN1_bp, // 27 PF1/USART2_Rx/TOSC2
  PIN2_bp, // 28 PF2/AIN12
  PIN3_bp, // 29 PF3/AIN13
  PIN4_bp, // 30 PF4/AIN14
  PIN5_bp, // 31 PF5/AIN15
  PIN6_bp  // 42 PF6 RESET
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
  PIN7_bm, //  7 PA7/SS/CLKOUT/LED_BUILTIN
  PIN0_bm, //  8 PC0/USART1_Tx
  PIN1_bm, //  9 PC1/USART1_Rx
  PIN2_bm, // 10 PC2
  PIN3_bm, // 11 PC3
  PIN4_bm, // 12 PC4
  PIN5_bm, // 13 PC5
  PIN0_bm, // 14 PD0/AIN0
  PIN1_bm, // 15 PD1/AIN1
  PIN2_bm, // 16 PD2/AIN2
  PIN3_bm, // 17 PD3/AIN3
  PIN4_bm, // 18 PD4/AIN4
  PIN5_bm, // 19 PD5/AIN5
  PIN6_bm, // 20 PD6/AIN6
  PIN7_bm, // 21 PD7/AIN7/AREF
  PIN0_bm, // 22 PE0/AIN8
  PIN1_bm, // 23 PE1/AIN9
  PIN2_bm, // 24 PE2/AIN10
  PIN3_bm, // 25 PE3/AIN11
  PIN0_bm, // 26 PF0/USART2_Tx/TOSC1
  PIN1_bm, // 27 PF1/USART2_Rx/TOSC2
  PIN2_bm, // 28 PF2/AIN12
  PIN3_bm, // 29 PF3/AIN13
  PIN4_bm, // 30 PF4/AIN14
  PIN5_bm, // 31 PF5/AIN15
  PIN6_bm  // 32 PF6 RESET
};

const uint8_t digital_pin_to_timer[] = {
  NOT_ON_TIMER, //  0 PA0/USART0_Tx/CLKIN
  NOT_ON_TIMER, //  1 PA1/USART0_Rx
  NOT_ON_TIMER, //  2 PA2/SDA
  NOT_ON_TIMER, //  3 PA3/SCL
  NOT_ON_TIMER, //  4 PA4/MOSI
  NOT_ON_TIMER, //  5 PA5/MISO
  NOT_ON_TIMER, //  6 PA6/SCK
  NOT_ON_TIMER, //  7 PA7/SS/CLKOUT/LED_BUILTIN
  TIMERA0,      //  8 PC0/USART1_Tx
  TIMERA0,      //  9 PC1/USART1_Rx
  TIMERA0,      // 10 PC2
  TIMERA0,      // 11 PC3
  TIMERA0,      // 12 PC4
  TIMERA0,      // 13 PC5
  NOT_ON_TIMER, // 14 PD0/AIN0
  NOT_ON_TIMER, // 15 PD1/AIN1
  NOT_ON_TIMER, // 16 PD2/AIN2
  NOT_ON_TIMER, // 17 PD3/AIN3
  NOT_ON_TIMER, // 18 PD4/AIN4
  NOT_ON_TIMER, // 19 PD5/AIN5
  NOT_ON_TIMER, // 20 PD6/AIN6
  NOT_ON_TIMER, // 21 PD7/AIN7/AREF
  NOT_ON_TIMER, // 22 PE0/AIN8
  NOT_ON_TIMER, // 23 PE1/AIN9
  NOT_ON_TIMER, // 24 PE2/AIN10
  NOT_ON_TIMER, // 25 PE3/AIN11
  NOT_ON_TIMER, // 26 PF0/USART2_Tx/TOSC1
  NOT_ON_TIMER, // 27 PF1/USART2_Rx/TOSC2
  NOT_ON_TIMER, // 28 PF2/AIN12
  NOT_ON_TIMER, // 29 PF3/AIN13
#ifdef MILLIS_USE_TIMERB0
  NOT_ON_TIMER, // 30 PF4/AIN14
#else
  TIMERB0,      // 30 PF4/AIN14
#endif
#ifdef MILLIS_USE_TIMERB1
  NOT_ON_TIMER, // 31 PF5/AIN15
#else
  TIMERB1,      // 31 PF5/AIN15
#endif
  NOT_ON_TIMER  // 32 PF6 RESET
};

#endif

void initVariant() __attribute__((weak));
void initVariant()
{
  // Disable unavailable pins on the 40 pin package
  PORTB.PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTB.PIN1CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTB.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTB.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTB.PIN4CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTB.PIN5CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTC.PIN6CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTC.PIN6CTRL = PORT_ISC_INPUT_DISABLE_gc;
}

#endif
