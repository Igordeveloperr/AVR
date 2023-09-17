#include "main.h"

int main(void)
{
	lcd_init(LCD_DISP_ON_BLINK);
	lcd_home();

	/* LCD test */
	lcd_led(0);
	lcd_gotoxy(0, 0);
	lcd_puts("Linia 1");

	lcd_gotoxy(0, 1);
	lcd_puts("Linia 2");
	
	lcd_home();

	while (1)
	{
	}

	return 0;
}
