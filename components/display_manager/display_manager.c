#include "display_manager.h"
static const char *TAG = "Display";
bool flagSync = false;


// Створення задачі freeRTOS
// lastSync має бути оголошена зовні або як static
static time_t lastSync = 0; 

void xTimeTask(void *pvParameters) {
    struct tm timeinfo;
    time_t now;
    uint8_t timeCNT = 0;

    while (1) {
        time(&now);
        localtime_r(&now, &timeinfo);

        // 1. СИНХРОНІЗАЦІЯ
        // Додаємо оновлення lastSync
        if (now - lastSync >= 86400) {
            sntpSyncTime();
            lastSync = now; // ТЕПЕР УМОВА СТАНЕ ХИБНОЮ НА НАСТУПНІ 24 ГОДИНИ
        }

        // 2. ВІДОБРАЖЕННЯ
        if (timeCNT <= 20) {
            timeSet(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        } else {
            dataSet(timeinfo.tm_mday, (timeinfo.tm_mon + 1), (timeinfo.tm_year + 1900));
        }

        // 3. КЕРУВАННЯ ЦИКЛОМ
        if (++timeCNT > 30) {
            timeCNT = 0;
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// передаємо значення часу на MAX7219
void timeSet(uint32_t h, uint32_t m, uint32_t s)
{
    MAX7219_Clear();
    // sec
    MAX7219_SendData(1, s % 10);
    MAX7219_SendData(2, s / 10);
    // min
    MAX7219_SendData(3, (m % 10)|0x80);
    MAX7219_SendData(4, (m / 10) );
    // hour
    MAX7219_SendData(5, (h % 10)|0x80);
    MAX7219_SendData(6, h / 10);
}

// передаємо значення дати на MAX7219
void dataSet(uint32_t d, uint32_t m, uint32_t y)
{
    MAX7219_Clear();
    // year
    MAX7219_SendData(1, y % 10 );
    MAX7219_SendData(2, ((y / 10) % 10));
    MAX7219_SendData(3, (y / 100) % 10 );
    MAX7219_SendData(4, (y / 1000) % 10  );
    // moun
    MAX7219_SendData(5, (m % 10)|0x80);
    MAX7219_SendData(6, m / 10);
    // day
    MAX7219_SendData(7, (d % 10)|0x80);
    MAX7219_SendData(8, d / 10);
}

