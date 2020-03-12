
#include "stm32l476xx.h"
#include "buttonInterrupts.h"
#include "throttle.h"
#include "initializations.h"
#include "SysTimer.h"
#include "nRF24L01.h"
#include "SPI.h"


int main() {
	// Initialization
	clock_inits();
	joystick_init();
	interrupt_init();
	pwm_init();
	SysTick_Init();
	TRX_Init();
	
	while(1);
	
	return 0;
}
