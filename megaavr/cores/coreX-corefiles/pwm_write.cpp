#include "Arduino.h"
#include "pins_arduino.h"
#include "wiring_private.h"

void pwmWrite(pwm_timers_t pwmTimer, uint16_t val, timers_route_t timerRoute) {
  // Set PORTMUX to route PWM to the correct pin
  if (timerRoute != ROUTE_UNTOUCHED) {
    if(timerRoute & 0x40)
      PORTMUX.TCAROUTEA = timerRoute & 0x07;
    else {
      uint8_t tcb_index = (timerRoute >> 4) & 0x03;
      uint8_t route_bit = timerRoute & 0x01;
      uint8_t mask = (1 << tcb_index);
      if(route_bit)
        PORTMUX.TCBROUTEA |= mask;
      else
        PORTMUX.TCBROUTEA &= ~mask;
    }
  }

  // Find corresponding IO pin based on pwmTimer
  uint8_t route = 0;
  uint8_t pin_bp = 0;
  uint8_t d_max = 0;
  VPORT_t *vport;
  if(pwmTimer <= TCA0_5) {
    route  = PORTMUX.TCAROUTEA;
    pin_bp = pwmTimer;
    vport  = &VPORTA + route;
    d_max  = TCA0.SPLIT.LPER;
  } else if(pwmTimer == TCB_0) {
    route  = PORTMUX.TCBROUTEA & 0x01;
    pin_bp = route? PIN4_bp: PIN2_bp;
    vport  = route? &VPORTF: &VPORTA;
    d_max  = TCB0.CCMPL;
  } else if(pwmTimer == TCB_1) {
    route  = PORTMUX.TCBROUTEA & 0x02;
    pin_bp = route? PIN5_bp: PIN3_bp;
    vport  = route? &VPORTF: &VPORTA;
    d_max  = TCB1.CCMPL;
  } else if(pwmTimer == TCB_2) {
    route  = PORTMUX.TCBROUTEA & 0x04;
    pin_bp = route? PIN4_bp: PIN0_bp;
    vport  = route? &VPORTB: &VPORTC;
    d_max  = TCB2.CCMPL;
  } else if(pwmTimer == TCB_3) {
    route  = PORTMUX.TCBROUTEA & 0x08;
    pin_bp = route? PIN1_bp: PIN5_bp;
    vport  = route? &VPORTC: &VPORTB;
    d_max  = TCB3.CCMPL;
  } else {
    return;
  }

  // Set IO pin as output
  vport->DIR |= (1<<pin_bp);
  
  TCB_t *timer_B;
  if(val <= 0 || val > d_max) {
    // Turn off PWM
    uint8_t bitpos = pin_bp;
    switch (pwmTimer) {
      case TCA0_0...TCA0_5:
        if (bitpos >= 3) ++bitpos; // Upper 3 bits are shifted by 1
        TCA0.SPLIT.CTRLB &= ~(1 << (TCA_SPLIT_LCMP0EN_bp + bitpos));
        break;

      case TCB_0:
      case TCB_1:
      case TCB_2:
      case TCB_3:
        timer_B = &TCB0 + (pwmTimer-TCB_0);
        timer_B->CTRLB &= ~(TCB_CCMPEN_bm);
        break;

      default:
        break;
    }
    // Set pin high or low
    if(val <= 0)
      vport->OUT &= ~(1<<pin_bp);
    else
      vport->OUT |= (1<<pin_bp);
  }

  // Turn on PWM using the correct timer
  else {
    uint8_t savedSREG = SREG;
    uint8_t *timer_cmp_out;

    switch (pwmTimer) {
      case TCA0_0...TCA0_5:
        if (pin_bp >= 3) {
          timer_cmp_out = ((uint8_t *)(&TCA0.SPLIT.HCMP0)) + 2*(pin_bp-3);
          ++pin_bp;
        } else {
          timer_cmp_out = ((uint8_t *)(&TCA0.SPLIT.LCMP0)) + 2*pin_bp;
        }
        cli();
        *timer_cmp_out = val;
        SREG = savedSREG;
        TCA0.SPLIT.CTRLB |= (1 << (TCA_SPLIT_LCMP0EN_bp + pin_bp));
        break;

      case TCB_0:
      case TCB_1:
      case TCB_2:
      case TCB_3:
        timer_B = &TCB0 + (pwmTimer-TCB_0);
        savedSREG = SREG;
        cli();
        timer_B->CCMPL = timer_B->CCMPL;
        timer_B->CCMPH = val;
        SREG = savedSREG;
        timer_B->CTRLB |= (TCB_CCMPEN_bm);
        break;
    }
  }
}

void pwmPrescaler(pwm_timers_t pwmTimer, timers_prescaler_t prescaler) {
  if(pwmTimer <= TCA0_5)
    TCA0.SPLIT.CTRLA = prescaler | TCA_SPLIT_ENABLE_bm;
  else {
    TCB_t *timer_B = &TCB0 + (pwmTimer-TCB_0);
    uint8_t p = (prescaler >> 4) & TCB_CLKSEL_gm;
    timer_B->CTRLA = ((timer_B->CTRLA & ~TCB_CLKSEL_gm) | p);
  }
}

void pwmSetResolution(pwm_timers_t pwmTimer, uint8_t maxValue) {
  // The max value will disable PWM and set pin high
  uint8_t top = maxValue? maxValue-1: 1;

  if(pwmTimer <= TCA0_5) {
    TCA0.SPLIT.LPER =
      TCA0.SPLIT.HPER = top;
    TCA0.SPLIT.LCMP0 =
      TCA0.SPLIT.LCMP1 =
        TCA0.SPLIT.LCMP2 =
          TCA0.SPLIT.HCMP0 =
            TCA0.SPLIT.HCMP1 =
              TCA0.SPLIT.HCMP2 = top >> 1;
  } else {
    TCB_t *timer_B = &TCB0 + (pwmTimer-TCB_0);
    timer_B->CCMPL = top;
    timer_B->CCMPH = top >> 1;
  }
    
}