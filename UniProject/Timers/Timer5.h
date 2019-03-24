/*
 * Timer5.h
 *
 * Created: 10/15/2018 1:00:36 AM
 *  Author: DR
 */ 


#ifndef TIMER5_H_
#define TIMER5_H_

void TCNT5_startingValue(unsigned int value) {
	TCNT5 = value;
}

void initializeTimerCounter_5()
{
	TIMSK5 |= (1 << TOIE5);
	TCCR5B = (1 << CS50); // doesnt increase countsec value - should change CS50 to CS51 or smth else 
	TCNT5_startingValue(1535);
}

#endif /* TIMER5_H_ */