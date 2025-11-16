#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_GPIO 4

static const char *TAG="LED_BLINK";

void app_main(void) {

	esp_rom_gpio_pad_select_gpio(LED_GPIO);

	gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

	ESP_LOGI(TAG, "Comenzando parpaadeo en GPIO %d", LED_GPIO);

	while(1){
		gpio_set_level(LED_GPIO, 1);
		ESP_LOGI(TAG, "LED ON");
		vTaskDelay(pdMS_TO_TICKS(500));

		gpio_set_level(LED_GPIO, 0);
		ESP_LOGI(TAG, "LED OFF");
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

