#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "digital_io.h"
#include "serial_io.h"
#include "lcd.h"
#include "keyboard.h"
#include "wifi.h"

#include "driver/gpio.h"
// int16_t cont = 0;

void app_main(void)
{
    // char lin0[] = "DevBoard__v01r04";
    // char lin1[] = "E[   ] _  S[   ]";
    // uint8_t tecla = 0;
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_INPUT_OUTPUT);
    // vTaskDelay(10);    

    vTaskDelay(1000/portTICK_PERIOD_MS);
    
    digital_io_init();
    // lcd_init();
    // keyboard_init();

    // lcd_print(0,0,lin0);
    // lcd_print(1,0,lin1);


    wifi_init();

    while( 1 )
    {
        gpio_set_level(GPIO_NUM_2, digital_out.bits.rl1);
        vTaskDelay(100/portTICK_PERIOD_MS);


        // digital_io_scan();
        // digital_out.data = digital_in.data;

    //     // tecla = keyboard();
    //     // lin1[7] = tecla?tecla:'_';
    //     // lcd_print(1,0,lin1);

    //     lcd_num(1, 2, digital_in.data,3);
    //     lcd_num(1,12, cont,    3);
    //     ++cont;
    //     if( cont > 99 )
    //         cont = -99;

        // vTaskDelay(10);
    }
}
