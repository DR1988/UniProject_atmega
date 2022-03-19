/*
 * Timer1.c
 *
 * Created: 28.04.2019 10:37:23
 *  Author: MI
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>
#include "../Servo_init/Servo_0.h"
#include "../Servo_init/Servo_1.h"
#include "../Servo_init/Servo_2.h"

static void reset_timer1_to_starting_value(){
	//TCNT1 = 0; // with such a prescaler and starting TCNT3 we get 0.5HZ
	TCNT1 = 34286; // with such a prescaler and starting TCNT3 we get 2HZ
	//TCNT1 = 17143; //with such a prescaler and starting TCNT3 we get 1HZ
}

void launch_timer_1(){
	PORTA |= (1<<PA1);
	reset_timer1_to_starting_value();
	TIMSK1 |= (1 << TOIE1);
	TCCR1B |= (1 << CS12);
}

void launch_timer_1_for2_seconds() {
	TCNT1 = 0;// with such a prescaler and starting TCNT3 we get 0.5HZ
	TIMSK1 |= (1 << TOIE1);
	TCCR1B |= (1 << CS12);
}

void stop_timer_1(){
	TIMSK1 &= ~(1 << TOIE1);
	TCCR1B &= ~(1 << CS12);
}

ISR(TIMER1_OVF_vect){
	//PORTA ^= (1<<PA1);
	if (servo_1_state == INITIAL_1_SERVO) {
		stop_timer_1();
		openValve_1();
	} else {
		stop_timer_1();
		StopServo_1();
	}
	if (servo_0_state == INITIAL_0_SERVO) {
		stop_timer_1();
		openValve_0();
	} else {
		stop_timer_1();
		StopServo_0();
	}
	if (servo_2_state == INITIAL_2_SERVO) {
		stop_timer_1();
		openValve_2();
	} else {
		stop_timer_1();
		StopServo_2();
	}
	//button_interruption_1_init();

}