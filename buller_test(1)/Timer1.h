#ifndef Timer1_h
#define Timer1_h

#include <avr/interrupt.h>

namespace Timer1 {
	extern unsigned long msecs1;
	extern void (*func1)();
	extern volatile unsigned long count1;
	extern volatile char overflowing1;
	extern volatile unsigned int tcnt1;
	
	void set(unsigned long us, void (*f)());
	void start();
	void stop();
	void _overflow();
}

#endif

