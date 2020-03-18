#include "nRF24L01.h"

void TRX_TX_Init(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  // Initialize SPI
  SPI1_GPIO_Init();
  SPI1_Init();

  // Initialize Transceiver
  TRX_IO_Init();
  nRF24L01_TX_Init();
}

void TRX_RX_Init(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  // Initialize SPI
  SPI1_GPIO_Init();
  SPI1_Init();

  // Initialize Transceiver
  TRX_IO_Init();
  nRF24L01_RX_Init();
}

// Transceiver IO functions
void TRX_IO_Init(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

  // E11 = CE - chip enable
  // E12 = CSN - ~chip select

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

  // Select the Transceiver
  nRF24L01_CSN_HIGH;
  // Enable nRF24L01
  nRF24L01_CE_ON;
}

void sendData(uint8_t *pBuffer, uint8_t NumByteToWrite)
{
  uint8_t rxBuffer[32];
  uint8_t command;
  // Set chip select Low at the start of the transmission
  nRF24L01_CSN_LOW; // TRX CS low
  SPI_Delay(10);

  //flush tx fifo
  command = nRF24L01_FLUSH_TX;
  SPI_Write(SPI1, &command, rxBuffer, 1);

  SPI_Delay(10);
  nRF24L01_CSN_HIGH;
  SPI_Delay(10);
  nRF24L01_CSN_LOW;
  SPI_Delay(10);

  // command to write to TX_FIFO
  command = nRF24L01_W_TX_PAYLOAD;
  SPI_Write(SPI1, &command, rxBuffer, 1);

  // write pfBuffer to TX_FIFO (MSB First)
  SPI_Write(SPI1, pBuffer, rxBuffer, NumByteToWrite);

  // Set chip select High at the end of the transmission
  SPI_Delay(10);
  nRF24L01_CSN_HIGH; // TRX CSN high
}

void readRecievedData(uint8_t *pBuffer, uint8_t NumByteToRead)
{
  uint8_t rxBuffer[32];
  uint8_t command;

  //set CE low
  nRF24l01_CE_OFF;
  SPI_Delay(10);

  // Set chip select Low at the start of the transmission
  nRF24L01_CSN_LOW; // TRX CS low
  SPI_Delay(10);

  // Send the Address of the indexed register
  command = nRF24L01_R_RX_PAYLOAD; //read from RX_PLD
  SPI_Write(SPI1, &command, rxBuffer, 1);

  // Receive the data that will be read from the device (MSB First)
  SPI_Read(SPI1, pBuffer, NumByteToRead);

  // Set chip select High at the end of the transmission
  SPI_Delay(10);
  nRF24L01_CSN_HIGH; // TRX CSN high
  SPI_Delay(10);
  nRF24L01_CE_ON;
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

void nRF24L01_TX_Init(void)
{
  uint8_t tempBuffer;

  // change data rate to 1 Mbps
  tempBuffer = 0x00; // 00000000
  TRX_IO_Write(&tempBuffer, nRF24L01_W_RF_SETUP, 1);

  // set frequency
  tempBuffer = 0x02; // 00000010
  TRX_IO_Write(&tempBuffer, nRF24L01_W_RF_CH, 1);

  //enable dynamic payload length
  tempBuffer = 0x04; // 00000100
  TRX_IO_Write(&tempBuffer, nRF24L01_W_FEATURE, 1);

  //set DPL_P0 bit for transmitting to RX with DPL enabled
  tempBuffer = 0x01;
  TRX_IO_Write(&tempBuffer, nRF24L01_W_DYNDP, 1);

  // power up and RX mode (PRIM_RX = 1)
  // tempBuffer = 0x0b; // 00001011

  // power up and TX mode (PRIM_RX = 0)
  tempBuffer = 0x0a; // 00001010
  TRX_IO_Write(&tempBuffer, nRF24L01_W_CONFIG, 1);

  //2ms delay to cover start up and TX settling transition states
  delay(2);
}

void nRF24L01_RX_Init(void)
{
  uint8_t tempBuffer;

  // change data rate to 1 Mbps
  tempBuffer = 0x00; // 00000000
  TRX_IO_Write(&tempBuffer, 0x26, 1);

  // set frequency
  tempBuffer = 0x02; // 00000010
  TRX_IO_Write(&tempBuffer, nRF24L01_W_RF_CH, 1);

  //enable dynamic payload length
  tempBuffer = 0x04; // 00000100
  TRX_IO_Write(&tempBuffer, nRF24L01_W_FEATURE, 1);

  //set entire DYNPD register (RX mode requirement)
  tempBuffer = 0x3f;
  TRX_IO_Write(&tempBuffer, nRF24L01_W_DYNDP, 1);

  // power up and RX mode (PRIM_RX = 1)
  tempBuffer = 0x0b; // 00001011
  TRX_IO_Write(&tempBuffer, nRF24L01_W_CONFIG, 1);

  //2ms delay to cover start up and RX settling transition states
  delay(2);
}
