#include "main.h"

int main(void)
{
	lcd_init(LCD_DISP_ON_BLINK);
	lcd_clrscr();
	lcd_puts("hello");
    while (1) 
    {
    }
}

