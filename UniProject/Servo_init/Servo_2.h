/*
 * servo2.h
 *
 * Created: 4/9/2021 11:46:22 AM
 *  Author: DR
 */ 

#ifndef SERVO2_H_
#define SERVO2_H_

#include <stdbool.h>

enum Servo_2_State {
	OPEN_2_SERVO,
	CLOSED_2_SERVO,
	INITIAL_2_SERVO,
};

extern enum Servo_2_State servo_2_state;

void StopServo_2();

void _launchServo_2();

void _setToOpenPosition_2();

bool checkServo_2_ForMoving();

void closeValve_2();

void openValve_2();

void InitializeServo_2();

#endif /* SERVO2_H_ */