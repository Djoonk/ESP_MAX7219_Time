#ifndef WIFI_NTP_H
#define WIFI_NTP_H
#include <string.h>
#include "freertos/FreeRTOS.h" // Обов'язково для portTICK_PERIOD_MS
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_err.h"           // Обов'язково для esp_err_t
#include "esp_wifi.h"          // Для wifi_config_t та функцій wifi
#include "esp_event.h"         // Для івент-лупа
#include "esp_log.h"           // Для ESP_LOGI
#include "nvs_flash.h"         // Для nvs_flash_init
#include "esp_netif.h"         // Для мережевого стеку
#include "esp_netif_sntp.h"    // Для NTP
#include "esp_sntp.h"
#include "wifi_ntp.h"

void obtain_time(void);
void wifi_init(void);
void sntpSyncTime(void);

#endif