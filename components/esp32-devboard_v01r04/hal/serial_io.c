#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "serial_io.h"



#define SERIAL_IO_CK( x )     gpio_set_level( ptrSerial_io->ck_pin, x )
#define SERIAL_IO_DI()        gpio_get_level( ptrSerial_io->di_pin )
#define SERIAL_IO_DO( x )     gpio_set_level( ptrSerial_io->do_pin, x )
#define SERIAL_IO_LD( x )     gpio_set_level( ptrSerial_io->ld_pin, x )


//////////////////////////////////////////
//////////////////////////////////////////


void serial_in_load( SERIAL_IN * ptrSerial_io )
{
    SERIAL_IO_LD(0);
    SERIAL_IO_LD(1);
}
void serial_out_load( SERIAL_OUT * ptrSerial_io )
{
    SERIAL_IO_LD(0);
    SERIAL_IO_LD(1);
}
void serial_io_load( SERIAL_IO * ptrSerial_io )
{
    SERIAL_IO_LD(0);
    SERIAL_IO_LD(1);
}


//////////////////////////////////////////
//////////////////////////////////////////


unsigned char serial_in_byteShift( SERIAL_IN * ptrSerial_io )
{
    unsigned char dataBit = 0x80;
    unsigned char dataIn = 0;

    while( dataBit )
    {
        SERIAL_IO_CK( 0 );
        if( SERIAL_IO_DI() )
            dataIn |= dataBit;
        SERIAL_IO_CK( 1 );
        dataBit >>= 1;
    }
    SERIAL_IO_CK( 0 );
    return( dataIn );
}

void serial_out_byteShift( SERIAL_OUT * ptrSerial_io, unsigned char dataOut )
{
    unsigned char dataBit = 0x80;
    while( dataBit )
    {
        SERIAL_IO_CK( 0 );
        if( dataOut & dataBit )
            SERIAL_IO_DO( 1 );
        else
            SERIAL_IO_DO( 0 );
        SERIAL_IO_CK( 1 );
        dataBit >>= 1;
    }
    SERIAL_IO_CK( 0 );
}

unsigned char serial_io_byteShift( SERIAL_IO * ptrSerial_io, unsigned char dataOut )
{
    unsigned char dataBit = 0x80;
    unsigned char dataIn = 0;

    while( dataBit )
    {
        SERIAL_IO_CK( 0 );
        if( dataOut & dataBit )
            SERIAL_IO_DO( 1 );
        else
            SERIAL_IO_DO( 0 );

        if( SERIAL_IO_DI() )
            dataIn |= dataBit;
        SERIAL_IO_CK( 1 );
        dataBit >>= 1;
    }
    SERIAL_IO_CK( 0 );
    return( dataIn );
}

//////////////////////////////////////////
//////////////////////////////////////////

void serial_in_scan( SERIAL_IN * ptrSerial_io )
{
    unsigned char i;
    serial_in_load( ptrSerial_io );
    for( i=0; i<ptrSerial_io->vLength; i++ )
    {
        ptrSerial_io->vIn[i] = serial_in_byteShift( ptrSerial_io );
    }
    serial_in_load( ptrSerial_io );
}

void serial_out_scan( SERIAL_OUT * ptrSerial_io )
{
    unsigned char i,j;
    j = ptrSerial_io->vLength - 1;
    serial_out_load( ptrSerial_io );
    for( i=0; i<ptrSerial_io->vLength; i++ )
    {
        serial_out_byteShift( ptrSerial_io, ptrSerial_io->vOut[j-i] );
    }
    serial_out_load( ptrSerial_io );
}


void serial_io_scan( SERIAL_IO * ptrSerial_io )
{
    unsigned char i,j;
    j = ptrSerial_io->vLength - 1;
    serial_io_load( ptrSerial_io );
    for( i=0; i<ptrSerial_io->vLength; i++ )
    {
        ptrSerial_io->vIn[i] = serial_io_byteShift( ptrSerial_io, ptrSerial_io->vOut[j-i] );
    }
    serial_io_load( ptrSerial_io );
}

//////////////////////////////////////////
//////////////////////////////////////////

void serial_in_init( SERIAL_IN * ptrSerial_io )
{
    gpio_reset_pin( ptrSerial_io->ck_pin );
    gpio_set_direction( ptrSerial_io->ck_pin, GPIO_MODE_OUTPUT );

    gpio_reset_pin( ptrSerial_io->di_pin );
    gpio_set_direction( ptrSerial_io->di_pin, GPIO_MODE_INPUT );

    gpio_reset_pin( ptrSerial_io->ld_pin );
    gpio_set_direction( ptrSerial_io->ld_pin, GPIO_MODE_OUTPUT );
    
    SERIAL_IO_CK( 0 );
    SERIAL_IO_LD( 1 );
}

void serial_out_init( SERIAL_OUT * ptrSerial_io )
{
    gpio_reset_pin( ptrSerial_io->ck_pin );
    gpio_set_direction( ptrSerial_io->ck_pin, GPIO_MODE_OUTPUT );

    gpio_reset_pin( ptrSerial_io->do_pin );
    gpio_set_direction( ptrSerial_io->do_pin, GPIO_MODE_OUTPUT );

    gpio_reset_pin( ptrSerial_io->ld_pin );
    gpio_set_direction( ptrSerial_io->ld_pin, GPIO_MODE_OUTPUT );

    SERIAL_IO_CK( 0 );
    SERIAL_IO_DO( 0 );
    SERIAL_IO_LD( 1 );
}

void serial_io_init( SERIAL_IO * ptrSerial_io )
{
    gpio_reset_pin( ptrSerial_io->ck_pin );
    gpio_set_direction( ptrSerial_io->ck_pin, GPIO_MODE_OUTPUT );

    gpio_reset_pin( ptrSerial_io->di_pin );
    gpio_set_direction( ptrSerial_io->di_pin, GPIO_MODE_INPUT );
    
    gpio_reset_pin( ptrSerial_io->do_pin );
    gpio_set_direction( ptrSerial_io->do_pin, GPIO_MODE_OUTPUT );

    gpio_reset_pin( ptrSerial_io->ld_pin );
    gpio_set_direction( ptrSerial_io->ld_pin, GPIO_MODE_OUTPUT );

    SERIAL_IO_CK( 0 );
    SERIAL_IO_DO( 0 );
    SERIAL_IO_LD( 1 );
}
//////////////////////////////////////////
//////////////////////////////////////////
