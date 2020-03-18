#ifndef __STM32L476G_DISCOVERY_nRF24L01
#define __STM32L476G_DISCOVERY_nRF24L01

#include "stm32l476xx.h"
#include "SPI.h"
#include "SysTimer.h"

//read register command words
#define nRF24L01_R_CONFIG 0x00 // Configuration Register Address
#define nRF24L01_R_EN_AA 0X01
#define nRF24L01_R_EN_RXADDR 0x02 // Enabled RX Register Address
#define nRF24L01_R_SETUP_AW 0x03  // Setup Address Width Register Adress
#define nRF24L01_R_SETUP_RETR 0x04
#define nRF24L01_R_RF_CH 0x05    // RF Channel (frequency)
#define nRF24L01_R_RF_SETUP 0x06 // RF Setup Register
#define nRF24L01_R_STATUS 0x07
#define nRF24L01_R_OBSERVE_TX 0x08
#define nRF24L01_R_RPD 0x09
#define nRF24L01_R_ADDR_P0 0x0a // Data Pipe 0 receive address
#define nRF24L01_R_RX_ADDR_P1 0x0b
#define nRF24L01_R_RX_ADDR_P2 0x0c
#define nRF24L01_R_RX_ADDR_P3 0x0d
#define nRF24L01_R_RX_ADDR_P4 0x0e
#define nRF24L01_R_RX_ADDR_P5 0x0f
#define nRF24L01_R_TX_ADDR 0x10  // Transmit address (TX Mode)
#define nRF24L01_R_RX_PW_P0 0x11 // Data Pipe 0 RX Payload Width
#define nRF24L01_R_RX_PW_P1 0x12
#define nRF24L01_R_RX_PW_P2 0x13
#define nRF24L01_R_RX_PW_P3 0x14
#define nRF24L01_R_RX_PW_P4 0x15
#define nRF24L01_R_RX_PW_P5 0x16
#define nRF24L01_R_FIFO_STATUS 0x17

#define nRF24L01_R_DYNDP 0x1c
#define nRF24L01_R_FEATURE 0x1d

//write to rewgister command wordsl
#define nRF24L01_W_CONFIG 0x00 | 0x20 // Configuration Register Address
#define nRF24L01_W_EN_AA 0X01 | 0x20
#define nRF24L01_W_EN_RXADDR 0x02 | 0x20 // Enabled RX Register Address
#define nRF24L01_W_SETUP_AW 0x03 | 0x20  // Setup Address Width Register Adress
#define nRF24L01_W_SETUP_RETR 0x04 | 0x20
#define nRF24L01_W_RF_CH 0x05 | 0x20    // RF Channel (frequency)
#define nRF24L01_W_RF_SETUP 0x06 | 0x20 // RF Setup Register
#define nRF24L01_W_STATUS 0x07 | 0x20
#define nRF24L01_W_OBSERVE_TX 0x08 | 0x20
#define nRF24L01_W_RPD 0x09 | 0x20
#define nRF24L01_W_RX_ADDR_P0 0x0a | 0x20 // Data Pipe 0 receive address
#define nRF24L01_W_RX_ADDR_P1 0x0b | 0x20
#define nRF24L01_W_RX_ADDR_P2 0x0c | 0x20
#define nRF24L01_W_RX_ADDR_P3 0x0d | 0x20
#define nRF24L01_W_RX_ADDR_P4 0x0e | 0x20
#define nRF24L01_W_RX_ADDR_P5 0x0f | 0x20
#define nRF24L01_W_TX_ADDR 0x10 | 0x20  // Transmit address (TX Mode)
#define nRF24L01_W_RX_PW_P0 0x11 | 0x20 // Data Pipe 0 RX Payload Width
#define nRF24L01_W_RX_PW_P1 0x12 | 0x20
#define nRF24L01_W_RX_PW_P2 0x13 | 0x20
#define nRF24L01_W_RX_PW_P3 0x14 | 0x20
#define nRF24L01_W_RX_PW_P4 0x15 | 0x20
#define nRF24L01_W_RX_PW_P5 0x16 | 0x20
#define nRF24L01_W_FIFO_STATUS 0x17 | 0x20

#define nRF24L01_W_DYNDP 0x1c | 0x20
#define nRF24L01_W_FEATURE 0x1d | 0x20

//read rx payload
#define nRF24L01_R_RX_PAYLOAD 0b01100001

//write tx payload
#define nRF24L01_W_TX_PAYLOAD 0b10100000

//flush tx fifo
#define nRF24L01_FLUSH_TX 0b11100001

//flush rx fifo
#define nRF24L01_FLUSH_RX 0b11100010

//

// PE12 = TRX_CSN (Select = Chip Select NOT high)
#define nRF24L01_CSN_LOW GPIOE->ODR &= ~(1U << 12);
#define nRF24L01_CSN_HIGH GPIOE->ODR |= (1U << 12);

// PE11 = TRX_CE (Chip enable)
#define nRF24L01_CE_ON GPIOE->ODR |= (1U << 11);
#define nRF24l01_CE_OFF GPIOE->ODR &= ~(1U << 11);

void TRX_TX_Init(void);
void TRX_RX_Init(void);
void TRX_IO_Init(void);
void sendData(uint8_t *pBuffer, uint8_t NumByteToWrite);
void readRecievedData(uint8_t *pBuffer, uint8_t NumByteToRead);
void TRX_IO_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite);
void TRX_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint8_t NumByteToRead);
void nRF24L01_TX_Init(void);
void nRF24L01_RX_Init(void);

#endif /* __STM32L476G_DISCOVERY_L3GD20_H */
