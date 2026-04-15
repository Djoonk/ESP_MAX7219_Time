idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES
        ssd1306
        i2c_config
	esp_driver_i2c
        esp_driver_spi
        esp_driver_gpio
        esp_timer
	SPI_config
	MAX7219
	timer
)
