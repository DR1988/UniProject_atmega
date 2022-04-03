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
#include "Servo_init/Servo_0.h"
#include "Servo_init/Servo_1.h"
#include "Servo_init/Servo_2.h"
#include "Timers/Timer5.h"
#include "Valves/valves.h"

#define F_CPU 16000000UL
#define UART_data_in_length 45
#include <util/delay.h>

struct UARTData {
	volatile unsigned char data_in[UART_data_in_length];
	volatile unsigned char data_out[8];
	volatile unsigned char dataCount;
	volatile unsigned char sendingTrue;
};

struct PWM {
	volatile uint16_t pwmFrequency;
	volatile double pwmValue;
};

struct TIMER5 {
	volatile uint32_t counter;
	volatile uint32_t captureFirst;
	volatile uint32_t captureSecond;
	volatile uint32_t seconds;
	volatile uint32_t totalTicks;
};

struct RPM {
	volatile int16_t currentRPM;
	volatile int16_t setRPM;
	volatile uint16_t counter;
	const uint16_t interruptionCounter;
};

struct PID {
	volatile double proportional;
	volatile double integral;
	volatile double differational;
	};

volatile struct UARTData UART0 = {.dataCount = 0, .sendingTrue = 0};
volatile struct PWM PWM4C = {.pwmFrequency = 1000, .pwmValue = 0};
volatile struct TIMER5 Timer5_1 = {.counter = 0, .captureFirst = 0, .captureSecond = 0, .seconds = 0, .totalTicks = 0 };
volatile struct RPM RPM_1 = {.currentRPM = 0, .setRPM = 0, .counter = 0, .interruptionCounter = 10};

char sendinComands = 0;

void decodeCommands(volatile unsigned char commands[])
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned char tempBuf[10];
	unsigned int extractedValue;
	while(commands[i] != '\n') {
		// stop command from control program
		if (commands[i] == 'S'){
			RPM_1.setRPM = 0;
			closeValve_0();
			closeValve_1();
			closeValve_2();
			VALVES.closeV1();
			VALVES.closeV2();
			VALVES.closeV3();
			VALVES.closeV4();
			VALVES.closeV5();
			VALVES.closeV6();
		}
		if(commands[i] == 'R' && commands[i + 1] == '8') {
			i = i + 2;
			while(commands[i] != '|'){
				tempBuf[j] = commands[i];
				i++;
				j++;
			}
			sscanf(tempBuf, "%d", &extractedValue);
			//send_int_Uart(extractedValue);
			RPM_1.setRPM = extractedValue;
			//send_int_Uart();
			//TransmitString(commands);
			//extractValue(*commands++);
		}
		if(commands[i] == 'V' && commands[i + 1] == '0') {
			i = i + 2;
			if(commands[i] == 'Y')
			{
				VALVES.openV1();
			}
			if(commands[i] == 'N'){
				VALVES.closeV1();
			}
		}
		if(commands[i] == 'V' && commands[i + 1] == '1') {
			i = i + 2;
			if(commands[i] == 'Y')
			{
				VALVES.openV2();
			}
			if(commands[i] == 'N'){
				VALVES.closeV2();
			}
		}
		if(commands[i] == 'V' && commands[i + 1] == '2') {
			i = i + 2;
			if(commands[i] == 'Y')
			{
				VALVES.openV3();
			}
			if(commands[i] == 'N'){
				VALVES.closeV3();
			}
		}
		if(commands[i] == 'V' && commands[i + 1] == '3') {
			i = i + 2;
			if(commands[i] == 'Y')
			{
				VALVES.openV4();
			}
			if(commands[i] == 'N'){
				VALVES.closeV4();
			}
		}
		if(commands[i] == 'V' && commands[i + 1] == '4') {
			i = i + 2;
			if(commands[i] == 'Y')
			{
				VALVES.openV5();
			}
			if(commands[i] == 'N'){
				VALVES.closeV5();
			}
		}
		if(commands[i] == 'V' && commands[i + 1] == '5') {
			i = i + 2;
			if(commands[i] == 'Y')
			{
				VALVES.openV6();
			}
			if(commands[i] == 'N'){
				VALVES.closeV6();
			}
		}
		if(commands[i] == 'V' && commands[i + 1] == '6') {
			i = i + 2;
			if(commands[i] == 'Y')
			{
				openValve_0();
			}
			if(commands[i] == 'N'){
				closeValve_0();
			}
		}
		if(commands[i] == 'V' && commands[i + 1] == '7') {
			i = i + 2;
			if(commands[i] == 'Y')
			{
				openValve_1();
			}
			if(commands[i] == 'N'){
				closeValve_1();
			}
		}
		if(commands[i] == 'V' && commands[i + 1] == '8') {
			i = i + 2;
			if(commands[i] == 'Y')
			{
				openValve_2();
			}
			if(commands[i] == 'N'){
				closeValve_2();
			}
		}
		i++;
	}
}

