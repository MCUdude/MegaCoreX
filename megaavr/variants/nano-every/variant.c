#include <stdbool.h>

#include "pins_arduino.h"
#include "api/Common.h"

#define FORCE_INLINE __attribute__((always_inline)) inline

void setup_timers() {

  //  TYPE A TIMER  

  // PORTMUX setting for TCA -> all outputs [0:2] point to PORTB pins [0:2]
  PORTMUX.TCAROUTEA  = PORTMUX_TCA0_PORTB_gc;

  // Enable split mode before anything else
  TCA0.SPLIT.CTRLD = TCA_SINGLE_SPLITM_bm;

  // Period setting, two 8 bit registers
  TCA0.SPLIT.LPER =
  TCA0.SPLIT.HPER = PWM_TIMER_PERIOD;

  // Default duty 50%, will re-assign in analogWrite()
  TCA0.SPLIT.LCMP0 =
  TCA0.SPLIT.LCMP1 =
  TCA0.SPLIT.LCMP2 =
  TCA0.SPLIT.HCMP0 =
  TCA0.SPLIT.HCMP1 =
  TCA0.SPLIT.HCMP2 = PWM_TIMER_COMPARE;

#if F_CPU <= 1000000L
  // Use DIV4 prescaler (giving 250kHz clock), enable TCA timer
  TCA0.SPLIT.CTRLA = (TCA_SPLIT_CLKSEL_DIV4_gc) | (TCA_SPLIT_ENABLE_bm);
#elif F_CPU <= 2000000L
  // Use DIV8 prescaler (giving 250kHz clock), enable TCA timer
  TCA0.SPLIT.CTRLA = (TCA_SPLIT_CLKSEL_DIV8_gc) | (TCA_SPLIT_ENABLE_bm);
#elif F_CPU <= 8000000L
  // Use DIV16 prescaler (giving 250kHz clock), enable TCA timer
  TCA0.SPLIT.CTRLA = (TCA_SPLIT_CLKSEL_DIV16_gc) | (TCA_SPLIT_ENABLE_bm);
#else
  // Use DIV64 prescaler (giving 250kHz clock), enable TCA timer
  TCA0.SPLIT.CTRLA = (TCA_SPLIT_CLKSEL_DIV64_gc) | (TCA_SPLIT_ENABLE_bm);
#endif

  //  TYPE B TIMERS 
  
  // Setup TCB0 routing
  #if defined(TCB0)
    PORTMUX.TCBROUTEA |= PORTMUX_TCB0_bm; // Route signal to PF4
  #endif
  
  // Setup TCB1 routing
  #if defined(TCB1)
    PORTMUX.TCBROUTEA  |= PORTMUX_TCB1_bm; // Route signal to PF5
  #endif

  // Start with TCB0
  TCB_t *timer_B = (TCB_t *)&TCB0;
  
  // Find end timer
  #if defined(TCB3)
    TCB_t *timer_B_end = (TCB_t *)&TCB3;
  #elif defined(TCB2)
    TCB_t *timer_B_end = (TCB_t *)&TCB2;
  #elif defined(TCB1)
    TCB_t *timer_B_end = (TCB_t *)&TCB1;
  #else
    TCB_t *timer_B_end = (TCB_t *)&TCB0;
  #endif

  // Timer B Setup loop for TCB[0:3]
  do
  {
    // 8 bit PWM mode, but do not enable output yet, will do in analogWrite()
    timer_B->CTRLB = (TCB_CNTMODE_PWM8_gc);

    // Assign 8-bit period
    timer_B->CCMPL = PWM_TIMER_PERIOD;

    // default duty 50%, set when output enabled
    timer_B->CCMPH = PWM_TIMER_COMPARE;

    // Use TCA clock (250kHz) and enable
    // (sync update commented out, might try to synchronize later
    timer_B->CTRLA = (TCB_CLKSEL_CLKTCA_gc)
            //|(TCB_SYNCUPD_bm)
            |(TCB_ENABLE_bm);

    // Increment pointer to next TCB instance
    timer_B++;

  // Stop when pointing to TCB3
  } while (timer_B <= timer_B_end);

  // Stuff for synchronizing PWM timers
//   // Restart TCA to sync TCBs
//   // should not be needed   
//   TCA0.SINGLE.CTRLESET = TCA_SINGLE_CMD_RESTART_gc;
//   TCA0.SINGLE.CTRLECLR = TCA_SINGLE_CMD_RESTART_gc;
//
//   timer_B = (TCB_t *)&TCB0;
//
//   // TCB are sync to TCA, remove setting 
//   for (uint8_t digitial_pin_timer = (TIMERB0 - TIMERB0);
//   digitial_pin_timer < (TIMERB3 - TIMERB0);
//   digitial_pin_timer++)
//   {
//     // disable sync with tca
//     timer_B->CTRLA &= ~ (TCB_SYNCUPD_bm);
//
//     // Add offset to register 
//     timer_B++;
//
//   }
}

void initVariant() {
}