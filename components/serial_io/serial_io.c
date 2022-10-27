#include <stdio.h>
#include "driver/gpio.h"
#include "serial_io.h"

#define SERIAL_IO_CK( x )     gpio_set_level( ptrSerial_io->ck_pin, x )
#define SERIAL_IO_DI()        gpio_get_level( ptrSerial_io->di_pin )
#define SERIAL_IO_DO( x )     gpio_set_level( ptrSerial_io->do_pin, x )
#define SERIAL_IO_LD( x )     gpio_set_level( ptrSerial_io->ld_pin, x )

void serial_io_load( SERIAL_IO * ptrSerial_io )
{
    SERIAL_IO_LD(0);
    SERIAL_IO_LD(1);
}

unsigned char serial_io_byteShift( SERIAL_IO * ptrSerial_io, unsigned char dataIn )
{
    unsigned char dataBit;
    unsigned char dataOut;

    dataBit = 0x80;
    dataOut = 0;

    while( dataBit )
    {
        SERIAL_IO_CK( 0 );
        if( dataIn & dataBit )
            SERIAL_IO_DO( 1 );
        else
            SERIAL_IO_DO( 0 );

        if( SERIAL_IO_DI() )
            dataOut |= dataBit;
        SERIAL_IO_CK( 1 );
        dataBit >>= 1;
    }
    SERIAL_IO_CK( 0 );
    return( dataOut );
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

//***************** Inicialiação de interface com SerialIO
void serial_io_init( SERIAL_IO * ptrSerial_io )
{
    // ptrSerialIn = ptrIn;
    // ptrSerialOut = ptrOut;
    // lenSerialIO = length;
// ************************** Serial IO Shift/Load
    gpio_reset_pin( ptrSerial_io->ld_pin );
    gpio_set_direction( ptrSerial_io->ld_pin, GPIO_MODE_OUTPUT );

// ************************** Serial IO Clock
    gpio_reset_pin( ptrSerial_io->ck_pin );
    gpio_set_direction( ptrSerial_io->ck_pin, GPIO_MODE_OUTPUT );

// ************************** Serial IO Output
    gpio_reset_pin( ptrSerial_io->do_pin );
    gpio_set_direction( ptrSerial_io->do_pin, GPIO_MODE_OUTPUT );

// ************************** Serial IO Input
    gpio_reset_pin( ptrSerial_io->di_pin );
    gpio_set_direction( ptrSerial_io->di_pin, GPIO_MODE_INPUT );
    
//***************** Inicialização dos pinos de interface com os CIs
    SERIAL_IO_CK( 0 );
    SERIAL_IO_DO( 0 );
    SERIAL_IO_LD( 1 );
}
//////////////////////////////////////////
//////////////////////////////////////////



// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// void sio_delay( unsigned int t )
// {
//     vTaskDelay( t / portTICK_PERIOD_MS);
//     // vTaskDelay( pdMS_TO_TICKS( t ));
// }

//  IOs
// #define SIO_DI_PIN      13
// #define SIO_CK_PIN      12
// #define SIO_DO_PIN      27
// #define SIO_LD_PIN      14

#define SIO_DI_PIN      13

// LCD
#define SIO_CK_PIN      17
#define SIO_DO_PIN      18
#define SIO_LD_PIN      5


#define SIO_LD( x )     gpio_set_level( SIO_LD_PIN, x )
#define SIO_DO( x )     gpio_set_level( SIO_DO_PIN, x )
#define SIO_CK( x )     gpio_set_level( SIO_CK_PIN, x )
#define SIO_DI()        gpio_get_level( SIO_DI_PIN )

unsigned char * ptrSerialIn;
unsigned char * ptrSerialOut;
unsigned char   lenSerialIO;


void serialIOload( void )
{
    SIO_LD( 0 );
    SIO_LD( 1 );
}

unsigned char serialIObyteShift( unsigned char dataIn )
{
    unsigned char dataBit;
    unsigned char dataOut;

    dataBit = 0x80;
    dataOut = 0;

    while( dataBit )
    {
        SIO_CK( 0 );
        if( dataIn & dataBit )
            SIO_DO( 1 );
        else
            SIO_DO( 0 );

        if( SIO_DI() )
            dataOut |= dataBit;
        SIO_CK( 1 );
        dataBit >>= 1;
    }
    SIO_CK( 0 );
    return( dataOut );
}

//***************** Interface Serial IO Scan
void serialIO_scan( void )
{
    unsigned char i,j;
    j = lenSerialIO - 1;
    serialIOload();
    for( i=0; i<lenSerialIO; i++ )
    {
        ptrSerialIn[i] = serialIObyteShift( ptrSerialOut[j-i]);
    }
    serialIOload();
}

//***************** Inicialiação de interface com SerialIO
void serialIO_init( unsigned char * ptrIn, unsigned char * ptrOut, unsigned char length )
{
    ptrSerialIn = ptrIn;
    ptrSerialOut = ptrOut;
    lenSerialIO = length;
// ************************** Serial IO Shift/Load
    gpio_reset_pin( SIO_LD_PIN );
    gpio_set_direction( SIO_LD_PIN, GPIO_MODE_OUTPUT );

// ************************** Serial IO Clock
    gpio_reset_pin( SIO_CK_PIN );
    gpio_set_direction( SIO_CK_PIN, GPIO_MODE_OUTPUT );

// ************************** Serial IO Output
    gpio_reset_pin( SIO_DO_PIN );
    gpio_set_direction( SIO_DO_PIN, GPIO_MODE_OUTPUT );

// ************************** Serial IO Input
    gpio_reset_pin( SIO_DI_PIN );
    gpio_set_direction( SIO_DI_PIN, GPIO_MODE_INPUT );
    
//***************** Inicialização dos pinos de interface com os CIs
    SIO_CK( 0 );
    SIO_DO( 0 );
    SIO_LD( 1 );
}