int main(void)
{

	DDRA |= (1 << PA1);
	DDRF |= (1 << DDF2);

	DDRH |= (1 << DDH4);



 	TIMSK0 |= (1 << TOIE0);
 	TCCR0B |= (1 << CS02) | (1 << CS00);

	//TCNT0 = 130;
	////
	EICRA |= (0 << ISC31) | (1 << ISC30);
	EIMSK |= (1 << INT3);

	sei();

 	initializeTimerCounter_5();
 	InitializeServo_0();
 	InitializeServo_1();
 	InitializeServo_2();
 	InitializeUART0(500000, 0, 8, 0, 0);
 	InitializePWM_4C(PWM4C.pwmFrequency, PWM4C.pwmValue);

	//DDRH |= ( 1 << PH3 );
	//TCCR4A |= ( 1 << WGM41) | ( 0 << WGM40 ) | ( 1 << COM4A1 ) | ( 0 << COM4A0 );
	//TCCR4B |= ( 1 << WGM43) | ( 1 << WGM42 ) ;
	//TCCR4B |= ( 1 << CS42 ) | ( 1 << CS40 );
	//ICR4 = (uint16_t) (F_CPU/1000 / 1024 + 1);
	//OCR4A=3;

	initValves();
	/* Replace with your application code */
    while (1)
    {

    }
}


//ISR(PCINT0_vect){
	//if (checkServo_0_ForMoving()){
		////PORTA ^= (1<<PA1); // just for show that interruption works
		//PORTA |= (1<<PA3);
	//} else {
		//StopServo_0();
	//}
	//if(checkServo_1_ForMoving()){
		////PORTA ^= (1<<PA1); // just for show that interruption works
	//} else{
		//StopServo_1();
	//}
//}


ISR(INT3_vect)
{

	//PORTH ^= (1 << PH4);
	RPM_1.counter++;
	if(RPM_1.counter >= RPM_1.interruptionCounter) {
		//send_int_Uart(Timer5_1.counter);
		Timer5_1.totalTicks += Timer5_1.counter * 64000 + TCNT5;
		/*** current RPM ***\
		RPM.counter - interruption count on PD3
		totalTicks - how much CPU ticks done per RPM_1.interruptionCounter interruptions
		multiply by 10 - now we now frequency of hall sensors signal
		multiply by 60 - per minute
		division by 4 - number of poles on engine - 8 => real revolution = 4 magnetic field revolutions
										(so, hall sensors will be detect it 4 times per real(mechanical) revolution)
		division by 4 - interruption works on rise and fall => 10 * 60 / 4 / 2 = 75
		\****************/
		RPM_1.currentRPM = F_CPU * 75 /* 10 */ / Timer5_1.totalTicks /* * 60 / 4 / 2 */ ;
		RPM_1.counter = 0;
		Timer5_1.counter = 0;
		Timer5_1.totalTicks = 0;
		TCNT5 = 1535;
	}

}

ISR(TIMER5_OVF_vect)
{
	//PORTA ^= (1<<PA1);
	if(sendinComands == 1)
	{
		decodeCommands(UART0.data_in);
		sendinComands = 0;
	}
	//TCNT5_startingValue(1535);
	TCNT5 = 1535;
	Timer5_1.counter++;
}

int connected = 0;
unsigned int countsec = 0;
ISR(TIMER0_OVF_vect){
	//PORTH ^= (1 << PH4);

	TCNT0 = 131;


	if(++countsec >= 125 && connected == 0){
		//send_int_Uart(RPM_1.currentRPM);
		TransmitString("CONNECTED");
		countsec=0;
		connected=1;
	}


	if(++Timer5_1.seconds >= 25 && connected == 1){
		//TransmitString("CON");
		Timer5_1.seconds = 0;
		if(RPM_1.setRPM <= 10 && RPM_1.currentRPM != 0){
			send_int_Uart("COM");
			setPwm(0);
			RPM_1.currentRPM = 0;
			PWM4C.pwmValue = 0;
		} else if (RPM_1.setRPM > 10) {

			send_int_Uart(RPM_1.currentRPM);

			setPwm(PWM4C.pwmValue += (RPM_1.setRPM - RPM_1.currentRPM) * 0.001);

			if (RPM_1.currentRPM < RPM_1.setRPM)
			{
				setPwm(PWM4C.pwmValue += (abs(RPM_1.setRPM - RPM_1.currentRPM)) * 0.0005);
			}
			else
			{
				setPwm(PWM4C.pwmValue -= (abs(RPM_1.setRPM - RPM_1.currentRPM)) * 0.0005);
			}
		}
	}
}


ISR (USART0_RX_vect)
{
	//cli();
	//TIMSK0 &= ~(1 << TOIE0);
	UART0.data_in[UART0.dataCount] = UDR0;
	if(UART0.data_in[UART0.dataCount] == '\n') {
		UART0.dataCount = 0;
		sendinComands = 1;
		//sei();
		//TIMSK0 = (1 << TOIE0);
		//UART0.dataCount = 0;
		//UART0.sendingTrue=1;
	} else {
		if(++UART0.dataCount >= UART_data_in_length){
			 UART0.dataCount = 0;
		}
		//++UART0.dataCount;
	}
}
