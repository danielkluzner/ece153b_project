#include "INA260.h"

char message[2] = {0};
uint8_t SlaveAddress = INA260_ADDRESS;
uint8_t voltageRegisterAddress = INA260_VOLTAGE_REGISTER_ADDRESS;
uint8_t Data_Receive[2] = {0};
uint16_t voltageRegisterValue = 0;
float voltage = 0.0;

void INA260_init(void)
{
    I2C_SendData(I2C1, SlaveAddress, &voltageRegisterAddress, 1);
}

void INA260_read(void)
{
    //data from voltage register on INA260 is 16 bits
    //received in bytes, MSByte first
    I2C_ReceiveData(I2C1, SlaveAddress, Data_Receive, 2);
    voltageRegisterValue |= Data_Receive[0] << 8; //Data[0] is MSByte
    voltageRegisterValue |= Data_Receive[1];

    voltage = voltageRegisterValue * 1.25 / 1000.0; //conversion to Volts
    voltageRegisterValue = 0;                       //reset stored value of voltage register

    sprintf(message, "%.2f", voltage);
    LCD_DisplayString((uint8_t *)message);
}
