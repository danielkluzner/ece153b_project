

#include "stm32l476xx.h"
#include "buttonInterrupts.h"
#include "throttle.h"
#include "initializations.h"



int main() {
	// Initialization
	void clock_inits();
	void joystick_init();
	void interrupt_init();
	void pwm_init();
	
	while(1);
	
	return 0;
}

