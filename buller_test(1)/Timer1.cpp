#include "Timer1.h"

unsigned long Timer1::msecs1;
void (*Timer1::func1)();
volatile unsigned long Timer1::count1;
volatile char Timer1::overflowing1;
volatile unsigned int Timer1::tcnt1;

void Timer1::set(unsigned long us, void (*f)()) {
	float prescaler1 = 0.0;
	
	TIMSK1 &= ~(1<<TOIE1);
	TCCR1A &= ~(1<<WGM11);
	TCCR1A &= ~(1<<WGM10);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	TCCR1B &= ~0x07;
	
	if(us<10){
		prescaler1 = 1.0;
		TCCR1B |=0x01;
		tcnt1 =  0xffff - (int)((float)F_CPU * 0.000001);
	}
	else if(us<500){
		prescaler1 = 8.0;
		TCCR1B |=0x02;
		if(us%100 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.0001/prescaler1);
			us /=100;
		}
		else if(us%50 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.00005/prescaler1);
			us /=50;
		}
		else if(us%20 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.00002/prescaler1);
			us /=20;
		}
		else if(us%10 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.00001/prescaler1);
			us /=10;
		}
		else
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.000001/prescaler1);
		}
	}
	else if(us<2000){
		prescaler1 = 64.0;
		TCCR1B |=0x03;
		if(us%200 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.0002/prescaler1);
			us /=200;
		}
		else if(us%100 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.0001/prescaler1);
			us /=100;
		}
		else if(us%50 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.00005/prescaler1);
			us /=50;
		}
		else if(us%20 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.00002/prescaler1);
			us /=20;
		}
		else
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.00001/prescaler1);
			us /=10;
		}
	}
	else{
		prescaler1 = 256.0;
		TCCR1B |=0x04;
		if(us%4000 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.004/prescaler1);
			us /=4000;
		}
		else if(us%2000 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.002/prescaler1);
			us /=2000;
		}
		else if(us%1000 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.001/prescaler1);
			us /=1000;
		}
		else if(us%500 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.0005/prescaler1);
			us /=500;
		}
		else if(us%200 == 0)
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.0002/prescaler1);
			us /=200;
		}
		else
		{
			tcnt1 =  0xffff - (int)((float)F_CPU * 0.0001/prescaler1);
			us /=100;
		}
	}
	
	if (us == 0)
		msecs1 = 1;
	else
		msecs1 = us;
		
	func1 = f;
}

void Timer1::start() {
	count1 = 0;
	overflowing1 = 0;
	TCNT1L = Timer1::tcnt1 & 0xFF;
	TCNT1H = Timer1::tcnt1 >> 8;
	TIMSK1 |= (1<<TOIE1);
}

void Timer1::stop() {
	TIMSK1 &= ~(1<<TOIE1);
}

void Timer1::_overflow() {
	count1++;
	
	if (count1 >= msecs1 && !overflowing1) {
		overflowing1 = 1;
		count1 = 0;
		(*func1)();
		overflowing1 = 0;
	}
}

ISR(TIMER1_OVF_vect) {
	TCNT1L = Timer1::tcnt1 & 0xFF;
	TCNT1H = Timer1::tcnt1 >> 8;
	Timer1::_overflow();
}

