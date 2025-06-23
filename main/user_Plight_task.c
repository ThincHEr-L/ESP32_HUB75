#include "all_task.h"
#include "driver/gpio.h"

#define LED_GPIO_PIN GPIO_NUM_12

uint8_t led_pin_level = 0;

void PowerLightInit(void)
{
    gpio_config_t io_cfg = {
        .pin_bit_mask = 1 << LED_GPIO_PIN,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = 0,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_cfg);
    gpio_set_level(LED_GPIO_PIN, 0); // Set initial state to low
}

void power_light_task(void *arg)
{
    PowerLightInit();
    while (1)
    {
        led_pin_level = !led_pin_level;
        gpio_set_level(LED_GPIO_PIN, led_pin_level);
        vTaskDelay(pdMS_TO_TICKS(1000));        
    }
}
