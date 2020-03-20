#ifndef THROTTLE_H
#define THROTTLE_H

#include "stm32l476xx.h"

//throttle signal to motors is PWM
//period = 2 milliseconds
//OneShot125 protocol
//min pulse is 125 us
//max pulse is 250 us

#define MAX_THROTTLE (170 * 5)   //170 us
#define MIN_THROTTLE (125 * 5)   //125 us
#define STEP_THROTTLE (1 * 5)    //  1 us
#define START_THROTTLE (130 * 5) //130 us

void increaseThrottle(void);

void Motor1_inrease(void);
void Motor2_inrease(void);
void Motor3_inrease(void);
void Motor4_inrease(void);

void decreaseThrottle(void);

void Motor1_decrease(void);
void Motor2_decrease(void);
void Motor3_decrease(void);
void Motor4_decrease(void);

void killThrottle(void);

#endif
