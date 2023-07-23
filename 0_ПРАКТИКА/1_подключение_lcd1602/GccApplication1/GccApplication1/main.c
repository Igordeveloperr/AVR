#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "LCD1602/lcd1602.h"

#define F_CPU 32768UL;

int hour = 0;
int minutes = 0;
int seconds = 0;
char str[80];


void control_time()
{
	if (minutes == 60)
	{
		hour++;
		minutes = 0;
	}
	
	if (hour == 23 && minutes == 59 && seconds == 58)
	{
		hour = 0;
		minutes = 0;
		seconds = 0;
	}
}

ISR(TIMER1_OVF_vect)
{
	TCCR1B &= ~(1 << CS10);
	TCCR1B |= (1 << CS10);
	seconds += 2;
	if (seconds == 60)
	{
		minutes++;
		seconds = 0;
		control_time();
		clear_lcd();
		sprintf(str, "%d:%d", hour, minutes);
		send_text(str);
	}
}

int main(void)
{	
	LCD_RS_E_DDR = (1 << RS) | (1 << RW) | (1 << E);
	LCD_DDR = 0b11111111;
	lcd_init();

	TIMSK |= (1 << TOIE1);
	sei();
	TCCR1B |= (1 << CS10);
	
	sprintf(str, "%d:%d", hour, minutes);
	send_text(str);
	while(1)
	{
		
	}
}

