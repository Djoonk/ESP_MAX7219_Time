#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/gptimer.h"
#include "spi_config.h"
#include "esp_timer.h"
#include "timer_config.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include <stdbool.h>
#include "MAX7219.h"

static const char *TAG = "time";
extern gptimer_handle_t gptimer;

volatile uint32_t time = 0;
bool flagTime = false;

void task_MAX7219(void *pvParameters);
void task_time(void *pvParameters);

void task_MAX7219(void *pvParameters)
{
    while (1)
    {
        if (flagTime)
        {
            uint32_t h = time / 3600;
            uint32_t m = (time % 3600) / 60;
            uint32_t s = time % 60;
            flagTime = false;
            ESP_LOGI(TAG, "Time: %02d:%02d:%02d", h, m, s);
            timeSet(h, m, s);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    // vTaskDelete(NULL);
}

void app_main(void)
{
    // init_timer_bus();
    // start_timer();
    init_spi_bus();
    init_spi_device();
    MAX7219_Init();
    timerInit();
    
    //----------------Get time------------------
    // MAX7219_Clear();
    // MAX7219_Number(-9876543);
    
    // int64_t t1 = esp_timer_get_time();
    // ESP_LOGI(TAG, "time value = %d", t1);
    // xTaskCreate(task_time, "task_time",4090,NULL,5,NULL);
    xTaskCreate(task_MAX7219, "task_time",4090,NULL,5,NULL);

    // while (1)
    // {
    //     vTaskDelay(500 / portTICK_PERIOD_MS);
    // }
}

