#include "Comparator.h"

AnalogComparator Comparator(0, AC0);

// Array for storing ISR function pointers
#if defined(AC2_AC_vect)
static volatile voidFuncPtr intFuncAC[3];
#elif defined(AC1_AC_vect)
static volatile voidFuncPtr intFuncAC[2];
#elif defined(AC0_AC_vect)
static volatile voidFuncPtr intFuncAC[1];
#else
#error target does not have an analog comparator!
#endif


AnalogComparator::AnalogComparator(const uint8_t comp_number, AC_t& ac) : comparator_number(comp_number), AC(ac)     
{
}

void AnalogComparator::init()
{
  // Set voltage reference
  if(reference != ref::disable)
  {
    VREF.CTRLA = (VREF.CTRLA & ~VREF_AC0REFSEL_AVDD_gc) | reference;
    VREF.CTRLB = VREF_AC0REFEN_bm;
  }
  else
    VREF.CTRLB &= ~VREF_AC0REFEN_bm;

  // Set DACREF
  AC.DACREF = dacref;

  // Set hysteresis
  AC.CTRLA = (AC.CTRLA & ~AC_HYSMODE_gm) | hysteresis;
  
  // Set inputs
  if(input_p == in_p::in0)
    PORTD.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_p == in_p::in1)
    PORTD.PIN4CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_p == in_p::in2)
    PORTD.PIN6CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_p == in_p::in3)
    PORTD.PIN1CTRL = PORT_ISC_INPUT_DISABLE_gc;
  if(input_n == in_n::in0)
    PORTD.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_n == in_n::in1)
    PORTD.PIN5CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_n == in_n::in2)
    PORTD.PIN7CTRL = PORT_ISC_INPUT_DISABLE_gc;
  AC.MUXCTRLA = (AC.MUXCTRLA & ~0x1B) | (input_p << 3) | input_n;

  // Set output
  if(output == out::enable)
  {
    AC.MUXCTRLA &= ~out::invert;
    AC.CTRLA |= out::enable;
    PORTA.DIRSET = PIN7_bm;
  }
  else if(output == out::invert)
  {
    AC.MUXCTRLA |= out::invert;
    AC.CTRLA |= out::enable;
    PORTA.DIRSET = PIN7_bm;
  }
  else if(output == out::disable)
  {
    AC.MUXCTRLA &= ~out::invert;
    AC.CTRLA &= ~out::enable;
    PORTA.DIRCLR = PIN7_bm;
  }
}

void AnalogComparator::start(bool state)
{
  if(state)
    AC.CTRLA |= AC_ENABLE_bm;
  else
    AC.CTRLA &= ~AC_ENABLE_bm;
}

void AnalogComparator::stop()
{
  start(false);
}

void AnalogComparator::attachInterrupt(void (*userFunc)(void), uint8_t mode)
{
  AC_INTMODE_t intmode;
  switch (mode) 
  {
    // Set RISING, FALLING or CHANGE interrupt trigger for the comparator output
    case RISING:
      intmode = AC_INTMODE_POSEDGE_gc;
      break;
    case FALLING:
      intmode = AC_INTMODE_NEGEDGE_gc;
      break;
    case CHANGE:
      intmode = AC_INTMODE_BOTHEDGE_gc;
      break;
    default:
      // Only RISING, FALLING and CHANGE is supported
      return;
  }
  AC.CTRLA = (AC.CTRLA & ~AC_INTMODE_POSEDGE_gc) | intmode;
  
  // Store function pointer
  intFuncAC[comparator_number] = userFunc;
  
  // Enable interrupt
  AC.INTCTRL |= AC_CMP_bm;
}

void AnalogComparator::detachInterrupt()
{
  // Disable interrupt
  AC.INTCTRL &= ~AC_CMP_bm;
}

#ifdef AC0_AC_vect
ISR(AC0_AC_vect)
{
  // Run user function
  intFuncAC[0]();
  
  // Clear flag
  AC0.STATUS = AC_CMP_bm;
}
#endif

#ifdef AC1_AC_vect
ISR(AC1_AC_vect)
{
  // Run user function
  intFuncAC[1]();
  
  // Clear flag
  AC1.STATUS = AC_CMP_bm;
}
#endif

#ifdef AC2_AC_vect
ISR(AC2_AC_vect)
{
  // Run user function
  intFuncAC[2]();
  
  // Clear flag
  AC2.STATUS = AC_CMP_bm;
}
#endif
