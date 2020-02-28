
#include "buttonInterrupts.h"
#include "throttle.h"



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

//void EXTI2_IRQHandler(void){
//	EXTI->PR1 |= EXTI_PR1_PIF2;
//	
//	Red_LED_Toggle();
//}

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

