

#include "stm32l476xx.h"
#include "buttonInterrupts.h"
#include "throttle.h"
#include "initializations.h"



int main() {
	// Initialization
	clock_inits();
	joystick_init();
	interrupt_init();
	pwm_init();
	
	while(1);
	
	return 0;
}

