#include "nRF24L01.h"
#include "SPI.h"

void TRX_Init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	// Initialize SPI
	SPI1_GPIO_Init();
	SPI_Init();
	
	// Initialize Transceiver
	TRX_IO_Init();
	nRF24L01_Init();
}

// Transceiver IO functions
void TRX_IO_Init(void) {
    
    // E11 = CE
    // E12 = CSN
    
    // GPIO output mode for pins 11, 12
		GPIOE->MODER &= ~GPIO_MODER_MODE11_1;
    GPIOE->MODER |= GPIO_MODER_MODE11_0;
    GPIOE->MODER &= ~GPIO_MODER_MODE12_1;
    GPIOE->MODER |= GPIO_MODER_MODE12_0;
    
    // set output type as push-pull
		GPIOE->OTYPER &= ~GPIO_OTYPER_OT11;
    GPIOE->OTYPER &= ~GPIO_OTYPER_OT12;
    
    // set output speed to very high
		GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED11;
    GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED12;
    
    // set to no pull-up, pull-down
		GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD11;
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD12;
    
    // Deselect the Transceiver
    nRF24L01_CSN_HIGH;
		// Enable nRF24L01
		nRF24L01_CE_ON;
}

void sendData(uint8_t *pBuffer, uint8_t NumByteToWrite){
	uint8_t rxBuffer[32];
	
	uint8_t AddrByte = 0xa0;  // set write mode
	
	// Set chip select Low at the start of the transmission 
	nRF24L01_CSN_LOW;  // TRX CS low
	SPI_Delay(10);  
	
	// Send the Address of the indexed register 
	SPI_Write(SPI1, &AddrByte, rxBuffer, 1);
	
	// Send the data that will be written into the device (MSB First) 
	SPI_Write(SPI1, pBuffer, rxBuffer, NumByteToWrite);
  
	// Set chip select High at the end of the transmission  
	SPI_Delay(10);
	nRF24L01_CSN_HIGH; // TRX CSN high
}

void receiveData(uint8_t *pBuffer, uint8_t NumByteToRead){
	uint8_t rxBuffer[32];
	
	uint8_t AddrByte = 0x61;  // set read mode
	
	// Set chip select Low at the start of the transmission 
	nRF24L01_CSN_LOW; // TRX CS low
	SPI_Delay(10);
	
	// Send the Address of the indexed register 
	SPI_Write(SPI1, &AddrByte, rxBuffer, 1);
	
	// Receive the data that will be read from the device (MSB First) 
	SPI_Read(SPI1, pBuffer, NumByteToRead);
  
	// Set chip select High at the end of the transmission  
	SPI_Delay(10);
	nRF24L01_CSN_HIGH; // TRX CSN high
}

void TRX_IO_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite){
	
	uint8_t rxBuffer[32];
	
	uint8_t AddrByte = WriteAddr | ((uint8_t) 0x20);  // set write mode & autoincrement
	
	// Set chip select Low at the start of the transmission 
	nRF24L01_CSN_LOW;  // TRX CS low
	SPI_Delay(10);  
	
	// Send the Address of the indexed register 
	SPI_Write(SPI1, &AddrByte, rxBuffer, 1);
	
	// Send the data that will be written into the device (MSB First) 
	SPI_Write(SPI1, pBuffer, rxBuffer, NumByteToWrite);
  
	// Set chip select High at the end of the transmission  
	SPI_Delay(10);
	nRF24L01_CSN_HIGH; // TRX CSN high
}

void TRX_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint8_t NumByteToRead){

	uint8_t rxBuffer[32];
	
	uint8_t AddrByte = ReadAddr & ((uint8_t) 0x1f);  // set read mode & autoincrement
	
	// Set chip select Low at the start of the transmission 
	nRF24L01_CSN_LOW; // TRX CS low
	SPI_Delay(10);
	
	// Send the Address of the indexed register 
	SPI_Write(SPI1, &AddrByte, rxBuffer, 1);
	
	// Receive the data that will be read from the device (MSB First) 
	SPI_Read(SPI1, pBuffer, NumByteToRead);
  
	// Set chip select High at the end of the transmission  
	SPI_Delay(10);
	nRF24L01_CSN_HIGH; // TRX CSN high
}	


void nRF24L01_Init(void) {
	// TODO
	uint8_t tempBuffer;
	
	// change data rate to 1 Mbps
	tempBuffer = 0x06; // 00000110
	TRX_IO_Write(&tempBuffer, nRF24L01_RF_SETUP, 1);
	// set frequency
	tempBuffer = 0x03; // 00000011
	TRX_IO_Write(&tempBuffer, nRF24L01_RF_CH, 1);
	
	/*
	tempBuffer = 0x3f; // 00111111
	TRX_IO_Write(&tempBuffer, nRF24L01_EN_RXADDR, 1);
	*/
	
	// set payload width of data pipe 5 to 32 byte
	tempBuffer = 0x20; // 00100000
	TRX_IO_Write(&tempBuffer, nRF24L01_RX_PW_P0, 1);
	
	/*
	uint8_t ugh[5] = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7};
	TRX_IO_Write(ugh, 0x0b, 5);
	*/
	
	// RX mode (PRIM_RX = 1)
	tempBuffer = 0x0b; // 00001011
	// TX mode (PRIM_RX = 0)
	//tempBuffer = 0x0a; // 00001010
	
	TRX_IO_Write(&tempBuffer, nRF24L01_CONFIG, 1);
}	
