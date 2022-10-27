#include <stdio.h>
// #include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "piscaLed.h"
#include "serial_io.h"
#include "lcd.h"


unsigned char entradas = 0;
unsigned char saidas = 0;
#define DGITAL_IO_CK_PIN      12
#define DGITAL_IO_DI_PIN      13
#define DGITAL_IO_DO_PIN      27
#define DGITAL_IO_LD_PIN      14


SERIAL_IO digital_io =  {   
                            DGITAL_IO_CK_PIN,
                            DGITAL_IO_DI_PIN,
                            DGITAL_IO_DO_PIN,
                            DGITAL_IO_LD_PIN,
                            &entradas,
                            &saidas,
                            1
                        };




#define IO_SIZE     1
void app_main(void)
{
    // unsigned char vIn[IO_SIZE];
    // unsigned char vOut[IO_SIZE] = {0};

    blink_init();
    // serialIO_init( vIn, vOut, IO_SIZE );
    lcd_init();
    serial_io_init(&digital_io);

    while( 1 )
    {
        blink();
        vTaskDelay(1000);
        ++saidas;
        serial_io_scan(&digital_io);
    }
}


// void app_main(void)
// {
//     gpio_set_direction(GPIO_NUM_2,GPIO_MODE_INPUT_OUTPUT);
//     while( 1 )
//     {
//         gpio_set_level(GPIO_NUM_2, !gpio_get_level(GPIO_NUM_2));
//         vTaskDelay(50);    
//     }
// }
