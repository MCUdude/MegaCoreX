/*
  wiring.c
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

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

  Substantially rewritten by Egil Kvaleberg, 23 Sep 2019, to
  use a dedicated 16 bit TSB timer for all timing purposes. This
  cleans up a lot of things, and makes the code much simpler and
  faster. The TCB timers have limitations making it impossible to
  use the same timer for both PWM and timing, so this is no loss.

*/

#include "wiring_private.h"

uint32_t F_CPU_CORRECTED = F_CPU;

volatile uint32_t timer_millis = 0;

inline uint16_t clockCyclesPerMicrosecondComp(uint32_t clk){
	return ( (clk) / 1000000L );
}

inline uint16_t clockCyclesPerMicrosecond(){
	return clockCyclesPerMicrosecondComp(F_CPU_CORRECTED);
}

inline unsigned long clockCyclesToMicroseconds(unsigned long cycles){
	return ( cycles / clockCyclesPerMicrosecond() );
}

inline unsigned long microsecondsToClockCycles(unsigned long microseconds){
	return ( microseconds * clockCyclesPerMicrosecond() );
}

static volatile TCB_t* _timer =
#if defined(MILLIS_USE_TIMERB0)
	&TCB0;
#elif defined(MILLIS_USE_TIMERB1)
	&TCB1;
#elif defined(MILLIS_USE_TIMERB2)
	&TCB2;
#else // fallback or defined(MILLIS_USE_TIMERB3)
	&TCB3; //TCB3 fallback
#endif

#if defined(MILLIS_USE_TIMERB0)
	ISR(TCB0_INT_vect)
#elif defined(MILLIS_USE_TIMERB1)
	ISR(TCB1_INT_vect)
#elif defined(MILLIS_USE_TIMERB2)
	ISR(TCB2_INT_vect)
#else // fallback or defined(MILLIS_USE_TIMERB3)
	ISR(TCB3_INT_vect)
#endif
{
	timer_millis++;

	/* Clear flag */
	_timer->INTFLAGS = TCB_CAPT_bm;
}

unsigned long millis()
{
	unsigned long m;

	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer_millis)
	uint8_t status = SREG;
	cli();

	m = timer_millis;

	SREG = status;

	return m;
}

unsigned long  micros() {
	uint32_t m;
	uint16_t t;

	/* Save current state and disable interrupts */
	uint8_t status = SREG;
	cli();

	/* Get current number of millis (i.e. overflows) and timer count */
	m = timer_millis;
	t = _timer->CNT;

	/* If the timer overflow flag is raised, we just missed it,
	increment to account for it, & read new ticks */
	if(_timer->INTFLAGS & TCB_CAPT_bm){
		m++;
		t = _timer->CNT;
	}

	// Restore SREG
	SREG = status;

	return (m * 1000L) + (t / (TIME_TRACKING_TIMER_COUNT / 1000));
}

void delay(unsigned long ms)
{
	uint32_t start_time = micros(), delay_time = 1000*ms;

	/* Calculate future time to return */
	uint32_t return_time = start_time + delay_time;

	/* If return time overflows */
	if(return_time < delay_time){
		/* Wait until micros overflows */
		while(micros() > return_time);
	}

	/* Wait until return time */
	while(micros() < return_time);
}

