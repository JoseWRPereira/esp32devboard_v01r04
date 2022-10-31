#ifndef DIGITAL_IO_H
#define DIGITAL_IO_H

struct digital_in_t
{
    int8_t e0:1;
    int8_t e1:1;
    int8_t e2:1;
    int8_t e3:1;
    int8_t e4:1;
    int8_t e5:1;
    int8_t e6:1;
    int8_t e7:1;
};

struct digital_out_t
{
    int8_t rl0:1;
    int8_t rl1:1;
    int8_t ca0:1;
    int8_t ca1:1;
    int8_t s1:1;
    int8_t s2:1;
    int8_t s3:1;
    int8_t s4:1;
};

typedef union digital_in_u
{
    struct digital_in_t bits;
    uint8_t data;
} DIGITAL_IN;

typedef union digital_ou_u
{
    struct digital_out_t bits;
    uint8_t data;
} DIGITAL_OUT;

extern DIGITAL_IN digital_in;
extern DIGITAL_OUT digital_out;

void digital_io_init( void );
void digital_io_scan( void );

#endif
