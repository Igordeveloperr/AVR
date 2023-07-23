#ifndef __LCD1602__
#define __LCD1602__

#include <avr/io.h>
#define LCD_DDR DDRD
#define LCD_PORT PORTD
#define LCD_RS_E_DDR DDRC
#define LCD_RS_E_PORT PORTC
#define RS PC0
#define RW PC1
#define E PC2

void lcd_init();
void send_char(unsigned char ch);
void send_text(char *str);
void next_line();
void clear_lcd();

#endif