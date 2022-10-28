#include <stdio.h>
#include "driver/gpio.h"
#include "keyboard.h"
#include "serial_io.h"


// KEYBOARD
#define SERIAL_IO_KEYBOARD_CK_PIN        4
#define SERIAL_IO_KEYBOARD_DI_PIN        15
#define SERIAL_IO_KEYBOARD_DO_PIN        16
#define SERIAL_IO_KEYBOARD_LD_PIN        2
unsigned char keyb_in  = 0;
unsigned char keyb_out = 0;
SERIAL_IO keyboard_drv = 
                    {   
                        SERIAL_IO_KEYBOARD_CK_PIN,
                        SERIAL_IO_KEYBOARD_DI_PIN,
                        SERIAL_IO_KEYBOARD_DO_PIN,
                        SERIAL_IO_KEYBOARD_LD_PIN,
                        &keyb_in,
                        &keyb_out,
                        1
                    };

#define NUM_COL         4
#define NUM_LIN         4
#define L0_MASK         0x01
#define C0_MASK         0x01

// unsigned char teclIn = 0;
// unsigned char teclOut = 0;

void keyboard_init( void )
{
//    keyb_serialIO_init( &teclIn, &teclOut, 1 );
    serial_io_init(&keyboard_drv);
}

const char tecladoMatriz[4][4] = {  {'1','2','3','A'},
                                    {'4','5','6','B'},
                                    {'7','8','9','C'},
                                    {'*','0','#','D'} };

unsigned char keyboard( void )
{
    unsigned char aux = 0;
    unsigned char l,c;
    
    for( l=0; l<NUM_LIN; l++ )
    {
        // teclOut = (unsigned char)(L0_MASK << l);
        keyb_out = (unsigned char)(L0_MASK << l);
        // keyb_serialIO_scan();
        // keyb_serialIO_scan();
        // keyb_serialIO_scan();
        // serial_io_scan(&keyboard_drv);
        // serial_io_scan(&keyboard_drv);
        serial_io_scan(&keyboard_drv);
        for( c=0; c<NUM_COL; c++ )
        {
//            keyb_serialIO_scan();
            if( keyb_in & (C0_MASK<<c) )
                aux = tecladoMatriz[l][c];
        }
    }   
    return( aux );
}