
#include "buttonInterrupts.h"
#include "throttle.h"



//void EXTI0_IRQHandler(void){
//	EXTI->PR1 |= EXTI_PR1_PIF0;
//	
//	killThrottle();
//}

//void EXTI1_IRQHandler(void){
//	EXTI->PR1 |= EXTI_PR1_PIF1;

//	Green_LED_Toggle();
//}

//void EXTI2_IRQHandler(void){
//	EXTI->PR1 |= EXTI_PR1_PIF2;
//	
//	midThrottle();
//}

//PA3, up
void EXTI3_IRQHandler(void){
	EXTI->PR1 |= EXTI_PR1_PIF3;
	
	increaseThrottle();
}

//PA5, down
void EXTI9_5_IRQHandler(void){
	EXTI->PR1 |= EXTI_PR1_PIF5;
	
	decreaseThrottle();
}

