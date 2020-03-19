
#include "buttonInterrupts.h"
#include "throttle.h"
#include "nRF24L01.h"
#include "LCD.h"
#include <stdio.h>


//void EXTI0_IRQHandler(void){
//	EXTI->PR1 |= EXTI_PR1_PIF0;
//	
//	Red_LED_Toggle();
//	Green_LED_Toggle();
//}

//void EXTI1_IRQHandler(void){
//	EXTI->PR1 |= EXTI_PR1_PIF1;

//	Green_LED_Toggle();
//}

void EXTI2_IRQHandler(void){
	
	
	char RX_Data[1];
	uint8_t read;
	
	TRX_IO_Read(&read, nRF24L01_STATUS, 1);
	sprintf(RX_Data, "%x", read);
	LCD_DisplayString(RX_Data);
	uint8_t temp = 0x70;
	TRX_IO_Write(&temp, nRF24L01_STATUS, 1);
	
	EXTI->PR1 |= EXTI_PR1_PIF2;
}

//PA3, up
void EXTI3_IRQHandler(void){
	EXTI->PR1 |= EXTI_PR1_PIF3;
	
	increaseThrottleTenPercent();
}

//PA5, down
void EXTI9_5_IRQHandler(void){
	EXTI->PR1 |= EXTI_PR1_PIF5;
	
	decreaseThrottleTenPercent();
}

