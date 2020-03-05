

#include "throttle.h"

void increaseThrottleTenPercent(void){

	if ((TIM2->CCR3 + 20) >= 249){
		TIM2->CCR2 = 250;
		TIM2->CCR3 = 250;
		TIM1->CCR3 = 250;
		TIM1->CCR4 = 250;
	}else{
	TIM2->CCR2 += 20;
	TIM2->CCR3 += 20;
	TIM1->CCR3 += 20;
	TIM1->CCR4 += 20;
	}
	//TIM2->CCR2 = 250;
	//TIM2->CCR3 = 250;
	//TIM1->CCR3 = 250;
	//TIM1->CCR4 = 250;
}
void decreaseThrottleTenPercent(void){

	if ((TIM2->CCR3 - 20) <= 125){
		TIM2->CCR2 = 125;
		TIM2->CCR3 = 125;
		TIM1->CCR3 = 125;
		TIM1->CCR4 = 125;
	}else{
	TIM2->CCR2 -= 20;
	TIM2->CCR3 -= 20;
	TIM1->CCR3 -= 20;
	TIM1->CCR4 -= 20;
	}
	//TIM2->CCR2 = 125;
	//TIM2->CCR3 = 125;
	//TIM1->CCR3 = 125;
	//TIM1->CCR4 = 125;
}

