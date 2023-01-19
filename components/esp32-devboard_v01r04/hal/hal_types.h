#ifndef HAL_TYPES_H
#define HAL_TYPES_H


/////////////////////////////////////////
///////////////////////////////////////// Serial_IO
/////////////////////////////////////////

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


/////////////////////////////////////////
///////////////////////////////////////// Digital_IO
/////////////////////////////////////////
struct DigitalIn_t
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

struct DigitalOut_t
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

typedef union DigitalIn_u
{
    struct DigitalIn_t bits;
    uint8_t data;
} DigitalIn;

typedef union DigitalOut_u
{
    struct DigitalOut_t bits;
    uint8_t data;
} DigitalOut;


typedef struct Digital_ioT
{
    DigitalIn * input;
    DigitalOut * output;
    void (* init)( void );
    void (* scan)( void );
} Digital;


/////////////////////////////////////////
///////////////////////////////////////// LCD
/////////////////////////////////////////

typedef struct lcdT
{
    void (* init)(void);
    void (* clr)( void );

    /// @brief Escreve uma string na (linha,coluna) do display
    /// @param lin Posição linha a inserir string
    /// @param col Posição coluna a inserir string
    /// @param str String a ser exibida no display a partir da posição (li, col)
    void (* print)( unsigned char lin, unsigned char col, char * str );
    void (* num)( uint8_t lin, uint8_t col, int16_t num, uint8_t tam );
} Lcd;


/////////////////////////////////////////
///////////////////////////////////////// Keyboard
/////////////////////////////////////////
typedef struct keyboardT
{
    void (* init)( void );
    uint8_t (* key)( void );
} Keyboard;


/////////////////////////////////////////
///////////////////////////////////////// StepMotor
/////////////////////////////////////////
typedef struct stepmotorT
{
    void (* init)( void );
    void (* passos)(int32_t passos);
} Stepmotor;


/////////////////////////////////////////
///////////////////////////////////////// Analog
/////////////////////////////////////////
typedef struct adcT
{
    void (* init)( void );
} Adc;

/////////////////////////////////////////
///////////////////////////////////////// Global
/////////////////////////////////////////

typedef struct globalT
{
    void (* init)( void );
} Global;

/////////////////////////////////////////
///////////////////////////////////////// DevBoard
/////////////////////////////////////////

/// @brief Declaração dos objetos que compoem o objeto principal.
typedef struct devboardT
{
    Global global;
    Lcd lcd;
    Digital digital;
    Keyboard keyboard;
    Stepmotor stepmotor;
    Adc adc;
 } Devboard;


#endif