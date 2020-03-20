#include "nRF24L01.h"

void TX_Init(void)
{

	// Initialize SPI
	SPI1_GPIO_Init();
	SPI1_Init();

	// Initialize Transceiver
	// Deselect the Transceiver
	nRF24L01_CSN_HIGH;
	nRF24L01_Init();

	//set PWR_ON and PRIM_RX bits high
	//->TX mode
	uint8_t regSetValue = 0b00001010;
	TRX_IO_Write(&regSetValue, nRF24L01_CONFIG, 1);

	//1.5ms settling time before entering TX or RX mode
	//130us settling time before entering RX mode
	delay(2); //2ms delay for settling times

	nRF24L01_Init();
}
void RX_Init(void)
{

	// Initialize SPI
	SPI1_GPIO_Init();
	SPI1_Init();
	//	SPI1_IRQ_Init();

	nRF24L01_Init();
	// Deselect the Transceiver
	nRF24L01_CSN_HIGH;
	//Enable nRF24L01 for RX mode only: remains enabled
	nRF24L01_CE_ON;

	//set PWR_ON bit high, keep PRIM_RX low
	//->RX mode
	uint8_t regSetValue = 0b00001011;
	TRX_IO_Write(&regSetValue, nRF24L01_CONFIG, 1);

	//1.5ms settling time before entering Standby 1 Mode
	//130us settling time before entering TX or RX mode
	delay(2); //2ms delay for settling times
}

void sendData(uint8_t *pBuffer, uint8_t NumByteToWrite)
{
	uint8_t rxBuffer[32];

	uint8_t AddrByte = 0xa0; // set write mode

	// Set chip select Low at the start of the transmission
	nRF24L01_CSN_LOW; // TRX CS low
	SPI_Delay(10);

	// Send the Address of the indexed register
	SPI_Write(SPI1, &AddrByte, rxBuffer, 1);

	// Send the data that will be written into the device (MSB First)
	SPI_Write(SPI1, pBuffer, rxBuffer, NumByteToWrite);

	// Set chip select High at the end of the transmission
	SPI_Delay(10);
	nRF24L01_CSN_HIGH; // TRX CSN high
}

void receiveData(uint8_t *pBuffer, uint8_t NumByteToRead)
{
	uint8_t rxBuffer[32];

	uint8_t AddrByte = 0x61; // set read mode

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

void TRX_IO_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite)
{

	uint8_t rxBuffer[32];

	uint8_t AddrByte = WriteAddr | ((uint8_t)0x20); // set write mode & autoincrement

	// Set chip select Low at the start of the transmission
	nRF24L01_CSN_LOW; // TRX CS low
	SPI_Delay(10);

	// Send the Address of the indexed register
	SPI_Write(SPI1, &AddrByte, rxBuffer, 1);

	// Send the data that will be written into the device (MSB First)
	SPI_Write(SPI1, pBuffer, rxBuffer, NumByteToWrite);

	// Set chip select High at the end of the transmission
	SPI_Delay(10);
	nRF24L01_CSN_HIGH; // TRX CSN high
}

void TRX_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint8_t NumByteToRead)
{

	uint8_t rxBuffer[32];

	uint8_t AddrByte = ReadAddr & ((uint8_t)0x1f); // set read mode & autoincrement

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

void nRF24L01_Init(void)
{
	uint8_t tempBuffer;

	//set auto retransmit delay to .5ms,
	//allow 15 retransmits on AA fail
	tempBuffer = 0b00011111;
	TRX_IO_Write(&tempBuffer, 0x04, 1);

	// change data rate to 1 Mbps, output power to 0dBm
	tempBuffer = 0b00000110;
	TRX_IO_Write(&tempBuffer, 0x06, 1);

	// set frequency
	tempBuffer = 0x03; // 00000011
	TRX_IO_Write(&tempBuffer, 0x05, 1);

	// set payload width of data pipe 0 to 32 byte
	tempBuffer = 0x20; // 00100000
	TRX_IO_Write(&tempBuffer, 0x11, 1);

	//Disable the "Auto ACK Disable" function for data pipe 0
	//(Enabling Auto Ack for Data Pipe 0)
	tempBuffer = 0b00000000;
	TRX_IO_Write(&tempBuffer, 0x01, 1);
}

void TRX_Read_Status(void)
{

	uint8_t status[1];
	TRX_IO_Read(status, nRF24L01_STATUS, 1);
	char str[1];
	sprintf(str, "%x", *status);
	LCD_Clear();
	LCD_DisplayString(str);
}