/* Delay for the given number of microseconds.  Assumes a 1, 8, 12, 16, 20 or 24 MHz clock. */
// BUG: should really be implemented using _timer instead!!!!!!!!!!
void delayMicroseconds(unsigned int us)
{
	// call = 4 cycles + 2 to 4 cycles to init us(2 for constant delay, 4 for variable)

	// calling avrlib's delay_us() function with low values (e.g. 1 or
	// 2 microseconds) gives delays longer than desired.
	//delay_us(us);
#if F_CPU >= 24000000L
	// for the 24 MHz clock for the aventurous ones, trying to overclock

	// zero delay fix
	if (!us) return; //  = 3 cycles, (4 when true)

	// the following loop takes a 1/6 of a microsecond (4 cycles)
	// per iteration, so execute it six times for each microsecond of
	// delay requested.
	us *= 6; // x6 us, = 7 cycles

	// account for the time taken in the preceeding commands.
	// we just burned 22 (24) cycles above, remove 5, (5*4=20)
	// us is at least 6 so we can substract 5
	us -= 5; //=2 cycles

#elif F_CPU >= 20000000L
	// for the 20 MHz clock on rare Arduino boards

	// for a one-microsecond delay, simply return.  the overhead
	// of the function call takes 18 (20) cycles, which is 1us
	__asm__ __volatile__ (
		"nop" "\n\t"
		"nop" "\n\t"
		"nop" "\n\t"
		"nop"); //just waiting 4 cycles
	if (us <= 1) return; //  = 3 cycles, (4 when true)

	// the following loop takes a 1/5 of a microsecond (4 cycles)
	// per iteration, so execute it five times for each microsecond of
	// delay requested.
	us = (us << 2) + us; // x5 us, = 7 cycles

	// account for the time taken in the preceeding commands.
	// we just burned 26 (28) cycles above, remove 7, (7*4=28)
	// us is at least 10 so we can substract 7
	us -= 7; // 2 cycles

#elif F_CPU >= 16000000L
	// for the 16 MHz clock on most Arduino boards

	// for a one-microsecond delay, simply return.  the overhead
	// of the function call takes 14 (16) cycles, which is 1us
	if (us <= 1) return; //  = 3 cycles, (4 when true)

	// the following loop takes 1/4 of a microsecond (4 cycles)
	// per iteration, so execute it four times for each microsecond of
	// delay requested.
	us <<= 2; // x4 us, = 4 cycles

	// account for the time taken in the preceeding commands.
	// we just burned 19 (21) cycles above, remove 5, (5*4=20)
	// us is at least 8 so we can substract 5
	us -= 5; // = 2 cycles,

#elif F_CPU >= 12000000L
	// for the 12 MHz clock if somebody is working with USB

	// for a 1 microsecond delay, simply return.  the overhead
	// of the function call takes 14 (16) cycles, which is 1.5us
	if (us <= 1) return; //  = 3 cycles, (4 when true)

	// the following loop takes 1/3 of a microsecond (4 cycles)
	// per iteration, so execute it three times for each microsecond of
	// delay requested.
	us = (us << 1) + us; // x3 us, = 5 cycles

	// account for the time taken in the preceeding commands.
	// we just burned 20 (22) cycles above, remove 5, (5*4=20)
	// us is at least 6 so we can substract 5
	us -= 5; //2 cycles

#elif F_CPU >= 8000000L
	// for the 8 MHz internal clock

	// for a 1 and 2 microsecond delay, simply return.  the overhead
	// of the function call takes 14 (16) cycles, which is 2us
	if (us <= 2) return; //  = 3 cycles, (4 when true)

	// the following loop takes 1/2 of a microsecond (4 cycles)
	// per iteration, so execute it twice for each microsecond of
	// delay requested.
	us <<= 1; //x2 us, = 2 cycles

	// account for the time taken in the preceeding commands.
	// we just burned 17 (19) cycles above, remove 4, (4*4=16)
	// us is at least 6 so we can substract 4
	us -= 4; // = 2 cycles

#elif F_CPU >= 4000000L
  // The overhead of the function call is 14 (16) cycles which is 4 us
  if (us <= 2)
    return;

  // Subtract microseconds that were wasted in this function
  us -= 2;

  // We don't need to multiply here because one request microsecond is exactly one loop cycle

#elif F_CPU >= 2000000L
  // The overhead of the function call is 14 (16) cycles which is 8.68 us
  // Plus the if-statement that takes 3 cycles (4 when true): ~11us
  if (us <= 13)
    return;

  // Subtract microseconds that were wasted in this function
  us -= 11; // 2 cycles

  us = (us >> 1); // 3 cycles

#else
	// for the 1 MHz internal clock (default settings for common Atmega microcontrollers)

	// the overhead of the function calls is 14 (16) cycles
	if (us <= 16) return; //= 3 cycles, (4 when true)
	if (us <= 25) return; //= 3 cycles, (4 when true), (must be at least 25 if we want to substract 22)

	// compensate for the time taken by the preceeding and next commands (about 22 cycles)
	us -= 22; // = 2 cycles
	// the following loop takes 4 microseconds (4 cycles)
	// per iteration, so execute it us/4 times
	// us is at least 4, divided by 4 gives us 1 (no zero delay bug)
	us >>= 2; // us div 4, = 4 cycles


#endif

	// busy wait
	__asm__ __volatile__ (
		"1: sbiw %0,1" "\n\t" // 2 cycles
		"brne 1b" : "=w" (us) : "0" (us) // 2 cycles
	);
	// return = 4 cycles
}

