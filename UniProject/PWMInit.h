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

void setPwm(double Pwm){
	if (Pwm <= 100)
	{
		OCR4A = (uint16_t) ICR4 * 0.01 * Pwm;
	} else if (Pwm <= 0) {
		OCR4A = 0;
	} else if (Pwm > 100) {
		OCR4A = 0;
	}
}

void InitializePWM_4C( uint32_t Frequency, double Pwm )
{
	TCCR4B = 0x00;
	DDRH |= ( 1 << PH3 );
	TCCR4A |= ( 1 << WGM41) | ( 0 << WGM40 ) | ( 1 << COM4A1 ) | ( 0 << COM4A0 );
	TCCR4B |= ( 1 << WGM43) | ( 1 << WGM42 ) ;
	uint32_t F_factor = F_CPU / Frequency;

	int shifter = 1;
	uint32_t multiplier = F_factor;
	while ( multiplier > 65535 ){
		multiplier /= 2;
		shifter++;
	}
	if (shifter > 5) {
		shifter = 5;
	}
	switch ( shifter )
		{
		case 1:
			TCCR4B |= ( 1 << CS40 ); 
			ICR4 = (uint16_t) (F_factor  - 1);
		break;
		case 2:
			TCCR4B |= ( 1 << CS41 ); //decrease in 8
			ICR4 = (uint16_t) (F_factor / 8  - 1);
		break;
		case 3:
			TCCR4B |= ( 1 << CS41 ) | ( 1 << CS40 ); //decrease in 64
			ICR4 = (uint16_t) (F_factor / 64 - 1);
		break;
		case 4:
			TCCR4B |= ( 1 << CS42 ); //decrease in 256
			ICR4 = (uint16_t) (F_factor / 256  - 1);
		break;
		case 5:
			TCCR4B |= ( 1 << CS42 ) | ( 1 << CS40 ); //decrease in 1024
			ICR4 = (uint16_t) (F_factor / 1024 + 1);
		break;
	}
	
	if ( ICR4 == 0 )
	{
		OCR4A = 0;
	 } else {
		setPwm(Pwm); // 100 - percentage
	 }
}
#endif /* PWMInit */