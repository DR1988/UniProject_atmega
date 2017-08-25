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
	volatile uint16_t pwmFrequency;
	volatile double pwmValue;
};

volatile struct TIMER5 {
	volatile uint32_t counter;
	volatile uint32_t captureFirst;
	volatile uint32_t captureSecond;
	volatile uint32_t seconds;
	volatile uint32_t totalTicks;
};

volatile struct RPM {
	volatile uint16_t currentRPM;
	volatile uint16_t setRPM;
	volatile uint16_t counter;
};

struct UARTData UART0 = {.dataCount = 0};
struct PWM PWM4C = {.pwmFrequency = 2500, .pwmValue = 15};
struct TIMER5 Timer5_1 = {.counter = 0, .captureFirst = 0, .captureSecond = 0, .seconds = 0, .totalTicks = 0 };
struct RPM RPM_1 = {.currentRPM = 0, .setRPM = 2500, .counter = 0};

int main(void)
{
	DDRH |= (1 << DDH4);
	PORTH |=  (1 << PH4);
	
	//DDRD |= (0 << DDD4);
	PORTD |= (1 << PD3);
	
  TIMSK5 |= (1 << TOIE5) | (0 << ICIE5);
	TCCR5A = (0	<< COM5A1) | (0 << COM5A0) | (0 << WGM51) | ( 0 << WGM50);
	TCCR5B = (0 << ICNC5 ) | (0 << ICES5) | (0 << WGM53) | (0 << WGM52) | (0 << CS52) | (0 << CS51) | (1 << CS50);
  TCNT5 = 1535;
	
	EICRA |= (0 << ISC31) | (1 << ISC30);
	EIMSK |= (1 << INT3);

	sei();
	InitializeUART0(9600, 0, 8, 0, 0);
	InitializePWM_4C(PWM4C.pwmFrequency, PWM4C.pwmValue);
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
	//Timer5_1.totalTicks = Timer5_1.counter * 65535 + TCNT5;
	////send_int_Uart(F_CPU / Timer5_1.totalTicks * 3 * 4);
	//if (F_CPU / Timer5_1.totalTicks * 3 * 4 < setRPM) {
		////TransmitString("+");
		//setPwm(PWM4C.pwmValue += 0.05);
		////send_int_Uart(PWM4C.pwmValue);
		//} else if (F_CPU / Timer5_1.totalTicks * 3 * 4 > setRPM) {
		////TransmitString("-");
		//setPwm(PWM4C.pwmValue -= 0.05);
	//}
	//TCNT5 = 0;
	//Timer5_1.counter = 0;
	sei();
}

int sender = 0;
uint32_t currentRPM = 0 ;
ISR(INT3_vect)
{
	//TransmitString("asd");
	RPM_1.counter++;
	if(RPM_1.counter >= 10) {
		Timer5_1.totalTicks += Timer5_1.counter * 65535 + TCNT5;
		/*** current RPM ***\
		RPM.counter - interruption count on PD3
		totalTicks - how much cpu ticks done per 10 interruption
		multiply by 10 - now we now frequency of hall sensors signal
		multiply by 60 - per minute
		division by 4 - number of poles on engine - 8 => real revolution = 4 magnetic field revolutions
										(so, hall sensors will be detect it 4 times per real(mechanical) revolution) 
		division by 4 - interruption works on rise and fall => 10 * 60 / 4 / 2 = 75
		\****************/
		currentRPM = F_CPU * 75 /* 10 */ / Timer5_1.totalTicks /* * 60 / 4 / 2 */ ;
		RPM_1.counter = 0;
		Timer5_1.counter = 0;
		Timer5_1.totalTicks = 0;
		 TCNT5 = 0;
	}
	;
	sender++;
	if (sender > 500) {
		send_int_Uart(currentRPM);
		sender = 0;
	}
	//if (Timer5_1.captureFirst != 0)
	//{
		//Timer5_1.captureSecond = Timer5_1.captureFirst;
		//Timer5_1.captureFirst = TCNT5;
	//}
	//else
	//{
		//Timer5_1.captureFirst = TCNT5;
	//}
	//if (Timer5_1.captureFirst + Timer5_1.captureSecond > 64000)
	//{
		//Timer5_1.counter++;
		//Timer5_1.totalTicks += Timer5_1.counter * 64000 + abs(Timer5_1.captureFirst - Timer5_1.captureSecond);
	//}
	//else
	//{
		//Timer5_1.totalTicks += Timer5_1.counter * 64000 + Timer5_1.captureFirst + Timer5_1.captureSecond;
	//}
	//send_int_Uart(F_CPU / Timer5_1.totalTicks * 3 *4);
	//Timer5_1.totalTicks = Timer5_1.counter * 64000 + TCNT5;
	//PORTH ^= (1 << PH4);
}

ISR(TIMER5_OVF_vect)
{
	//if(Timer5_1.totalTicks == 0 && PWM4C.pwmValue == 0) {
		//PWM4C.pwmValue = 2;
		//setPwm(PWM4C.pwmValue);
	//}
	Timer5_1.counter++;
	//send_int_Uart(RPM_1.counter);
	//if (RPM_1.counter >= 10){
		//send_int_Uart(Timer5_1.totalTicks);
		//Timer5_1.totalTicks = 0;
		//Timer5_1.counter = 0;
		//RPM_1.counter = 0;
	//}
	//TCNT5 = 1535;
	//////Timer5_1.secondCounts++;
	
	//if(++Timer5_1.seconds >= 250){
		////if (F_CPU / Timer5_1.totalTicks * 3 * 4 < setRPM) {
			////TransmitString("+");
			////setPwm(PWM4C.pwmValue += 0.5);
		////send_int_Uart(PWM4C.pwmValue);
			////} else if (F_CPU / Timer5_1.totalTicks * 3 * 4 > setRPM) {
			////TransmitString("-");
			////setPwm(PWM4C.pwmValue -= 0.5);
		////}
		//PORTH ^= (1 << PH4);
		//Timer5_1.seconds = 0;
		//send_int_Uart( RPM_1.counter * 60 / 4 / 2  /* / RPM_1.counter / 100 * 3 * 4 */);
		////send_int_Uart( F_CPU / Timer5_1.totalTicks /* / RPM_1.counter / 100 * 3 * 4 */);
		//Timer5_1.counter = 0;
		//RPM_1.counter = 0;
		//Timer5_1.totalTicks = 0;
		////send_int_Uart(counter * 4 * 3);
		////counter=0;
	//}
	
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
