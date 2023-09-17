#include "main.h"

void lcd_puts_num(int number)
{
	char data[256];
	sprintf(data, "%d", number);
	lcd_puts(data);
}

int main(void)
{
	uint8_t count = 0;
	
	lcd_init(LCD_DISP_ON_BLINK);
	lcd_home();
	lcd_led(0);
	lcd_gotoxy(0, 0);
	lcd_puts("Hello epta!");
	_delay_ms(1000);
	lcd_clrscr();
	while (1)
	{
		lcd_home();
		lcd_puts("Count = ");
		lcd_gotoxy(8, 0);
		lcd_puts_num(count);
		count++;
		_delay_ms(1000);
	}

	return 0;
}
