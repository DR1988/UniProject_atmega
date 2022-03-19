/*
 * Timer4.c
 *
 * Created: 4/9/2021 12:00:32 PM
 *  Author: DR
 */ 
#include <avr/io.h>

static void reset_timer4_to_starting_value(){
	//TCNT4 = 0; // with such a prescaler and starting TCNT3 we get 0.5HZ
	//TCNT4 = 17143; //with such a prescaler and starting TCNT3 we get 1HZ
	TCNT4 = 34286; // with such a prescaler and starting TCNT3 we get 2HZ
}

void launch_timer_4(){
	reset_timer4_to_starting_value();
	TIMSK4 |= (1 << TOIE4);
	TCCR4B |= (1 << CS42);
}

//after 2 seconds that timer will overflow
void launch_timer_4_for2_seconds() {
	TCNT4 = 0;// with such a prescaler and starting TCNT3 we get 0.5HZ
	TIMSK4 |= (1 << TOIE4);
	TCCR4B |= (1 << CS42);
}

void stop_timer_4(){
	TIMSK4 &= ~(1 << TOIE4);
	TCCR4B &= ~(1 << CS42);
}