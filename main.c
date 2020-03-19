
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
#include <string.h>


int main() {
	// Initialization
	System_Clock_Init();
	SysTick_Init();
	clock_inits();
	joystick_init();
	SPI_Interrupt_Init();
	interrupt_init();
	//pwm_init();
	LCD_Initialization();
	TRX_Init();
	
	char RX_Data[32];
	uint8_t read[32];
	
	//sendData(&write, 1);
	
	while(1);
	while(1){
		
		// RECEIVER (CHRIS'S BOARD)
		receiveData(read, 32);
		sprintf(RX_Data, "%s", "-");
		LCD_DisplayString((uint8_t*) RX_Data);
		delay(1000);
		LCD_Clear();
		*read = 0;
		strcpy(RX_Data, "");
		TRX_IO_Read(read, 0x07, 1);
		sprintf(RX_Data, "%x", *read);
		LCD_DisplayString((uint8_t*) RX_Data);
		delay(1000);
		LCD_Clear();		
	}
	
	return 0;
}
