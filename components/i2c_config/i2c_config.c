#include "i2c_config.h"
#include "driver/i2c_master.h"

void init_i2c_bus(void)
{
    i2c_master_bus_config_t bus_cfg =
        {
            .i2c_port = I2C_NUM_0,
            .sda_io_num = I2C_SDA_PIN,
            .scl_io_num = I2C_SCL_PIN,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .flags.enable_internal_pullup = true,
            .glitch_ignore_cnt = 7,
        };
   
}


void i2c_init_device(void) 
{
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = 0x3C, // Типова адреса SSD1306
        .scl_speed_hz    = 400000, // 400kHz Fast Mode
    };

}