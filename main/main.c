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
#include "esp_sntp.h"
#include "wifi_ntp.h"
#include "esp_sleep.h"
#include "esp_netif.h"         // Для мережевого стеку
#include "esp_netif_sntp.h"    // Для NTP
#include "display_manager.h"

// RTC_DATA_ATTR static int boot_count = 0;
static const char *TAG = "Time";

void app_main(void)
{
    vTaskDelay(pdMS_TO_TICKS(100));
    init_spi_bus();
    init_spi_device();
    MAX7219_Init();

    // 1. Базова ініціалізація
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    } 
    ESP_ERROR_CHECK(ret);
    wifi_init();

    sntpSyncTime();
//=============================================================
    xTaskCreate(xTimeTask, "MaxTask", 2048, NULL, 5, NULL);

}

