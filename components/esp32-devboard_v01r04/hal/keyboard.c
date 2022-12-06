#include <stdio.h>
#include "pinout.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "keyboard.h"
#include "serial_io.h"


uint8_t keyb_in  = 0;
uint8_t keyb_out = 0;
SERIAL_IO keyboard_drv = 
                    {   
                        KEYBOARD_CK_PIN,
                        KEYBOARD_DI_PIN,
                        KEYBOARD_DO_PIN,
                        KEYBOARD_LD_PIN,
                        &keyb_in,
                        &keyb_out,
                        1
                    };

#define NUM_COL         4
#define NUM_LIN         4
#define L0_MASK         0x01
#define C0_MASK         0x01


void keyboard_init( void )
{
    serial_io_init(&keyboard_drv);
}

const uint8_t tecladoMatriz[4][4] = {   {'1','2','3','A'},
                                        {'4','5','6','B'},
                                        {'7','8','9','C'},
                                        {'*','0','#','D'} };

uint8_t keyboard( void )
{
    uint8_t aux = 0;
    uint8_t l,c;
    
    for( l=0; l<NUM_LIN; l++ )
    {
        keyb_out = (uint8_t)(L0_MASK << l);

        serial_io_scan(&keyboard_drv);
        // vTaskDelay(10/portTICK_PERIOD_MS);
        serial_io_scan(&keyboard_drv);
        serial_io_scan(&keyboard_drv);
        for( c=0; c<NUM_COL; c++ )
        {
            if( keyb_in & (C0_MASK<<c) )
            {
                aux = tecladoMatriz[l][c];
                break;
            }
        }
    }
    return( aux );
}