

#include "stm32l476xx.h"
#include "buttonInterrupts.h"
#include "throttle.h"
#include "initializations.h"
#include "I2C.h"
#include "LCD.h"
#include "SysCLock.h"
#include "INA260.h"
#include "SysTimer.h"
#include "L3GD20.h"
#include "angle.h"

int main()
{
	// Initialization
	clock_init();
	//	System Clock = 80 MHz
	System_Clock_Init();
	joystick_init();
	interrupt_init();
	pwm_init();
	I2C_GPIO_Init();
	I2C_Initialization();
	LCD_Initialization();
	LCD_Clear();
	INA260_init();
	GYRO_Init();
	SysTick_Init();
	

	return 0;
}
