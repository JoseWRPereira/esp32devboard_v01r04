#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp32-devboard_v01r04.h"
#include "wifi-ap-webserver.h"

void app_main(void)
{
    char lin0[] = "DevBoard  v01r04";
    char lin1[] = "E[   ] ## S[   ]";
    vTaskDelay(500/portTICK_PERIOD_MS);

    devboard.global.init();
    wifi_init();
    vTaskDelay(500/portTICK_PERIOD_MS);

    devboard.lcd.print(0,0,lin0);
    devboard.lcd.print(1,0,lin1);
    vTaskDelay(2000/portTICK_PERIOD_MS);

    while( 1 )
    {
        // devboard.digital.output->data = devboard.digital.input->data;
        // devboard.digital.scan();
        // vTaskDelay(30/portTICK_PERIOD_MS);
        devboard.stepmotor.passos(48, 1);
        vTaskDelay(100);
        devboard.stepmotor.passos(96, 0);
        vTaskDelay(100);
        // vTaskDelay(300/portTICK_PERIOD_MS);
        // devboard.stepmotor.passos(200, 0);
        // vTaskDelay(300/portTICK_PERIOD_MS);
    }
}