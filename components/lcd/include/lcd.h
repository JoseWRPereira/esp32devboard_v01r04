
#ifndef LCD_H
#define LCD_H

void lcd_init( void );
void lcd_clr( void );
// void lcd_print( unsigned char lin, unsigned char col, const char * str );
void lcd_print( unsigned char lin, unsigned char col, char * str );
// void lcd_num(  unsigned char lin, unsigned char col,
//                     int num, unsigned char tam );
void lcd_num( uint8_t lin, uint8_t col,
                    int16_t num, uint8_t tam );

void num2str( int num, char * pos );

#endif