#include "lcd1602.h"
#include <util/delay.h>

void execute_cmd()
{
	LCD_RS_E_PORT |= (1 << E);
	_delay_ms(1);
	LCD_RS_E_PORT &= ~(1 << E);
}

void lcd_init()
{
	LCD_PORT = 0x38;
	execute_cmd();
	LCD_PORT = 0x0E;
	execute_cmd();
	LCD_PORT = 0x06;
	execute_cmd();
}

void send_char(unsigned char ch)
{
	LCD_PORT = ch;
	execute_cmd();
}

void send_text(char *str)
{
	LCD_RS_E_PORT |= (1 << RS); // RS open
	for (int i = 0; str[i]!=0; i++)
	{
		send_char(str[i]);
	}
	LCD_RS_E_PORT &= ~(1 << RS); // RS close
}

void next_line()
{
	LCD_PORT = 0xC0;
	execute_cmd();
}

void clear_lcd()
{
	LCD_PORT = 0x01;
	execute_cmd();
}