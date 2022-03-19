/*
 * Servo_1.h
 *
 * Created: 10/14/2018 6:09:40 PM
 *  Author: DR
 */ 

#ifndef SERVO_1_H_
#define SERVO_1_H_

#include <stdbool.h>

enum Servo_1_State {
	OPEN_1_SERVO,
	CLOSED_1_SERVO,
	INITIAL_1_SERVO,
};

extern enum Servo_1_State servo_1_state;

void StopServo_1();

void _launchServo_1();

void _setToOpenPosition_1();

bool checkServo_1_ForMoving();

void closeValve_1();

void openValve_1();

void button_interruption_1_init();

void InitializeServo_1();

#endif /* SERVO_1_H_ */