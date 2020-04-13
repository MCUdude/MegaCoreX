#ifndef __TIMERS_H__
#define __TIMERS_H__

// The assumption is that we have a 16 bit timer fully available for timing purposes.
#define TIME_TRACKING_TIMER_DIVIDER 1                                            // Timer F_CPU Clock divider (can be 1 or 2)
#define TIME_TRACKING_TIMER_COUNT (F_CPU / (1000 * TIME_TRACKING_TIMER_DIVIDER)) // Should correspond to exactly 1 ms, i.e. millis()

#define PWM_TIMER_PERIOD 0xFE  // For frequency
#define PWM_TIMER_COMPARE 0x80 // For duty cycle

#endif
