#ifndef ANGLE_H
#define ANGLE_H

#include "stm32l476xx.h"

#include "L3GD20.h"
#include "SPI.h"

void Angle_init(void);
float get_v_x(void);
float get_v_y(void);
float get_v_z(void);
float get_x_angle(uint8_t milliseconds);
float get_y_angle(uint8_t milliseconds);
float get_z_angle(uint8_t milliseconds);

#endif