void init()
{
	// this needs to be called before setup() or some functions won't
	// work there
	
/******************************** CLOCK STUFF *********************************/

 	// Use external oscillator if already defined (in boards.txt, platformio.ini)
 	#if defined(USE_EXTERNAL_OSCILLATOR)
		_PROTECTED_WRITE(CLKCTRL_MCLKCTRLA, CLKCTRL_CLKSEL_EXTCLK_gc);
		_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0x00); // Fallback to 16 MHz internal if no EXTCLK
		
	// Use internal oscillator if not defined. No need to manipulate the MCLKCTRLA register here
	// because it's already done in the SYSCFG0 fuse byte
	#else 	
		#if (F_CPU == 20000000L)		
			/* No division on clock */
			_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0x00);
		#elif (F_CPU == 16000000L)		
			/* No division on clock */
			_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0x00);		
		#elif (F_CPU == 8000000L)		
			/* Clock DIV2 */
			_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_2X_gc));		
		#elif (F_CPU == 4000000L)		
			/* Clock DIV4 */
			_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_4X_gc));
		#elif (F_CPU == 2000000L)		
			/* Clock DIV8 */
			_PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, (CLKCTRL_PEN_bm | CLKCTRL_PDIV_8X_gc));
		#endif
	#endif

/********************************* ADC ****************************************/

#if defined(ADC0)

	/* ADC clock between 50-200 kHz */

	#if (F_CPU >= 20000000L)   // 20 MHz / 128 = 156.250 kHz
		ADC0.CTRLC |= ADC_PRESC_DIV128_gc;
	#elif (F_CPU >= 16000000L) // 16 MHz / 128 = 125 kHz
		ADC0.CTRLC |= ADC_PRESC_DIV128_gc;
	#elif (F_CPU >= 8000000L)  // 8 MHz / 64 = 125 kHz
		ADC0.CTRLC |= ADC_PRESC_DIV64_gc;
	#elif (F_CPU >= 4000000L)  // 4 MHz / 32 = 125 kHz
		ADC0.CTRLC |= ADC_PRESC_DIV32_gc;
	#elif (F_CPU >= 2000000L)  // 2 MHz / 16 = 125 kHz
		ADC0.CTRLC |= ADC_PRESC_DIV16_gc;
	#elif (F_CPU >= 1000000L)  // 1 MHz / 8 = 125 kHz
		ADC0.CTRLC |= ADC_PRESC_DIV8_gc;
	#else // 128 kHz / 2 = 64 kHz -> This is the closest you can get, the prescaler is 2
		ADC0.CTRLC |= ADC_PRESC_DIV2_gc;
	#endif

	/* Enable ADC */
	ADC0.CTRLA |= ADC_ENABLE_bm;
	analogReference(VDD);

#endif

	PORTMUX.USARTROUTEA = 0;

	setup_timers();

	/********************* TCB for system time tracking **************************/

	// BUG: we can compensate for F_CPU_CORRECTED by fine tuning value of TIME_TRACKING_TIMER_COUNT

	/* Select vanilla 16 bit periodic interrupt mode */
	_timer->CTRLB = TCB_CNTMODE_INT_gc;

	/* TOP value for overflow every N clock cycles */
	_timer->CCMP = TIME_TRACKING_TIMER_COUNT - 1;

	/* Enable TCB interrupt */
	_timer->INTCTRL |= TCB_CAPT_bm;

	/* Clock selection is F_CPU/N -- which is independent of TCA */
#if TIME_TRACKING_TIMER_DIVIDER==1
	_timer->CTRLA = TCB_CLKSEL_CLKDIV1_gc; /* F_CPU */
#elif TIME_TRACKING_TIMER_DIVIDER==2
	_timer->CTRLA = TCB_CLKSEL_CLKDIV2_gc; /* F_CPU/2 */
#else
#assert "TIME_TRACKING_TIMER_DIVIDER not supported"
#endif

	/* Enable & start */
	_timer->CTRLA |= TCB_ENABLE_bm;	/* Keep this last before enabling interrupts to ensure tracking as accurate as possible */

/*************************** ENABLE GLOBAL INTERRUPTS *************************/

	sei();
}

void setup_timers(void)  __attribute__((weak));
