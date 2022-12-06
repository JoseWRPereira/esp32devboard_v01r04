#include <stdio.h>
#include "pinout.h"
#include "digital_io.h"
#include "serial_io.h"


DigitalIn digital_in;
DigitalOut digital_out;

SERIAL_IO digital_io =  {   
                            DGITAL_IO_CK_PIN,
                            DGITAL_IO_DI_PIN,
                            DGITAL_IO_DO_PIN,
                            DGITAL_IO_LD_PIN,
                            &digital_in.data,
                            &digital_out.data,
                            1
                        };

void digital_io_init( void )
{
    serial_io_init(&digital_io);
}


void digital_io_scan( void )
{
    serial_io_scan(&digital_io);
}
