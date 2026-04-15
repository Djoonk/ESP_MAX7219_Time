#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c_config.h"
#include "driver/i2c_master.h"

#define I2C_SCL_PIN     22
#define I2C_SDA_PIN     21
#define I2C_BUS_SPEED   400000   /* 400 kHz */

void init_i2c_bus(void);
void i2c_init_device(void);


#ifdef __cplusplus
}
#endif