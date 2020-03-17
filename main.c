
#include "stm32l476xx.h"
#include "buttonInterrupts.h"
#include "throttle.h"
#include "initializations.h"
#include "SysTimer.h"
#include "SysClock.h"
#include "nRF24L01.h"
#include "SPI.h"
#include "LCD.h"
#include <stdio.h>


int main() {
	// Initialization
	System_Clock_Init();
	SysTick_Init();
	clock_inits();
	joystick_init();
	interrupt_init();
	pwm_init();
	LCD_Initialization();
	TRX_Init();
	
	char RX_Data[8] = {"5"};
	uint8_t read = 4;
	uint8_t write = 2;
	
	PAYLOAD_Write(&write, 1);
	
	while(1){
		
		// RECEIVER (CHRIS'S BOARD)
		LCD_DisplayString((uint8_t*) RX_Data);
		for(int i = 0; i < 10000000; i++);
		sprintf(RX_Data, "%d", read);
		LCD_DisplayString((uint8_t*) RX_Data);
		for(int i = 0; i < 10000000; i++);
		PAYLOAD_Read(&read, 1);
		sprintf(RX_Data, "%d", read);
		LCD_DisplayString((uint8_t*) RX_Data);
		for(int i = 0; i < 10000000; i++);
		
		
		
		// TRANSMITTER (DANIEL'S BOARD)

		
	}
	
	return 0;
}
