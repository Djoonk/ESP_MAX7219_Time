#include "spi_config.h"
#include "driver/spi_master.h"

static const char *TAG = "SPI2";
esp_err_t ret;
spi_device_handle_t spi;

void init_spi_bus(void)
{
    spi_bus_config_t buscfg =
    {
        .sclk_io_num = PIN_NUM_SCLK,
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2, &buscfg, SPI_DMA_DISABLED));
}

void init_spi_device(void)
{
    spi_device_interface_config_t devcfg = 
    {
        .clock_speed_hz = 1 * 1000 * 1000, // Clock out at 10 MHz
        .mode = 0,                         // SPI mode 0
        .spics_io_num = PIN_NUM_CS,        // CS pin
        .queue_size = 7,                   // We want to be able to queue 7 transactions at a time
    };
    // Attach the device () to the SPI bus
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2, &devcfg, &spi));
}