
#include "buttonInterrupts.h"

void EXTI0_IRQHandler(void)
{
	EXTI->PR1 |= EXTI_PR1_PIF0;

	killThrottle();
}

void EXTI1_IRQHandler(void)
{ //left
	EXTI->PR1 |= EXTI_PR1_PIF1;

	INA260_read();
	// LCD_Clear();
	// LCD_DisplayString("left");
}

void EXTI2_IRQHandler(void)
{ //right
	EXTI->PR1 |= EXTI_PR1_PIF2;

	TRX_Read_Status();
	// LCD_Clear();
	// LCD_DisplayString("right");
}

//PA3, up
void EXTI3_IRQHandler(void)
{ //up
	EXTI->PR1 |= EXTI_PR1_PIF3;

	increaseThrottle();
	LCD_Clear();
	LCD_DisplayString("up");
}

//PA5, down
void EXTI9_5_IRQHandler(void)
{ //down
	EXTI->PR1 |= EXTI_PR1_PIF5;

	decreaseThrottle();
	LCD_Clear();
	LCD_DisplayString("down");
}
