
#ifndef BUTTONINTERRUPTS_H
#define BUTTONINTERRUPTS_H

#include "stm32l476xx.h"
#include "throttle.h"
#include "INA260.h"
#include "LCD.h"
#include "nRF24L01.h"

//void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

#endif
