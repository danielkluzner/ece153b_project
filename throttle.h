

#ifndef THROTTLE_H
#define THROTTLE_H

#include "stm32l476xx.h"

#define MAX_THROTTLE (170 * 5)
#define MIN_THROTTLE (125 * 5)
#define STEP_THROTTLE (2 * 5)

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
