
#ifndef LCD_H
#define LCD_H

#include "hal_types.h"
// typedef struct lcdT
// {
//     void (* init)(void);
//     void (* print)( unsigned char lin, unsigned char col, char * str );
// } Lcd;

extern Lcd lcd;

void lcd_init( void );
void lcd_clr( void );
// void lcd_print( unsigned char lin, unsigned char col, const char * str );

/// @brief Escreve uma string na (linha,coluna) do display
/// @param lin Posição linha a inserir string
/// @param col Posição coluna a inserir string
/// @param str String a ser exibida no display a partir da posição (li, col)
void lcd_print( unsigned char lin, unsigned char col, char * str );
// void lcd_num(  unsigned char lin, unsigned char col,
//                     int num, unsigned char tam );
void lcd_num( uint8_t lin, uint8_t col,
                    int16_t num, uint8_t tam );

void num2str( int num, char * pos );

#endif