/*
 * UniProject.c
 *
 * Created: 8/15/2017 9:44:43 PM
 * Author : DR
 */ 

#include <avr/io.h>
#include "UART.h"
#include "PWMInit.h"

#define F_CPU 16000000UL

int main(void)
{
	InitializeUART0(9600, 0, 8, 0, 0);
	InitializePWM_4C( 1000, 33);
	//DDRH |= ( 1 << PH3 );
	//OCR4A = 10;
	//TCNT4 = 0;
	//ICR4 = 0xFF;
	//TCCR4A |= ( 1 << WGM41) | ( 0 << WGM40 ) | ( 1 << COM4A1 ) | ( 0 << COM4A0 );
	//TCCR4B |= ( 1 << WGM43) | ( 1 << WGM42 ) | ( 1 << CS41 );
    
	/* Replace with your application code */
    while (1) 
    {
		send_int_Uart(ICR4);
		//TransmitString("Hello World!");
			//TransmitUART0(10);
			//TransmitUART0(13);
    }
}

