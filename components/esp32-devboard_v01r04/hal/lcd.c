#include <stdio.h>
#include "pinout.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lcd.h"
#include "serial_io.h"


Lcd lcd;


unsigned char lcdbus = 0;
SERIAL_OUT lcd_drv = {  LCD_CK_PIN,
                        LCD_DO_PIN,
                        LCD_LD_PIN,
                        &lcdbus,
                        1
                    };



void delay( unsigned int t )
{
    // vTaskDelay( t / portTICK_PERIOD_MS);
    vTaskDelay( pdMS_TO_TICKS( t ));
}

//****************** Interface com PORTs/Pinos
#define LCD_BUS( x )    lcdbus = ((lcdbus & 0x0F) | (x & 0xF0)), serial_out_scan(&lcd_drv)
#define LCD_EN( x )     lcdbus = x ? (lcdbus | 0x08) : (lcdbus & ~0x08), serial_out_scan(&lcd_drv)
#define LCD_RS( x )     lcdbus = x ? (lcdbus | 0x04) : (lcdbus & ~0x04)
#define LCD_ROWS        4
#define LCD_COLS        20
// __delay_ms( 2 );
// __delay_us( 40 );
#define LCD_SHORT_DELAY()           delay( 8 )
#define LCD_LONG_DELAY()            delay( 8 )



//****************** Definicao de Comandos ao LCD 
#define LCD_CLEAR_DISPLAY           0x01

#define LCD_RETURN_HOME             0x02

#define LCD_ENTRY_MODE_SET          0x04
#define LCD_EMS_CURSOR_RIGHT        0x02
#define LCD_EMS_CURSOR_LEFT         0x00
#define LCD_EMS_SHIFT_DISPLAY       0x01

#define LCD_DISPLAY_CONTROL         0x08
#define LCD_DC_DISPLAY_ON           0x04
#define LCD_DC_DISPLAY_OFF          0x00
#define LCD_DC_CURSOR_ON            0x02
#define LCD_DC_CURSOR_OFF           0x00
#define LCD_DC_BLINK_ON             0x01
#define LCD_DC_BLINK_OFF            0x00

#define LCD_CURSOR_SHIFT            0x10
#define LCD_CS_LEFT                 0x00
#define LCD_CS_RIGHT                0x04

#define LCD_DISPLAY_SHIFT           0x10
#define LCD_DS_LEFT                 0x08
#define LCD_DS_RIGHt                0x0C

#define LCD_FUNCTION_SET            0x20
#define LCD_FS_DATA_LENGTH_8        0x10
#define LCD_FS_DATA_LENGTH_4        0x00
#define LCD_FS_LINE_NUMBER_1        0x00
#define LCD_FS_LINE_NUMBER_2        0x08
#define LCD_FS_DOTS_FORMAT_5x8      0x00
#define LCD_FS_DOTS_FORMAT_5x11     0x04

#define LCD_SET_CGRAM_ADDRS( adrs ) (0x40+(adrs & 0x3F))

// #define LCD_SET_DDRAM_ADDRS( adrs ) (0x80+(adrs & 0x7F))
// #define LCD_ADDR_LINE_0             0x80
// #define LCD_ADDR_LINE_1             0xC0
// #define LCD_ADDR_LINE_2             0x94
// #define LCD_ADDR_LINE_3             0xD4

const char lcd_addr_line[4] = {0x80, 0xC0, 0x94, 0xD4};


/// @brief Envia uma instrução para o display (Instruction Register)
/// @param i Instrução a ser enviada ao display
void lcd_instReg( unsigned char i )
{
    LCD_RS( 0 );
    LCD_BUS( i );

    LCD_EN( 0 );
    if( i == LCD_CLEAR_DISPLAY || i == LCD_RETURN_HOME )
    {
        LCD_LONG_DELAY();
    }
    else
    {
        LCD_SHORT_DELAY();
    }
    LCD_EN( 1 );
    

    if( (i & 0xF0) == (LCD_FUNCTION_SET | LCD_FS_DATA_LENGTH_4) )
    {
        LCD_RS( 0 );
        LCD_BUS( i );
        LCD_EN( 0 );
        LCD_SHORT_DELAY();
        LCD_EN( 1 );
    }

    LCD_RS( 0 );
    LCD_BUS( i<<4 );
    LCD_EN( 0 );
    if( i == LCD_CLEAR_DISPLAY || i == LCD_RETURN_HOME )
    {
        LCD_LONG_DELAY();
    }
    else
    {
        LCD_SHORT_DELAY();
    }
    LCD_EN( 1 );
}



