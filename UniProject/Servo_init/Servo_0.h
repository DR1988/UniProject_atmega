/*
 * Servo_0.h
 *
 * Created: 10/14/2018 6:09:40 PM
 *  Author: DR
 */ 

#ifndef SERVO_0_H_
#define SERVO_0_H_

#include <stdbool.h>

enum Servo_0_State {
	OPEN_0_SERVO,
	CLOSED_0_SERVO,
	INITIAL_0_SERVO,
};

extern enum Servo_0_State servo_0_state;

void StopServo_0();

void _launchServo_0();

void _setToOpenPosition_0();

bool checkServo_0_ForMoving();

void closeValve_0();

void openValve_0();

void button_interruption_3_init();

void InitializeServo_0();

#endif /* SERVO_0_H_ */