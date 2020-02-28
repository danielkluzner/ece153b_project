

#include "throttle.h"

void increaseThrottleTenPercent(void){

//	if ((TIM2->CCR1 + 100) >= 2499){
//		TIM2->CCR1 = 2000;
//	}else{
//	TIM2->CCR1 += 200;
//	}
	TIM1->CCR1 = 1000;
}
void decreaseThrottleTenPercent(void){

//	if ((TIM2->CCR1 - 100) <= 1000){
//		TIM2->CCR1 = 1000;
//	}else{
//	TIM2->CCR1 -= 200;
//	}
	TIM1->CCR1 = 125;
}

