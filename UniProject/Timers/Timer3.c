/*
 * Timer3.c
 *
 * Created: 28.04.2019 10:37:23
 *  Author: MI
 */ 

#include <avr/io.h>

//static void reset_timer3_to_starting_value(){
	////TCNT3 = 0; // with such a prescaler and starting TCNT3 we get 0.5HZ
	////TCNT3 = 17143; //with such a prescaler and starting TCNT3 we get 1HZ
	//TCNT3 = 34286; // with such a prescaler and starting TCNT3 we get 2HZ
//}
//
//void launch_timer_3(){
	//reset_timer3_to_starting_value();
	//TIMSK3 |= (1 << TOIE3);
	//TCCR3B |= (1 << CS32);
//}
//
////after 2 seconds that timer will overflow
//void launch_timer_3_for2_seconds() {
	//TCNT3 = 0;// with such a prescaler and starting TCNT3 we get 0.5HZ
	//TIMSK3 |= (1 << TOIE3);
	//TCCR3B |= (1 << CS32);
//}
//
//void stop_timer_3(){
	//TIMSK3 &= ~(1 << TOIE3);
	//TCCR3B &= ~(1 << CS32);
//}