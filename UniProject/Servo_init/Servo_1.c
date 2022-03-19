/*
 * Servo_1.c
 *
 * Created: 4/9/2021 3:53:29 PM
 *  Author: DR
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/cpufunc.h>
#include "../Timers/Timer1.h"
#include "../Servo_init/Servo_1.h"

#define SERVO_1_OPEN 39
#define SERVO_1_CLOSE 24

enum Servo_1_State servo_1_state;

void StopServo_1(){
	DDRB &= ~( 1 << DDB4 );
}

void _launchServo_1(){
	DDRB |= ( 1 << DDB4 );
}

void _setToOpenPosition_1() {
	OCR2A=30;
	_launchServo_1();
	servo_1_state = INITIAL_1_SERVO;
	launch_timer_1();
}

bool checkServo_1_ForMoving() {
	_NOP();
	return PINB & (1<<PB6);
}

void closeValve_1() {
	OCR2A = SERVO_1_CLOSE;
	_launchServo_1();
	servo_1_state = CLOSED_1_SERVO;
	launch_timer_1_for2_seconds();
}

void openValve_1() {
	OCR2A = SERVO_1_OPEN; // was 45
	servo_1_state = OPEN_1_SERVO;
	_launchServo_1();
	launch_timer_1_for2_seconds();
}

void button_interruption_1_init(){
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT6);
}

void InitializeServo_1()
{
	DDRB &= ~(1 << PB6);
	
 	DDRB &= ~( 1 << DDB4 );
 	TCCR2A |= ( 1 << COM2A1 ) | ( 1 << WGM21) | ( 1 << WGM20) ;
 	TCCR2B |=  ( 1 << CS20 ) | ( 1 << CS21 )  | (1 << CS22) ;
 	_setToOpenPosition_1();
}