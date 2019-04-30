/*
 * Timer1.c
 *
 * Created: 28.04.2019 10:37:23
 *  Author: MI
 */ 

#include <avr/io.h>

static void reset_timer1_to_starting_value(){
	//TCNT1 = 0; // with such a prescaler and starting TCNT3 we get 0.5HZ
	TCNT1 = 34286; // with such a prescaler and starting TCNT3 we get 2HZ
	//TCNT1 = 17143; //with such a prescaler and starting TCNT3 we get 1HZ
}

void launch_timer_1(){
	reset_timer1_to_starting_value();
	TIMSK1 |= (1 << TOIE1);
	TCCR1B |= (1 << CS12);
}

void stop_timer_1(){
	TIMSK1 &= ~(1 << TOIE1);
	TCCR1B &= ~(1 << CS12);
}