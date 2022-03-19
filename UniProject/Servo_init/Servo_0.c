/*
 * Servo_0.c
 *
 * Created: 4/9/2021 4:25:57 PM
 *  Author: DR
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/cpufunc.h>
#include "../Timers/Timer1.h"
#include "../Servo_init/Servo_0.h"

#define SERVO_0_OPEN 39
#define SERVO_0_CLOSE 24

enum Servo_0_State servo_0_state;

void StopServo_0(){
	DDRH &= ~( 1 << PH6 );
}

void _launchServo_0(){
	DDRH |= ( 1 << DDH6 );
}

void _setToOpenPosition_0() {
	OCR2B=30;
	_launchServo_0();
	servo_0_state = INITIAL_0_SERVO;
	launch_timer_1();
	//OCR2B=SERVO_0_OPEN;
}

bool checkServo_0_ForMoving() {
	_NOP();
	return PINB & (1<<PB7);
}

void closeValve_0() {
	OCR2B = SERVO_0_CLOSE;
	servo_0_state = CLOSED_0_SERVO;
	_launchServo_0();
	launch_timer_1_for2_seconds();
}

void openValve_0() {
	OCR2B = SERVO_0_OPEN;
	servo_0_state = OPEN_0_SERVO;
	_launchServo_0();
	launch_timer_1_for2_seconds();
}

void button_interruption_3_init(){
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT7);
}

void InitializeServo_0()
{
	//// need using interruption to detect shaft positions
	DDRB &= ~(1 << PB7);
	
	DDRH &= ~( 1 << PH6 );
	TCCR2A |= ( 1 << COM2B1 ) | ( 1 << WGM21) | ( 1 << WGM20) ;
	TCCR2B |=  ( 1 << CS20 ) | ( 1 << CS21 )  | (1 << CS22) ;
	_setToOpenPosition_0();
}
