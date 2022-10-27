#ifndef SERIAL_IO_H
#define SERIAL_IO_H

typedef struct serialinT
{
    unsigned char ck_pin;
    unsigned char di_pin;
    unsigned char ld_pin;
    unsigned char * vIn;
    unsigned char vLength;
} SERIAL_IN;

typedef struct serialoutT
{
    unsigned char ck_pin;
    unsigned char do_pin;
    unsigned char ld_pin;
    unsigned char * vOut;
    unsigned char vLength;
} SERIAL_OUT;

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

void serial_in_scan(  SERIAL_IN  * ptrSerial_io );
void serial_out_scan( SERIAL_OUT * ptrSerial_io );
void serial_io_scan(  SERIAL_IO  * ptrSerial_io );

void serial_in_init(  SERIAL_IN  * ptrSerial_io );
void serial_out_init( SERIAL_OUT * ptrSerial_io );
void serial_io_init(  SERIAL_IO  * ptrSerial_io );

#endif
