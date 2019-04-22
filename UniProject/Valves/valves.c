/*
 * CFile1.c
 *
 * Created: 4/8/2019 11:54:59 PM
 *  Author: DR
 */ 
#include <avr/io.h>

static void openValve1(){
	DDRF |= (1 << DDF0);
	PORTF |= (1 << PF0);
}

static void openValve2(){
	DDRF |= (1 << DDF1);
	PORTF |= (1 << PF1);
}

static void openValve3(){
	DDRF |= (1 << DDF5);
	PORTF |= (1 << PF5);
}

static void openValve4(){
	DDRK |= (1 << DDK0);
	PORTK |= (1 << PK0);
}

static void openValve5(){
	DDRK |= (1 << DDK6);
	PORTK |= (1 << PF6);
}

static void openValve6(){
	DDRK |= (1 << DDK7);
	PORTK |= (1 << PK7);
}

static void closeValve1(){
	DDRF &= ~(1 << DDF0);
	PORTF &= ~(1 << PF0);
}

static void closeValve2(){
	DDRF &= ~(1 << DDF1);
	PORTF &= ~(1 << PF1);
}

static void closeValve3(){
	DDRF &= ~(1 << DDF5);
	PORTF &= ~(1 << PF5);
}

static void closeValve4(){
	DDRK &= ~(1 << DDK0);
	PORTK &= ~(1 << PK0);
}

static void closeValve5(){
	DDRK &= ~(1 << DDK6);
	PORTK &= ~(1 << PF6);
}

static void closeValve6(){
	DDRK &= ~(1 << DDK7);
	PORTK &= ~(1 << PK7);
}


struct Valves {
	void (*openV1)();
	void (*openV2)();
	void (*openV3)();
	void (*openV4)();
	void (*openV5)();
	void (*openV6)();
	void (*closeV1)();
	void (*closeV2)();
	void (*closeV3)();
	void (*closeV4)();
	void (*closeV5)();
	void (*closeV6)();
} VALVES;

int initValves(void){
	VALVES.openV1 = openValve1;
	VALVES.openV2 = openValve2;
	VALVES.openV3 = openValve3;
	VALVES.openV4 = openValve4;
	VALVES.openV5 = openValve5;
	VALVES.openV6 = openValve6;
	VALVES.closeV1 = closeValve1;
	VALVES.closeV2 = closeValve2;
	VALVES.closeV3 = closeValve3;
	VALVES.closeV4 = closeValve4;
	VALVES.closeV5 = closeValve5;
	VALVES.closeV6 = closeValve6;
}

