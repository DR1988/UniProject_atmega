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
#include <avr/delay.h>

void StopServo_1(){
	DDRB &= ~( 1 << DDB4 );
}

void _launchServo_1(){
	DDRB |= ( 1 << DDB4 );
}

void _setToOpenPosition_1() {
	OCR2A=30;
	_launchServo_1();
	_delay_ms(500);
	OCR2A=45;
}

bool checkServo_1_ForMoving() {
	return PINK & (1<<PK7);
}

void closeValve_1() {
	OCR2A = 20;
	_launchServo_1();
}

void openValve_1() {
	OCR2A = 45;
	_launchServo_1();
}

void InitializeServo_1()
{
	DDRK &= ~(1 << PB6);
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT6);
	
 	DDRB &= ~( 1 << DDB4 );
 	//DDRB |= ( 1 << DDB4 );
 	TCCR2A |= ( 1 << COM2A1 ) | ( 1 << WGM21) | ( 1 << WGM20) ;
 	TCCR2B |=  ( 1 << CS20 ) | ( 1 << CS21 )  | (1 << CS22) ;
 	_setToOpenPosition_1();
	
}


#endif /* SERVO_1_H_ */