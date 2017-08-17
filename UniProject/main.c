/*
 * UniProject.c
 *
 * Created: 8/15/2017 9:44:43 PM
 * Author : DR
 */ 

#include <avr/io.h>
#include "UART.h"

#define F_CPU 16000000UL

int main(void)
{
		InitializeUART0(9600, 0, 8, 0, 0);
		
    /* Replace with your application code */
    while (1) 
    {
			TransmitString("Hello World!");
			//TransmitUART0(10);
			//TransmitUART0(13);
    }
}

