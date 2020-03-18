

#ifndef INITIALIZATIONS_H
#define INITIALIZATIONS_H

#include "stm32l476xx.h"

//microseconds * 5 = throttleCount
//
#define START_THROTTLE (130 * 5) //130 us

void PWM_Init(void);
void joystick_init(void);
void interrupt_init(void);

#endif
