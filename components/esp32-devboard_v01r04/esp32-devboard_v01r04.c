#include <stdio.h>
#include "esp32-devboard_v01r04.h"
#include "serial_io.h"
#include "digital_io.h"
#include "lcd.h"
#include "keyboard.h"

void esp32_devboard_init( void )
{
    digital_io_init();
    lcd_init();
    keyboard_init();
}



Devboard devboard = {
    .global.init = esp32_devboard_init,
    .lcd.init = lcd_init,
    .lcd.clr = lcd_clr,
    .lcd.print = lcd_print,
    .lcd.num = lcd_num,
    .digital.output = &digital_out,
    .digital.input = &digital_in,
    .digital.init = digital_io_init,
    .digital.scan = digital_io_scan,
    .keyboard.init = keyboard_init,
    .keyboard.key = keyboard
};
