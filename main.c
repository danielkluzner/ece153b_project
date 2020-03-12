

#include "stm32l476xx.h"
#include "buttonInterrupts.h"
#include "throttle.h"
#include "initializations.h"
#include "I2C.h"
#include "LCD.h"
#include "SysCLock.h"

int main()
{
	// Initialization
	clock_inits();
	//  System Clock = 80 MHz
	System_Clock_Init();
	joystick_init();
	interrupt_init();
	pwm_init();
	LCD_Initialization();
	LCD_Clear();

	// Initialize I2C
	I2C_GPIO_Init();
	I2C_Initialization();

#define INA260_I2CADDR_DEFAULT 0x80 ///< INA260 default i2c address
#define INA260_REG_BUSVOLTAGE 0x02  //voltage register address

	char message[2] = {0};
	uint8_t SlaveAddress = INA260_I2CADDR_DEFAULT;
	uint8_t *voltageRegisterAddress;
	*voltageRegisterAddress = INA260_REG_BUSVOLTAGE;
	uint8_t Data_Receive[2] = {0};
	uint16_t voltageRegisterValue = 0;
	uint8_t Data_Send[1] = {0};
	float voltage = 0.0;

	I2C_SendData(I2C1, SlaveAddress, voltageRegisterAddress, 1);

	while (1)
	{
//		I2C_ReceiveData(I2C1, SlaveAddress, Data_Receive, 2);
//		voltageRegisterValue |= Data_Receive[0] << 8;
//		voltageRegisterValue |= Data_Receive[1];
//		
//		voltage = voltageRegisterValue * 1.25 / 1000.0;

//		sprintf(message, "%.2f", voltage);
//		LCD_DisplayString((uint8_t *)message);
//		voltage = 0.0;
//		voltageRegisterValue = 0;


	};

	return 0;
}
