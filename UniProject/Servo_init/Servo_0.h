/*
 * Servo_0.h
 *
 * Created: 10/14/2018 6:09:40 PM
 *  Author: DR
 */ 


#ifndef SERVO_0_H_
#define SERVO_0_H_

#define SERVO_0_OPEN 40
#define SERVO_0_CLOSE 20

#define F_CPU 16000000UL

#include <stdbool.h>
#include <avr/cpufunc.h>
#include "../Timers/Timer3.h"

bool is_Servo_0_Open = true;

void StopServo_0(){
	DDRH &= ~( 1 << PH6 );
}

void _launchServo_0(){
	DDRH |= ( 1 << DDH6 );
}

void _setToOpenPosition_0() {
	OCR2B=26;
	_launchServo_0();
	launch_timer_3();
	//OCR2B=SERVO_0_OPEN;
}

bool checkServo_0_ForMoving() {
	_NOP();
	return PINB & (1<<PB7);
}

void closeValve_0() {
	OCR2B = SERVO_0_CLOSE;
	is_Servo_0_Open=false;
	_launchServo_0();
}

void openValve_0() {
	OCR2B = SERVO_0_OPEN;
	is_Servo_0_Open=true;
	_launchServo_0();
}

void button_interruption_3_init(){
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT7);
}

void InitializeServo_0()
{
	//DDRG &= ~(1 << PG5); // set PG5 to zero
	////DDRG |= (1 << PG5);
	////PORTG |= (1 << PG5);
	//TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00); // fast PWM
	//TCCR0B |= (1 << CS02) | (1 << CS00);
	//// OCR0B = 32;  // full left
	//// OCR0B = 16;  // full right
	////OCR0B = 16;
	//
	//// need using interruption to detect shaft positions 
	DDRB &= ~(1 << PB7);
	
 	DDRH &= ~( 1 << PH6 );
// 	DDRH |= ( 1 << DDH6 );
 	TCCR2A |= ( 1 << COM2B1 ) | ( 1 << WGM21) | ( 1 << WGM20) ;
 	TCCR2B |=  ( 1 << CS20 ) | ( 1 << CS21 )  | (1 << CS22) ;
 	//OCR2B = 16;
	_setToOpenPosition_0();
}


ISR(TIMER3_OVF_vect){
	openValve_0();
	stop_timer_3();
	button_interruption_3_init();
	//reset_timer3_to_starting_value();
	//PORTF ^= (1 << PF2);
}


#endif /* SERVO_0_H_ */