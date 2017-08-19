#ifndef UARTInit

#define UARTInit

#define  EVEN 0
#define  ODD 1

#define RETURN_NEWLINE "\r\n"

#include <math.h>
#include <avr/io.h>

#define F_CPU 16000000UL

unsigned char ReceiveUART0(void)
{
	while (! (UCSR0A & (1 << RXC0)) );

	return UDR0;
}

void TransmitUART0(unsigned char data)
{
	//Wait until the Transmitter is ready
	while (! (UCSR0A & (1 << UDRE0)) );

	//Get that data out a here!
	UDR0 = data;
}

void returnNewLine()
{
	TransmitUART0(10);
	TransmitUART0(13);
}

void TransmitString(unsigned char *s)
{
	while (*s != 0) TransmitUART0(*s++);
	returnNewLine();
}

void send_int_Uart(uint32_t c)
{
	char buffer[9];
	sprintf(buffer, "%lu", c);
	//itoa(c, buffer, 10);
	TransmitString(buffer);
}

void InitializeUART0(int Baud, char AsyncDoubleSpeed, char DataSizeInBits, char ParityEVEorODD, char StopBits)
{
	uint16_t UBBRValue = lrint( F_CPU / 16L / Baud ) - 1;
	
	if (AsyncDoubleSpeed == 1) UCSR0A = (1 << U2X0); // setting the U2X bit to 1 for double speed async
	
	//Put the upper part of the baud number here (bits 8 to 11)
	UBRR1H = (unsigned char) (UBBRValue >> 8);
	
	UBRR0L = UBBRValue;
	//Enable the receiver and transmitter
	UCSR0B = ( 1 << RXCIE0 ) |(1 << RXEN0) | (1 << TXEN0);
	
	//set 2 stop bits
	if (StopBits == 2) UCSR0C = (1 << USBS0);
	
	if (ParityEVEorODD == EVEN) UCSR0C |= (1 << UPM01);
	if (ParityEVEorODD == ODD) UCSR0C |= (3 << UPM01);
	
	if (DataSizeInBits == 6) UCSR0C |= (1 << UCSZ00); // 6 bit data length
	if (DataSizeInBits == 7) UCSR0C |= (2 << UCSZ00); // 7 bit data length
	if (DataSizeInBits == 8) UCSR0C |= (3 << UCSZ00); // 8 bit data length
	if (DataSizeInBits == 9) UCSR0C |= (7 << UCSZ00); // 9 bit data length
}

#endif UARTInit