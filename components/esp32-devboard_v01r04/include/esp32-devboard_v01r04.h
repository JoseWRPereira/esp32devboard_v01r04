#ifndef ESP32_DEVBOARD_V01R04_H
#define ESP32_DEVBOARD_V01R04_H

#include "hal_types.h"

void esp32_devboard_init( void );
void esp32_devboard_scan( void );


extern Devboard devboard;


// void digital_io_scan( void );
// uint8_t keyboard( void );
// void lcd_clr( void );
// void lcd_print( unsigned char lin, unsigned char col, char * str );
// void lcd_num( uint8_t lin, uint8_t col,
//                     int16_t num, uint8_t tam );
// void num2str( int num, char * pos );

// void serial_in_scan(  SERIAL_IN  * ptrSerial_io );
// void serial_out_scan( SERIAL_OUT * ptrSerial_io );
// void serial_io_scan(  SERIAL_IO  * ptrSerial_io );
// void serial_in_init(  SERIAL_IN  * ptrSerial_io );
// void serial_out_init( SERIAL_OUT * ptrSerial_io );
// void serial_io_init(  SERIAL_IO  * ptrSerial_io );


#endif