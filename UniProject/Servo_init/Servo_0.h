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

void StopServo_0(){
	DDRG &= ~(1 << PG5);
}

void _launchServo_0(){
	DDRG |= (1 << PG5);
}

void _setToOpenPosition() {
	OCR0B=33;
	_launchServo_0();
}

bool checkServo_0_ForMoving() {
	return PINK & (1<<PK7);
}

void closeValve_0() {
	OCR0B = 20;
	_launchServo_0();
}

void openValve_0() {
	OCR0B = 34;
	_launchServo_0();
}

void InitializeServo_0()
{
	DDRG &= ~(1 << PG5); // set PG5 to zero
	//DDRG |= (1 << PG5);
	//PORTG |= (1 << PG5);
	TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00); // fast PWM
	TCCR0B |= (1 << CS02) | (1 << CS00);
	// OCR0B = 32;  // full left
	// OCR0B = 16;  // full right
	//OCR0B = 16;
	
	// need using interruption to detect shaft positions 
	DDRK &= ~(1 << PK7);
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT23);
	
	_setToOpenPosition();
}


#endif /* SERVO_1_H_ */