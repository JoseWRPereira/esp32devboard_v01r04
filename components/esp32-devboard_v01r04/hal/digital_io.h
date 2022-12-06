#ifndef DIGITAL_IO_H
#define DIGITAL_IO_H

#include "hal_types.h"
// struct DigitalIn_t
// {
//     int8_t e0:1;
//     int8_t e1:1;
//     int8_t e2:1;
//     int8_t e3:1;
//     int8_t e4:1;
//     int8_t e5:1;
//     int8_t e6:1;
//     int8_t e7:1;
// };

// struct DigitalOut_t
// {
//     int8_t rl0:1;
//     int8_t rl1:1;
//     int8_t ca0:1;
//     int8_t ca1:1;
//     int8_t s1:1;
//     int8_t s2:1;
//     int8_t s3:1;
//     int8_t s4:1;
// };

// typedef union DigitalIn_u
// {
//     struct DigitalIn_t bits;
//     uint8_t data;
// } DigitalIn;

// typedef union DigitalOut_u
// {
//     struct DigitalOut_t bits;
//     uint8_t data;
// } DigitalOut;

extern DigitalIn digital_in;
extern DigitalOut digital_out;

void digital_io_init( void );
void digital_io_scan( void );

#endif
