

#include "stm32l476xx.h"
#include "SysCLock.h"
#include "SysTimer.h"
#include "LCD.h"
#include "initializations.h"
#include "buttonInterrupts.h"
#include "throttle.h"
#include "I2C.h"
#include "SPI.h"
#include "INA260.h"
#include "nRF24L01.h"
#include "L3GD20.h"
#include "angle.h"
#include "PWM_Motor_Signals.h"

//extern volatile float x;

int main()
{
	// Initialization
	//	System Clock = 80 MHz
	System_Clock_Init();
	SysTick_Init();
	LCD_Initialization();

	clock_init();

	//Uncomment for joystick functions
	//joystick_init();
	//interrupt_init();
	Motor_PWM_Init();

	INA260_init();
	RX_Init();
	//GYRO_Init();

	LCD_DisplayString("start");

	int i = 0;

	while (1)
	{
		//**********************//
		//THROTTLE DEMONSTRATION//
		//**********************//

		// TIM2->CCR1 = (125 * 5);
		// TIM2->CCR2 = (125 * 5);
		// TIM2->CCR3 = (125 * 5);
		// TIM2->CCR4 = (125 * 5);
		// delay(500);
		// TIM2->CCR1 = (150 * 5);
		// TIM2->CCR2 = (150 * 5);
		// TIM2->CCR3 = (150 * 5);
		// TIM2->CCR4 = (150 * 5);
		// delay(500);
		// killThrottle();

		// delay(2000);
		// killThrottle();
		// delay(1000);
		// for (i = 0; i < 10; i++)
		// {
		// 	increaseThrottle();
		// 	increaseThrottle();
		// 	delay(1000);
		// }
		// for (i = 0; i < 10; i++)
		// {
		// 	decreaseThrottle();
		// 	decreaseThrottle();
		// 	delay(1000);
		// }

		// killThrottle();
		// return 0;
	};

	return 0;
}
