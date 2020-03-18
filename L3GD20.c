#include "L3GD20.h"
#include "SPI.h"

// Modifed from l3gd20.c V2.0.0, COPYRIGHT(c) 2015 STMicroelectronics

void GYRO_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Initialize SPI
	SPI2_GPIO_Init();
	SPI2_Init();

	// Initialize Gyroscope
	GYRO_IO_CS_Init();
	L3GD20_Init();
}

// Gyroscope IO functions
void GYRO_IO_CS_Init(void)
{
	// ENABLE CLOCK????????????????????

	// GPIO output mode for pin 7
	GPIOD->MODER &= ~GPIO_MODER_MODE7_1;
	GPIOD->MODER |= GPIO_MODER_MODE7_0;

	// set output type as push-pull
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT7;

	// set output speed to very high
	GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEED7;

	// set to no pull-up, pull-down
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD7;

	// Deselect the Gyroscope
	L3GD20_CS_HIGH;
}

void GYRO_IO_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite)
{

	uint8_t rxBuffer[32];

	/* Configure the MS bit: 
       - When 0, the address will remain unchanged in multiple read/write commands.
       - When 1, the address will be auto incremented in multiple read/write commands.
	*/
	if (NumByteToWrite > 0x01)
	{
		WriteAddr |= (uint8_t)MULTIPLEBYTE_CMD; // Set write mode & auto-increment
	}

	// Set chip select Low at the start of the transmission
	L3GD20_CS_LOW; // Gyro CS low
	SPI_Delay(10);

	// Send the Address of the indexed register
	SPI_Write(SPI2, &WriteAddr, rxBuffer, 1);

	// Send the data that will be written into the device (MSB First)
	SPI_Write(SPI2, pBuffer, rxBuffer, NumByteToWrite);

	// Set chip select High at the end of the transmission
	SPI_Delay(10); // Gyro CS high
	L3GD20_CS_HIGH;
}

void GYRO_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint8_t NumByteToRead)
{

	uint8_t rxBuffer[32];

	uint8_t AddrByte = ReadAddr | ((uint8_t)0xC0); // set read mode & autoincrement

	// Set chip select Low at the start of the transmission
	L3GD20_CS_LOW; // Gyro CS low
	SPI_Delay(10);

	// Send the Address of the indexed register
	SPI_Write(SPI2, &AddrByte, rxBuffer, 1);

	// Receive the data that will be read from the device (MSB First)
	SPI_Read(SPI2, pBuffer, NumByteToRead);

	// Set chip select High at the end of the transmission
	SPI_Delay(10); // Gyro CS high
	L3GD20_CS_HIGH;
}

void L3GD20_Init(void)
{
	// TODO
	uint8_t tempBuffer;
	tempBuffer = 0x3F;
	// bits to write to Gyro CTRL_REG1
	GYRO_IO_Write(&tempBuffer, L3GD20_CTRL_REG1_ADDR, 1);
	tempBuffer = 0x30; // 00110000
	// bits to write to Gyro CTRL_REG4
	GYRO_IO_Write(&tempBuffer, L3GD20_CTRL_REG4_ADDR, 1);
}