/// @brief Envia um caractere para o display (Data Register))
/// @param d Dado/caractere a ser impresso no display
void lcd_dataReg( unsigned char d )
{
    LCD_RS( 1 );
    LCD_BUS( d );
    LCD_EN(0);
    LCD_SHORT_DELAY();
    LCD_EN( 1 );

    LCD_RS( 1 );
    LCD_BUS( d << 4 );
    LCD_EN( 0 );
    LCD_SHORT_DELAY();
    LCD_EN( 1 );
}



/// @brief Posicionar o cursor na coordenada: (linha, coluna)
/// @param lin linha do display: começa em 0
/// @param col coluna do display: começa em 0
void lcd_lincol( unsigned char lin, unsigned char col)
{
    // lcd_instReg( LCD_SET_DDRAM_ADDRS( ((LCD_ADDR_LINE_1 * lin) + (col + LCD_ADDR_LINE_0)) ) );
    lcd_instReg( lcd_addr_line[lin] + col );
}




/// @brief Inicializa os pinos conectados ao display e em seguida o proprio display
/// @param - 
void lcd_init( void )
{
    delay(250);
    lcdbus = 0;
    serial_out_init( &lcd_drv );

    delay(250);
    LCD_EN( 1 );
    lcd_instReg( LCD_FUNCTION_SET|LCD_FS_DATA_LENGTH_4|LCD_FS_LINE_NUMBER_2 );
    lcd_instReg( LCD_DISPLAY_CONTROL|LCD_DC_DISPLAY_ON|LCD_DC_CURSOR_OFF|LCD_DC_BLINK_OFF );
    lcd_instReg( LCD_CLEAR_DISPLAY );
    lcd_instReg( LCD_RETURN_HOME );
    delay(500);
}



/// @brief Limpa conteudo do display LCD.
/// @param  -
void lcd_clr( void )
{
    lcd_instReg(LCD_CLEAR_DISPLAY);
}



/// @brief Escreve uma string na (linha,coluna) do display
/// @param lin Posição linha a inserir string
/// @param col Posição coluna a inserir string
/// @param str String a ser exibida no display a partir da posição (li, col)
void lcd_print( unsigned char lin, unsigned char col, char * str )
{
    char pos = col;
    lcd_lincol( lin, col );

    while( *str )
    {
        lcd_dataReg( *str );
        ++str;
        ++pos;
    }
}


/// @brief Escreve um número inteiro no display
/// @param lin Posição linha
/// @param col Posição coluna
/// @param num Número a ser impresso
/// @param tam Quantidade de caracteres que o número ocupa
void lcd_num( uint8_t lin, uint8_t col,
                    int16_t num, uint8_t tam )
{
    int div;
    unsigned char size;
    char sinal; // 0:+ 1:-
   
    sinal = num < 0;
    if( sinal )
        num = (~num) + 1;

    lcd_lincol(lin, col);
   
    div=10000;
    size = 5;
    while( div >= 1 )
    {
        if( num/div == 0 )
            --size;
        else
            break;
        div/=10;
    }

    while( tam > (size+sinal) && tam > 1 )
    {
        lcd_dataReg(' ');
        --tam;
    }  

    if( sinal )
        lcd_dataReg('-');

    
    while( div >= 1 )
    {
        lcd_dataReg( (unsigned char)(num / div) + '0' );
        num = num % div;
        div/=10;
    }
}


/// @brief Converte um número inteiro em uma string
/// @param num Número
/// @param pos Apontar local a ser inserida a string
void num2str( int num, char * pos )
{
    int mask = 10000;
    char print = 0;
    char n = 0;
    while( mask )
    {
        n = (num/mask)%10;
        if( print || n )
        {
            print = 1;
            *pos = n+'0';
            ++pos;
        }
        num %= mask;
        mask /= 10;
    }
}



