/*
 * Servo_2.c
 *
 * Created: 4/9/2021 4:50:36 PM
 *  Author: DR
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/cpufunc.h>
#include "../Timers/Timer1.h"
#include "../Timers/Timer3.h"
#include "../Servo_init/Servo_2.h"

#define SERVO_2_OPEN 39
#define SERVO_2_CLOSE 24

enum Servo_2_State servo_2_state;

void StopServo_2(){
	DDRE &= ~( 1 << PE3 );
}

void _launchServo_2(){
	DDRE |= ( 1 << PE3 );
}

void _setToOpenPosition_2() {
	OCR3A = 30;
	_launchServo_2();
	servo_2_state = INITIAL_2_SERVO;
	launch_timer_1();
}

bool checkServo_2_ForMoving() { //remove this shit
	_NOP();
	return PINB & (1<<PB4);
}

void closeValve_2() {
	OCR3A = SERVO_2_CLOSE;
	_launchServo_2();
	servo_2_state = CLOSED_2_SERVO;
	launch_timer_1_for2_seconds();
}

void openValve_2() {
	OCR3A = SERVO_2_OPEN; // was 45
	servo_2_state = OPEN_2_SERVO;
	_launchServo_2();
	launch_timer_1_for2_seconds();
}

void InitializeServo_2()
{
	DDRE &= ~( 1 << PE3 );
	TCCR3A |= ( 1 << COM3A1 ) | ( 1 << WGM30) ;
	TCCR3B |=  ( 1 << CS30 ) | ( 0 << CS31 )  | (1 << CS32)| ( 1 << WGM32) ; // clkI/O/1024 (From prescaler)
	_setToOpenPosition_2();
}
