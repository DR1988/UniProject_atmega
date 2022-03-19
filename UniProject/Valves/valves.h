/*
 * valves.h
 *
 * Created: 4/8/2019 11:15:21 PM
 *  Author: DR
 */ 


#ifndef VALVES_H_
#define VALVES_H_

struct Valves {
  void (*openV1)();
  void (*openV2)();
  void (*openV3)();
  void (*openV4)();
  void (*openV5)();
  void (*openV6)();
  void (*openV7)();
  void (*openV8)();
  void (*closeV1)();
  void (*closeV2)();
  void (*closeV3)();
  void (*closeV4)();
  void (*closeV5)();
  void (*closeV6)();
  void (*closeV7)();
  void (*closeV8)();
}VALVES;

//void openValve1(void);


#endif /* VALVES_H_ */