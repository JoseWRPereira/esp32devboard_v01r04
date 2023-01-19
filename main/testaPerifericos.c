#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp32-devboard_v01r04.h"
#include "wifi-ap-webserver.h"

void app_main(void)
{
    char previous_din = 0;
    char previous_dout = 0;
    char previous_key = 0;
    char key = 0;

    char lin0[] = "ESP32DevBoard v01r04";
    char lin1[] = "E00000000  S00000000";
    char lin2[] = "                    ";
    char lin3[] = "...              ...";

    vTaskDelay(500/portTICK_PERIOD_MS);

    devboard.global.init();
    // devboard.keyboard.init();
    wifi_init();
    vTaskDelay(500/portTICK_PERIOD_MS);

    devboard.lcd.print(0,0,lin0);
    devboard.lcd.print(1,0,lin1);
    devboard.lcd.print(2,0,lin2);
    devboard.lcd.print(3,0,lin3);
    vTaskDelay(2000/portTICK_PERIOD_MS);

    while( 1 )
    {
        if( previous_din != devboard.digital.input->data )
        {
            previous_din = devboard.digital.input->data;
            lin1[8] = devboard.digital.input->bits.e0 ? '1' : '0';
            lin1[7] = devboard.digital.input->bits.e1 ? '1' : '0';
            lin1[6] = devboard.digital.input->bits.e2 ? '1' : '0';
            lin1[5] = devboard.digital.input->bits.e3 ? '1' : '0';
            lin1[4] = devboard.digital.input->bits.e4 ? '1' : '0';
            lin1[3] = devboard.digital.input->bits.e5 ? '1' : '0';
            lin1[2] = devboard.digital.input->bits.e6 ? '1' : '0';
            lin1[1] = devboard.digital.input->bits.e7 ? '1' : '0';
            devboard.lcd.print(1,0,lin1);
        }

        devboard.digital.output->data = web_digital_output();
        if( previous_dout != devboard.digital.output->data )
        {
            previous_dout = devboard.digital.output->data;
            lin1[19] = devboard.digital.output->bits.rl0 ? '1':'0';
            lin1[18] = devboard.digital.output->bits.rl1 ? '1':'0';
            lin1[17] = devboard.digital.output->bits.ca0 ? '1':'0';
            lin1[16] = devboard.digital.output->bits.ca1 ? '1':'0';
            lin1[15] = devboard.digital.output->bits.s1 ? '1':'0';
            lin1[14] = devboard.digital.output->bits.s2 ? '1':'0';
            lin1[13] = devboard.digital.output->bits.s3 ? '1':'0';
            lin1[12] = devboard.digital.output->bits.s4 ? '1':'0';
            devboard.lcd.print(1,0,lin1);
        }

        if( web_stepmotor() )
        {
            devboard.stepmotor.passos( web_stepmotor() );
            web_stepmotor_reset();
        }

        // switch( key = devboard.keyboard.key() )
        // {
        //     case '0': lin3[0] = '0'; break;
        //     case '1': lin3[0] = '1'; break;
        //     case '2': lin3[0] = '2'; break;
        //     case '3': lin3[0] = '3'; break;
        //     case '4': lin3[0] = '4'; break;
        //     case '5': lin3[0] = '5'; break;
        //     case '6': lin3[0] = '6'; break;
        //     case '7': lin3[0] = '7'; break;
        //     case '8': lin3[0] = '8'; break;
        //     case '9': lin3[0] = '9'; break;
        //     case 'A': lin3[0] = 'A'; break;
        //     case 'B': lin3[0] = 'B'; break;
        //     case 'C': lin3[0] = 'C'; break;
        //     case 'D': lin3[0] = 'D'; break;
        //     case '*': lin3[0] = '*'; break;
        //     case '#': lin3[0] = '#'; break;
        //     default:  lin3[0] = ' '; break;
        // }

        // if( previous_key != key )
        // {
        //     devboard.lcd.print(3,0,lin3);
        //     previous_key = key;
        // }

        devboard.digital.scan();
        vTaskDelay(30/portTICK_PERIOD_MS);
    }
}
