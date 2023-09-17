#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "lcdpcf8574/lcdpcf8574.h"
#include "pcf8574/pcf8574.h"

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

	lcd_gotoxy(0, 2);
	lcd_puts("Linia 3");

	lcd_gotoxy(0, 3);
	lcd_puts("Linia 4");

	for (;;) {

	}

	return 0;
}
