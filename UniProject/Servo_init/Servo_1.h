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

void StopServo_1(){
	DDRB &= ~( 1 << DDB4 );
}

void _launchServo_1(){
	DDRB |= ( 1 << DDB4 );
}

void _setToOpenPosition_1() {
	OCR2A=33;
	_launchServo_1();
}

bool checkServo_1_ForMoving() {
	return PINK & (1<<PK7);
}

void closeValve_1() {
	OCR2A = 20;
	_launchServo_1();
}

void openValve_1() {
	OCR2A = 34;
	_launchServo_1();
}

void InitializeServo_1()
{
	DDRK &= ~(1 << PK7);
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT23);
	
 	DDRB &= ~( 1 << DDB4 );
 	//DDRB |= ( 1 << DDB4 );
 	TCCR2A |= ( 1 << COM2A1 ) | ( 1 << WGM21) | ( 1 << WGM20) ;
 	TCCR2B |=  ( 1 << CS20 ) | ( 1 << CS21 )  | (1 << CS22) ;
 	_setToOpenPosition_1();
	
}


#endif /* SERVO_1_H_ */