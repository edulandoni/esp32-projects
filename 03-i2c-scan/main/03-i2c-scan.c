#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_err.h"

#define I2C_PORT I2C_NUM_0
#define I2C_SDA_GPIO 8
#define I2C_SCL_GPIO 9
#define I2C_FREQ_HZ 400000
#define I2C_TIMEOUT_MS 1000

static void i2c_master_init(void)
{
	i2c_config_t conf = {
		.mode = I2C_MODE_MASTER,
		.sda_io_num = I2C_SDA_GPIO,
		.scl_io_num = I2C_SCL_GPIO,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.master.clk_speed = I2C_FREQ_HZ,
		.clk_flags = 0
	}

	esp_err-t err = i2c_param_config(I2C_PORT, &conf);
	if (err != ESP_OK){
		printf("i2c_param_config failed: %s\n", esp_err_to_name(err));
		return;
	}

	err = i2c_driver_install(I2C_PORT, conf.mode,0,0,0);
	if (err != ESP_OK) {
		printf("i2c_driver_install failed: %s\n", esp_err_to_name(err));
		return;
	}
}

static esp_err_t i2c_probe_address(unit8_t addr)
{
	i2_cmd_handle_t cmd = i2c_cmd_link_create();
	if (cmd == NULL){
    return ESP_FAIL;
  }

  i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addr<<1) | I2C_MASTER_WRITE, true);
	i2c_masteer_stop(cmd);

	esp_err_t err=i2c_master_cmd_begin(
			I2C_PORT,
			cmd,
			pdMS_TO_TIKS(I2C_TIMEOUT_MS)
	);

	i2c_cmd_link_delet(cmd);

	return err;
}

static void i2c_scan_bus(void)
{
	printf("Scanning I2C bus... \n");

	for (unit8_t addr = 1; addr < 0x7F; addr++){
    esp_err_t err = i2c_probe_address(addr);
    if (err == ESP_OK){
      printf("Found device at 0x%02X\n", addr);
    }
  }
  printf("Scan done.\n");
}

void app_main(void)
{
  i2c_master_init();
  vTaskDelay(pdMS_TO_TICKS(100));
  i2c_scan_bus();

  while(1){
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}



























































