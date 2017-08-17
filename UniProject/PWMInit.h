/*
 * IncFile1.h
 *
 * Created: 17.08.2017 15:51:42
 *  Author: DR
 */ 


#ifndef PWMInit
#define PWMInit

#define F_CPU 16000000UL
#include <math.h>

void setPwm(int Pwm){
	if (Pwm <= 100)
	{
		OCR4A = (uint16_t) ICR4 * 0.01 * Pwm;
	} else {
		OCR4A = 0;
	}
}

void InitializePWM_4C( uint32_t Frequency, int Pwm)
{
	TCCR4B = 0x00;
	DDRH |= ( 1 << PH3 );
	TCCR4A |= ( 1 << WGM41) | ( 0 << WGM40 ) | ( 1 << COM4A1 ) | ( 0 << COM4A0 );
	TCCR4B |= ( 1 << WGM43) | ( 1 << WGM42 ) ;
	uint32_t F_factor = F_CPU / Frequency;
	//F_factor > 64000 => freq < 250 Hz
	if ( F_factor < 64000 ) {
		TCCR4B |= ( 1 << CS40 );
		ICR4 = (uint16_t) F_factor - 1;
	} else if ()

	
	if ( ICR4 == 0 )
	{
		OCR4A = 0;
	 } else {
		setPwm(Pwm); // 100 - percentage
	 }
}
#endif /* PWMInit */