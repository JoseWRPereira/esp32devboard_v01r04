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

/// @brief  Produz borda no pino de carregamento de dados do
///         registrador de deslocamento (74165), efetuando a 
///         leitura de 8 bits.
/// @param ptrSerial_io Ponteiro para estrutura de dados da 
///         comunicação serial via CI 74165.
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

/// @brief  Executa o deslocamento de 8 bits, carregados
//          no registrador de deslocamento 74165, de forma 
///         serial, lendo-os e armazenando-os em uma variável.
/// @param ptrSerial_io Ponteiro para a estrutura de dados 
///         de comunicação com CI 74165.
/// @return Dado lido (8-bits) e disponibilizados como 
///         variável de retorno.
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

/// @brief  Realiza o processo de transferência serial de dados 
///         de entrada e de saída de forma simultânea. Tais dados
///         estão contidos na estrutura apontada pelo @param
///         O processo de transferência ocorre utilizando CI's 
///         registradores de deslocamento, que convertem dados
///         entre os formatos serial/paralelo (74595) e 
///         paralelo/serial (74165). 
/// @param ptrSerial_io Ponteiro para a estrutura de dados 
///         de comunicação com CI 74165.
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


/// @brief  Configuração e inicialização de pinos de interface com
///         CI de conversão paralelo/serial (74165).
/// @param ptrSerial_io Ponteiro para a estrutura de dados 
///         de comunicação com CI 74165.
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
