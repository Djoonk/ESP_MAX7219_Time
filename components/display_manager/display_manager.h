#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi_ntp.h"
#include "MAX7219.h"

void xTimeTask( void * pvParameters );
void timeSet(uint32_t h,uint32_t m,uint32_t s);
void dataSet(uint32_t d, uint32_t m, uint32_t y);

#ifdef __cplusplus
}
#endif