
#include "wifi_ntp.h"

static const char *TAG = "WIFI_NTP";

// Вкажи свої дані тут
#define WIFI_SSID      "MERCUSYS_8B3E"
#define WIFI_PASS      "TCK2839hsd1818"

void obtain_time(void) {
    // 1. Ініціалізація NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // 2. Ініціалізація мережевого стеку
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // wifi_config_t wifi_config = {
    //     .sta = {
    //         .ssid = WIFI_SSID,
    //         .password = WIFI_PASS,
    //     },
    // };

    // ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    // ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    
    // // 3. Підключення
    // ESP_LOGI(TAG, "Підключення до %s...", WIFI_SSID);
    // ESP_ERROR_CHECK(esp_wifi_start());
    // ESP_ERROR_CHECK(esp_wifi_connect());

    // 4. Налаштування SNTP
    ESP_LOGI(TAG, "Синхронізація часу...");
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");
    esp_netif_sntp_init(&config);

    // 5. Очікування (макс. 15 спроб по 2 сек)
    int retry = 0;
    while (esp_netif_sntp_sync_wait(2000 / portTICK_PERIOD_MS) == ESP_ERR_TIMEOUT && ++retry < 15) {
        ESP_LOGI(TAG, "Очікування NTP... (%d/15)", retry);
    }

    // 6. Чисте вимкнення Wi-Fi (замість example_disconnect)
    ESP_LOGI(TAG, "Час отримано. Вимикаємо Wi-Fi.");
    esp_netif_sntp_deinit();
    esp_wifi_stop();
    esp_wifi_deinit();
}

void wifi_init(void)
{
    // Ініціалізація ТСР/ІР стеку
    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // Зверніть увагу на дужки ()
    esp_wifi_init(&cfg);
        wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    // Підключення
    ESP_LOGI(TAG, "Підключення до %s...", WIFI_SSID);
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_connect());
}


void sntpSyncTime(void)
{
    esp_sntp_setoperatingmode(ESP_SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_init();
    int retry = 0;
    while (esp_netif_sntp_sync_wait(2000 / portTICK_PERIOD_MS) == ESP_ERR_TIMEOUT && ++retry < 15) {
        ESP_LOGI(TAG, "Очікування NTP... (%d/15)", retry);
    }
    // встановлення часового поясу (Київ)
    setenv("TZ", "EET-2EEST,M3.5.0/3,M10.5.0/4", 1);
    tzset();
}