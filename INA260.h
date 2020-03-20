#ifndef INA260_H
#define INA260_H

#include "stm32l476xx.h"
#include "I2C.h"
#include "LCD.h"

#define INA260_ADDRESS 0x80                           ///< INA260 default i2c address
#define INA260_VOLTAGE_REGISTER_ADDRESS (uint8_t)0x02 //voltage register address

void INA260_init(void);
void INA260_read(void);

#endif
