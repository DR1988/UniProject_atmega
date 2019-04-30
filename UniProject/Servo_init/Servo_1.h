/*
 * Servo_1.h
 *
 * Created: 10/14/2018 6:09:40 PM
 *  Author: DR
 */ 


#ifndef SERVO_1_H_
#define SERVO_1_H_

#define F_CPU 16000000UL

#include <stdbool.h>
#include <avr/cpufunc.h>
#include "../Timers/Timer1.h"

bool is_Servo_1_Open = true;

void StopServo_1(){
	DDRB &= ~( 1 << DDB4 );
}

void _launchServo_1(){
	DDRB |= ( 1 << DDB4 );
}

void _setToOpenPosition_1() {
	OCR2A=28;
	_launchServo_1();
	launch_timer_1();
}

bool checkServo_1_ForMoving() {
	_NOP();
	return PINB & (1<<PB6);
}

void closeValve_1() {
	OCR2A = 20;
	is_Servo_1_Open = false;
	_launchServo_1();
}

void openValve_1() {
	OCR2A = 45;
	is_Servo_1_Open = true;
	_launchServo_1();
}

void button_interruption_1_init(){
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT6);
}

void InitializeServo_1()
{
	DDRB &= ~(1 << PB6);
	
 	DDRB &= ~( 1 << DDB4 );
 	//DDRB |= ( 1 << DDB4 );
 	TCCR2A |= ( 1 << COM2A1 ) | ( 1 << WGM21) | ( 1 << WGM20) ;
 	TCCR2B |=  ( 1 << CS20 ) | ( 1 << CS21 )  | (1 << CS22) ;
 	_setToOpenPosition_1();
}

ISR(TIMER1_OVF_vect){
	openValve_1();
	stop_timer_1();
	button_interruption_1_init();
	//PORTF ^= (1 << PF2);
}


#endif /* SERVO_1_H_ */