// This file will be optimized away if attachInterrupt or detachInterrupt isn't used in
// user program, thanks to dot_a_linkage set in library.properties

#include "Comparator.h"

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
