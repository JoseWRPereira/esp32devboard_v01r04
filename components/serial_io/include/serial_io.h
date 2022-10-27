#ifndef SERIAL_IO_H
#define SERIAL_IO_H

// #define SIO_DI_PIN      13
// #define SIO_CK_PIN      12
// #define SIO_DO_PIN      27
// #define SIO_LD_PIN      14

typedef struct serialioT
{
    unsigned char ck_pin;
    unsigned char di_pin;
    unsigned char do_pin;
    unsigned char ld_pin;
    unsigned char * vIn;
    unsigned char * vOut;
    unsigned char vLength;
} SERIAL_IO;

void serial_io_scan( SERIAL_IO * ptrSerial_io );
void serial_io_init( SERIAL_IO * ptrSerial_io );

//////////////////////////////////////////
//////////////////////////////////////////


void serialIO_scan( void );
void serialIO_init( unsigned char * ptrIn, unsigned char * ptrOut, unsigned char length );

#endif
