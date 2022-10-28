#include <stdio.h>
// #include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "piscaLed.h"
#include "serial_io.h"
#include "lcd.h"
#include "keyboard.h"


#define DGITAL_IO_CK_PIN      12
#define DGITAL_IO_DI_PIN      13
#define DGITAL_IO_DO_PIN      27
#define DGITAL_IO_LD_PIN      14
unsigned char entradas = 0;
unsigned char saidas = 0;
SERIAL_IO digital_io =  {   
                            DGITAL_IO_CK_PIN,
                            DGITAL_IO_DI_PIN,
                            DGITAL_IO_DO_PIN,
                            DGITAL_IO_LD_PIN,
                            &entradas,
                            &saidas,
                            1
                        };
int16_t cont = 0;

void app_main(void)
{
    char lin0[] = "DevBoard__v01r04";
    char lin1[] = "E[   ] _  S[   ]";
    uint8_t tecla = 0;

    vTaskDelay(1000/portTICK_PERIOD_MS);

    serial_io_init(&digital_io);
    keyboard_init();
    lcd_init();

    lcd_print(0,0,lin0);
    lcd_print(1,0,lin1);

    while( 1 )
    {
        serial_io_scan(&digital_io);
        saidas = entradas;

        tecla = 'J';//keyboard();
        lin1[7] = tecla?tecla:'_';
        // lcd_print(1,0,lin1);

        lcd_num(1, 2, entradas,3);
        lcd_num(1,12, cont,    3);
        ++cont;
        if( cont > 99 )
            cont = -99;
        vTaskDelay(10);
    }
}
