#include "SPI.h"
#include "SysTimer.h"
#include "nRF24L01.h"
#include "LCD.h"

// Note: When the data frame size is 8 bit, "SPIx->DR = byte_data;" works incorrectly.
// It mistakenly send two bytes out because SPIx->DR has 16 bits. To solve the program,
// we should use "*((volatile uint8_t*)&SPIx->DR) = byte_data";

// LSM303C eCompass (a 3D accelerometer and 3D magnetometer module) SPI Interface:
//   MAG_DRDY = PC2   MEMS_SCK  = PD1 (SPI2_SCK)   XL_CS  = PE0
//   MAG_CS   = PC0   MEMS_MOSI = PD4 (SPI2_MOSI)  XL_INT = PE1
//   MAG_INT  = PC1
//
// L3GD20 Gyro (three-axis digital output) SPI Interface:
//   MEMS_SCK  = PD1 (SPI2_SCK)    GYRO_CS   = PD7 (GPIO)
//   MEMS_MOSI = PD4 (SPI2_MOSI)   GYRO_INT1 = PD2
//   MEMS_MISO = PD3 (SPI2_MISO)   GYRO_INT2 = PB8

void SPI1_GPIO_Init(void)
{

	//XPB2 = SPI IRQ
	//PE11 = CE - GPIO output
	//PE12 = CSN - GPIO output
	//PE13 = SCK - SPI
	//PE14 = MISO - SPI
	//PE15 = MOSI - SPI

	//SPI port pins clock enable
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	//	//PB2 input mode for SPI IRQ
	//	GPIOB->MODER &= ~GPIO_MODER_MODE2;
	//	GPIOB->PUPDR |= GPIO_PUPDR_PUPD2_1;
	//	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD2_0;

	// GPIO output mode for pins 11, 12
	GPIOE->MODER &= ~GPIO_MODER_MODE11_1;
	GPIOE->MODER |= GPIO_MODER_MODE11_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE12_1;
	GPIOE->MODER |= GPIO_MODER_MODE12_0;

	// GPIO AF mode for pins E 13, 14, 15
	GPIOE->MODER &= ~GPIO_MODER_MODE13;
	GPIOE->MODER |= GPIO_MODER_MODE13_1;
	GPIOE->MODER &= ~GPIO_MODER_MODE14;
	GPIOE->MODER |= GPIO_MODER_MODE14_1;
	GPIOE->MODER &= ~GPIO_MODER_MODE15;
	GPIOE->MODER |= GPIO_MODER_MODE15_1;

	// choose AF5 for all three pins
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL13;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL13_0;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL13_2;
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL14;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL14_0;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL14_2;
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL15;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL15_0;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL15_2;

	// set output type as push-pull
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT11;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT12;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT13;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT14;
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT15;

	// set output speed to very high
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED11;
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED12;
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED14;
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED15;

	// set to no pull-up, pull-down
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD11;
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD12;
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD14;
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD15;
}

void SPI2_GPIO_Init(void)
{

	//SPI port pins clock enable
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;

	// GPIO AF mode for pins 1, 3, 4
	GPIOD->MODER &= ~GPIO_MODER_MODE1;
	GPIOD->MODER |= GPIO_MODER_MODE1_1;
	GPIOD->MODER &= ~GPIO_MODER_MODE3;
	GPIOD->MODER |= GPIO_MODER_MODE3_1;
	GPIOD->MODER &= ~GPIO_MODER_MODE4;
	GPIOD->MODER |= GPIO_MODER_MODE4_1;

	// choose AF5 for all three pins
	GPIOD->AFR[0] &= ~GPIO_AFRL_AFSEL1;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL1_0;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL1_2;
	GPIOD->AFR[0] &= ~GPIO_AFRL_AFSEL3;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL3_0;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL3_2;
	GPIOD->AFR[0] &= ~GPIO_AFRL_AFSEL4;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL4_0;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL4_2;

	// set output type as push-pull
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT1;
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT3;
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT4;

	// set output speed to very high
	GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEED1;
	GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;
	GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEED4;

	// set to no pull-up, pull-down
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD1;
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD3;
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD4;
}

