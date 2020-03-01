

#include "throttle.h"

void increaseThrottleTenPercent(void){

	if ((TIM1->CCR1 + 10) >= 249){
		TIM1->CCR1 = 249;
	}else if(TIM1->CCR1 <125){
		TIM1->CCR1 = 125;
	}else{
	TIM1->CCR1 += 30;
	}
//	TIM1->CCR1 = 0;
}
void decreaseThrottleTenPercent(void){

	if ((TIM1->CCR1 - 30) <= 100){
		TIM1->CCR1 = 125;
	}else if(TIM1->CCR1 <125){
		TIM1->CCR1 = 125;
	}else{
	TIM1->CCR1 -= 30;
	}
//	TIM1->CCR1 = 0;
}

void midThrottle(void){
	
	TIM1->CCR1 = 197;
	
}

