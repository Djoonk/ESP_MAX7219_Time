#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "driver/spi_master.h"
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "stdbool.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi_ntp.h"

#define SPI2                    SPI2_HOST
#define PIN_NUM_SCLK            22
#define PIN_NUM_MOSI            23
#define PIN_NUM_CS              18
// Register Address Map
#define NO_OP                   0x00
#define DIGIT_0                 0x01
#define DIGIT_1                 0x02
#define DIGIT_2                 0x03
#define DIGIT_3                 0x04
#define DIGIT_4                 0x05
#define DIGIT_5                 0x06
#define DIGIT_6                 0x07
#define DIGIT_7                 0x08
#define DECODE_MODE             0x09
#define INTENSITY               0x0A
#define SCAN_LIMIT              0x0B
#define SHUTDOWN                0x0C
#define DISPLAY_TEST            0x0F

// Shutdown Register Format 
#define SHUTDOWN_MODE           0x00
#define NORMAL_OPERATION        0x01

// Decode mode 
#define NO_DECODE_MODE          0x00
#define DECODE_FOR_DIGIT_0      0x01
#define DECODE_FOR_DIGIT_3_0    0x0F
#define DECODE_FOR_DIGIT_7_0    0xFF

// function prototype
void MAX7219_SendData(uint8_t adress, uint8_t dat);
void MAX7219_Clear(void);
void MAX7219_Init(void);
void MAX7219_SetHour(volatile long num);

#ifdef __cplusplus
}
#endif