void SPI1_Init(void)
{
	// enable clock for SPI1 register write/read
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	// reset SPI1
	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;

	// Afterwards, clear the bits so that SPI1
	// does not remain in a reset state
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST; //have to wait?

	//ensure SPI is disabled
	//SPI control register 1
	//SPE: SPI enable;
	//0: disabled
	//1: enabled
	SPI1->CR1 &= ~SPI_CR1_SPE;

	//configure serial channel for full duplex comm.
	//pg 1300
	SPI1->CR1 &= ~SPI_CR1_RXONLY;

	//configure communication for 2-line unidirectional data mode
	SPI1->CR1 &= ~SPI_CR1_BIDIMODE;

	//disable the output in bidirectional mode
	SPI1->CR1 &= ~SPI_CR1_BIDIOE;

	//set frame format for receiving the MSB first
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;

	//set data length to 8 bits
	SPI1->CR2 |= SPI_CR2_DS;	// 1111
	SPI1->CR2 &= ~SPI_CR2_DS_3; //0111

	//set frame format to SPI Motorola mode
	SPI1->CR2 &= ~SPI_CR2_FRF;

	//set clk polarity to 0 (0 when idle)
	SPI1->CR1 &= ~SPI_CR1_CPOL;

	//set clock phase s.t. first clk
	// transition is first data capture edge
	SPI1->CR1 &= ~SPI_CR1_CPHA;

	//set baud prescaler to 16
	SPI1->CR1 |= SPI_CR1_BR;	//111
	SPI1->CR1 &= ~SPI_CR1_BR_2; //011

	//disable CRC calculation
	SPI1->CR1 &= ~SPI_CR1_CRCEN;

	//set board to operate in master mode
	SPI1->CR1 |= SPI_CR1_MSTR;

	//enable software slave management
	SPI1->CR1 |= SPI_CR1_SSM;

	//enable NSS pulse management
	SPI1->CR2 |= SPI_CR2_NSSP;

	//set the internal slave select bit
	SPI1->CR1 |= SPI_CR1_SSI; //1 = SET?

	//set the FIFO reception threshold to 1/4 (8 bit)
	SPI1->CR2 |= SPI_CR2_FRXTH;

	//enable SPI
	SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI2_Init(void)
{
	// enable clock for SPI2
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;

	// reset SPI2
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_SPI2RST;

	// Afterwards, clear the bits so that SPI2
	// does not remain in a reset state
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_SPI2RST;

	//ensure SPI is disabled
	//SPI control register 1
	//SPE: SPI enable;
	//0: disabled
	//1: enabled
	SPI2->CR1 &= ~SPI_CR1_SPE;

	//configure serial channel for full duplex comm.
	//pg 1300
	SPI2->CR1 &= ~SPI_CR1_RXONLY;

	//configure communication for 2-line unidirectional data mode
	SPI2->CR1 &= ~SPI_CR1_BIDIMODE;

	//disable the output in bidirectional mode
	SPI2->CR1 &= ~SPI_CR1_BIDIOE;

	//set frame format for receiving the MSB first
	SPI2->CR1 &= ~SPI_CR1_LSBFIRST;

	//set data length to 8 bits
	SPI2->CR2 |= SPI_CR2_DS;	// 1111
	SPI2->CR2 &= ~SPI_CR2_DS_3; //0111

	//set frame format to SPI Motorola mode
	SPI2->CR2 &= ~SPI_CR2_FRF;

	//set clk polarity to 0 (0 when idle)
	SPI2->CR1 &= ~SPI_CR1_CPOL;

	//set clock phase s.t. first clk
	// transition is first data capture edge
	SPI2->CR1 &= ~SPI_CR1_CPHA;

	//set baud prescaler to 16
	//80MHz->5MHz
	SPI2->CR1 |= SPI_CR1_BR;	//111
	SPI2->CR1 &= ~SPI_CR1_BR_2; //011

	//disable CRC calculation
	SPI2->CR1 &= ~SPI_CR1_CRCEN;

	//set board to operate in master mode
	SPI2->CR1 |= SPI_CR1_MSTR;

	//enable software slave management
	SPI2->CR1 |= SPI_CR1_SSM;

	//enable NSS pulse management
	SPI2->CR2 |= SPI_CR2_NSSP;

	//set the internal slave select bit
	SPI2->CR1 |= SPI_CR1_SSI;

	//set the FIFO reception threshold to 1/4 (8 bit)
	SPI2->CR2 |= SPI_CR2_FRXTH;

	//enable SPI
	SPI2->CR1 |= SPI_CR1_SPE;
}

void SPI_Write(SPI_TypeDef *SPIx, uint8_t *txBuffer, uint8_t *rxBuffer, int size)
{
	volatile uint32_t tmpreg;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		while ((SPIx->SR & SPI_SR_TXE) != SPI_SR_TXE)
			; // Wait for TXE (Transmit buffer empty)
		*((volatile uint8_t *)&SPIx->DR) = txBuffer[i];
		while ((SPIx->SR & SPI_SR_RXNE) != SPI_SR_RXNE)
			; // Wait for RXNE (Receive buffer not empty)
		rxBuffer[i] = *((__IO uint8_t *)&SPIx->DR);
	}
	while ((SPIx->SR & SPI_SR_BSY) == SPI_SR_BSY)
		; // Wait for BSY flag cleared
}

void SPI_Read(SPI_TypeDef *SPIx, uint8_t *rxBuffer, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		while ((SPIx->SR & SPI_SR_TXE) != SPI_SR_TXE)
			; // Wait for TXE (Transmit buffer empty)
		*((volatile uint8_t *)&SPIx->DR) = rxBuffer[i];
		// The clock is controlled by master. Thus the master has to send a byte
		// data to the slave to start the clock.
		while ((SPIx->SR & SPI_SR_RXNE) != SPI_SR_RXNE)
			;
		rxBuffer[i] = *((__IO uint8_t *)&SPIx->DR);
	}
	while ((SPIx->SR & SPI_SR_BSY) == SPI_SR_BSY)
		; // Wait for BSY flag cleared
}

void SPI_Delay(uint32_t us)
{
	uint32_t i, j;
	for (i = 0; i < us; i++)
	{
		for (j = 0; j < 18; j++) // This is an experimental value.
			(void)i;
	}
}

void SPIx_IRQHandler(SPI_TypeDef *SPIx, uint8_t *buffer, uint8_t *counter)
{
	if (SPIx->SR & SPI_SR_RXNE)
	{ //	SPI Busy
		buffer[*counter] = SPIx->DR;
		// Reading SPI_DR automatically clears the RXNE flag
		(*counter)++;
		if ((*counter) >= BufferSize)
		{
			(*counter) = 0;
		}
	}
}
