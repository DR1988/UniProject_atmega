/*
 * UniProject.c
 *
 * Created: 8/15/2017 9:44:43 PM
 * Author : DR
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "UART.h"
#include "PWMInit.h"

#define F_CPU 16000000UL

volatile struct UARTData {
	volatile unsigned char data_in[8];
	volatile unsigned char data_out[8];
	volatile unsigned char dataCount;
};

volatile struct PWM {
	volatile double pwmValue;
};

volatile struct TIMER5 {
	volatile uint32_t counter;
	volatile uint32_t captureFirst;
	volatile uint32_t captureSecond;
	volatile uint32_t seconds;
	volatile uint32_t totalTicks;
};

struct UARTData UART0 = {.dataCount = 0};
struct PWM PWM4C = {.pwmValue = 0};
struct TIMER5 Timer5_1 = {.counter = 0, .captureFirst = 0, .captureSecond = 0, .seconds = 0, .totalTicks = 0 };

int counter = 0;
int setRPM = 2500;

int main(void)
{
	DDRH |= (1 << PH4);
	PORTH |=  (1 << PH4);

  TIMSK5 |= (1 << TOIE5) | (1 << ICIE5);
	TCCR5A = (0	<< COM5A1) | (0 << COM5A0) | (0 << WGM51) | ( 0 << WGM50);
	TCCR5B = (1 << ICNC5 ) | (1 << ICES5) | (0 << WGM53) | (0 << WGM52) | (0 << CS52) | (0 << CS51) | (1 << CS50);
  TCNT5 = 1535;

	sei();
	InitializeUART0(9600, 0, 8, 0, 0);
	InitializePWM_4C(5000, PWM4C.pwmValue);
	//strlcpy();

	/* Replace with your application code */
    while (1) 
    {

    }
}

ISR(TIMER5_CAPT_vect)
{
	//counter++;
	cli();
	Timer5_1.totalTicks = Timer5_1.counter * 65535 + TCNT5;
	//send_int_Uart(F_CPU / Timer5_1.totalTicks * 3 * 4);
	if (F_CPU / Timer5_1.totalTicks * 3 * 4 < setRPM) {
		//TransmitString("+");
		setPwm(PWM4C.pwmValue += 0.05);
		//send_int_Uart(PWM4C.pwmValue);
		} else if (F_CPU / Timer5_1.totalTicks * 3 * 4 > setRPM) {
		//TransmitString("-");
		setPwm(PWM4C.pwmValue -= 0.05);
	}
	TCNT5 = 0;
	Timer5_1.counter = 0;
sei();
}

ISR(TIMER5_OVF_vect)
{
	if(Timer5_1.totalTicks == 0 && PWM4C.pwmValue == 0) {
		PWM4C.pwmValue = 10;
		setPwm(PWM4C.pwmValue);
	}
	Timer5_1.counter++;
	//Timer5_1.secondCounts++;
	if(++Timer5_1.seconds >= 250){
		//if (F_CPU / Timer5_1.totalTicks * 3 * 4 < setRPM) {
			//TransmitString("+");
			//setPwm(PWM4C.pwmValue += 0.5);
		//send_int_Uart(PWM4C.pwmValue);
			//} else if (F_CPU / Timer5_1.totalTicks * 3 * 4 > setRPM) {
			//TransmitString("-");
			//setPwm(PWM4C.pwmValue -= 0.5);
		//}
		PORTH ^= (1 << PH4);
		Timer5_1.seconds = 0;
		send_int_Uart(F_CPU / Timer5_1.totalTicks * 3 * 4);
		//send_int_Uart(counter * 4 * 3);
		//counter=0;
	}
	//PORTH ^= (1 << PH4);
}

ISR (USART0_RX_vect)
{
	UART0.data_in[UART0.dataCount] = UDR0;
	if(UDR0 == '+' ) {
		setPwm(++PWM4C.pwmValue);
		//TransmitString(UART0.data_in);
		//UART0.dataCount = 0;
		//memset(&UART0.dataCount, 0, sizeof(UART0.dataCount));
	} else {
		UART0.dataCount++;
	}
	//TransmitString(UART0.data_in);
}
