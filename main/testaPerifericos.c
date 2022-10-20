#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_INPUT_OUTPUT);
    while( 1 )
    {
        gpio_set_level(GPIO_NUM_2, !gpio_get_level(GPIO_NUM_2));
        vTaskDelay(100);

    }
}
