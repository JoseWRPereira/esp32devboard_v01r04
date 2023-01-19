#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "pinout.h"


void stepmotor_init( void )
{
    gpio_reset_pin( STEPMOTOR_SLEEP_PIN );
    gpio_reset_pin( STEPMOTOR_STEP_PIN );
    gpio_reset_pin( STEPMOTOR_DIR_PIN );
    gpio_set_direction( STEPMOTOR_SLEEP_PIN, GPIO_MODE_OUTPUT );
    gpio_set_direction( STEPMOTOR_DIR_PIN, GPIO_MODE_OUTPUT );
    gpio_set_direction( STEPMOTOR_STEP_PIN, GPIO_MODE_OUTPUT );
    gpio_set_level( STEPMOTOR_SLEEP_PIN, 0 );
    gpio_set_level( STEPMOTOR_DIR_PIN, 0 );
    gpio_set_level( STEPMOTOR_STEP_PIN, 0 );
}

void delay_step( unsigned int t )
{
    // vTaskDelay( t / portTICK_PERIOD_MS);
    vTaskDelay( pdMS_TO_TICKS( t ));
}

void stepmotor_passos( int32_t passos )
{
    gpio_set_level( STEPMOTOR_DIR_PIN, (passos>0)?1:0 );
    gpio_set_level( STEPMOTOR_SLEEP_PIN, 1 );
    while( passos )
    {
        gpio_set_level( STEPMOTOR_STEP_PIN, 1 );
        gpio_set_level( STEPMOTOR_STEP_PIN, 0 );
        delay_step(10);
        if( passos > 0 )
            --passos;
        else
            ++passos;
    }
    gpio_set_level( STEPMOTOR_SLEEP_PIN, 0 );
}
