
#include "SysTimer.h"
#include "INA260.h"

volatile uint32_t msTicks;
volatile uint8_t updateTicks = 0;

//******************************************************************************************
// Initialize SysTick
//******************************************************************************************
void SysTick_Init(void)
{
	// The RCC feeds the Cortex System Timer (SysTick) external clock with the AHB clock
	// (HCLK) divided by 8. The SysTick can work either with this clock or with the Cortex clock
	// (HCLK), configurable in the SysTick Control and Status Register.

	//  SysTick Control and Status Register
	SysTick->CTRL = 0; // Disable SysTick IRQ and SysTick Counter

	// SysTick Reload Value Register - f_clock = 80MHz
	SysTick->LOAD = 80000000 / 1000 - 1; // t_systick = 1 ms (1000 us)

	// SysTick Current Value Register
	SysTick->VAL = 0;

	NVIC_SetPriority(SysTick_IRQn, 1); // Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);	  // Enable EXTI0_1 interrupt in NVIC

	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does not assert the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	// Select processor clock
	// 1 = processor clock;  0 = external clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

//******************************************************************************************
// SysTick Interrupt Handler
//******************************************************************************************
void SysTick_Handler(void)
{ //interrupt every 1 ms (1000 us) as per SysTick_LOAD value
	msTicks++;

	//	if (++updateTicks == 25)
	//	{ //gyro has updated 19 times in 25 ms
	//read_last_angle_and_throttle_received();
	//update_current_angle();
	//stabilize_at_received_angle_and_throttle();
	//		updateTicks = 0;
	//	}
	//	INA260_read();
}

//******************************************************************************************
// Delay in ms
//******************************************************************************************
void delay(uint32_t T)
{
	uint32_t curTicks;

	curTicks = msTicks;
	while ((msTicks - curTicks) < T)
	{
	};

	msTicks = 0;
}
