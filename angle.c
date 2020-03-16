#include "angle.h"

#define NEGATIVE 0x8000

float v_x; // x velocity
float v_y; // y velocity
float v_z; // z velocity
float x;   // x posotion
float y;   // y position
float z;   // z position

void Angle_init(void)
{
    v_x = 0; // x angular velocity - millidegrees per second
    v_y = 0; // y angular velocity
    v_z = 0; // z angular velocity
    x = 0;   // x angle
    y = 0;   // y angle
    z = 0;   // z angle
}

float get_v_x(void)
{
    uint16_t gyro_x = 0;
    uint8_t *data;
    GYRO_IO_Read(data, L3GD20_OUT_X_H_ADDR, 1);
    gyro_x |= *data << 8;
    GYRO_IO_Read(data, L3GD20_OUT_X_L_ADDR, 1);
    gyro_x |= *data;
    if ((gyro_x & NEGATIVE) == NEGATIVE)
    {
        v_x = (~gyro_x + 1) * (-70); //gyro data is ouput in units of 70mdps
    }
    else
    {
        v_x = gyro_x * 70;
    }
    return v_x;
}
float get_v_y(void)
{
    uint16_t gyro_y = 0;
    uint8_t *data;
    GYRO_IO_Read(data, L3GD20_OUT_X_H_ADDR, 1);
    gyro_y |= *data << 8;
    GYRO_IO_Read(data, L3GD20_OUT_X_L_ADDR, 1);
    gyro_y |= *data;
    if ((gyro_y & NEGATIVE) == NEGATIVE)
    {
        v_y = (~gyro_y + 1) * (-70); //gyro data is ouput in units of 70mdps
    }
    else
    {
        v_y = gyro_y * 70;
    }
    return v_y;
}

float get_v_z(void)
{
    uint16_t gyro_z = 0;
    uint8_t *data;
    GYRO_IO_Read(data, L3GD20_OUT_X_H_ADDR, 1);
    gyro_z |= *data << 8;
    GYRO_IO_Read(data, L3GD20_OUT_X_L_ADDR, 1);
    gyro_z |= *data;
    if ((gyro_z & NEGATIVE) == NEGATIVE)
    {
        v_z = (~gyro_z + 1) * (-70); //gyro data is ouput in units of 70mdps
    }
    else
    {
        v_z = gyro_z * 70;
    }
    return v_z;
}

float get_x_angle(uint8_t milliseconds)
{
    x += ((v_x + get_v_x()) / 2) * (milliseconds / 1000);
    //angle = (angular velocity initial + angular velocity final ) / 2 * (time final - time initial) 
    return x;
}

float get_y_angle(uint8_t milliseconds)
{
    y += ((v_y + get_v_y()) / 2) * (milliseconds / 1000);
    return y;
}

float get_z_angle(uint8_t milliseconds)
{
    z += ((v_z + get_v_z()) / 2) * (milliseconds / 1000);
    return z;
}
