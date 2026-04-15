#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/spi_master.h"

#define SPI2             SPI2_HOST
#define PIN_NUM_SCLK     22
#define PIN_NUM_MOSI     23
#define PIN_NUM_CS       18

void init_spi_bus(void);
void init_spi_device(void);


#ifdef __cplusplus
}
#endif