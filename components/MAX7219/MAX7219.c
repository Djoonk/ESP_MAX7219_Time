#include "MAX7219.h"

static const char *TAG2= "NUMBER";

extern spi_device_handle_t spi;

spi_transaction_t TX =
{
    .flags = SPI_TRANS_USE_TXDATA,
    .length = 16,
};


void MAX7219_SendData(uint8_t adress, uint8_t dat)
{
    TX.tx_data[0] = adress;
    TX.tx_data[1] = dat;

    spi_device_transmit(spi, &TX);
}

void MAX7219_Clear(void)
{
    for (uint8_t i = 1; i <= 8; i++)
    {
        MAX7219_SendData(i, 0x0f);
    }
}

void MAX7219_Init(void)
{
    MAX7219_SendData(SHUTDOWN, SHUTDOWN_MODE);             // вимикаємо індікатор
    MAX7219_SendData(SCAN_LIMIT, 0x07);                    // кількість задіяних розрядів
    MAX7219_SendData(DECODE_MODE, DECODE_FOR_DIGIT_7_0);   // режим декодування    
    MAX7219_SendData(INTENSITY, 0x01);                     // яскравість (0x00 - 0x0F)
    MAX7219_SendData(SHUTDOWN, NORMAL_OPERATION);          // вмикаємо індікатор
    MAX7219_Clear();
}

void MAX7219_Number(volatile long num)
{
    uint8_t i = 0;
    bool neg = false;
   
    MAX7219_Clear();
    if (num < 0)
    {
        neg = true;
        num = num * (-1);
    }

    do
    {
        MAX7219_SendData(++i, num % 10);
        ESP_LOGI(TAG2, "NUM = %d\n", num);
        num /= 10;
        
    } while (num);
    if (neg && num == 0)
    {
        MAX7219_SendData(++i, 0xA);
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