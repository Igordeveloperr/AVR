#include "main.h"

int hour = 15;
int minutes = 6;
double seconds = 0;
char str[80];

double interval = 0;


void control_time()
{
	if (seconds >= 60)
	{
		minutes++;
		seconds = 0;
	}
	if (minutes >= 60)
	{
		hour++;
		minutes = 0;
	}
	if (hour == 23 && minutes >= 60)
	{
		hour = 0;
		minutes = 0;
		seconds = 0;
	}
}

void format_time()
{
	if (minutes < 10 && hour < 10)
	{
		sprintf(str, "0%d:0%d", hour, minutes);
	}
	
	if (minutes < 10 && hour >= 10)
	{
		sprintf(str, "%d:0%d", hour, minutes);
	}
	
	if (minutes >= 10 && hour < 10)
	{
		sprintf(str, "0%d:%d", hour, minutes);
	}
	
	if (minutes >= 10 && hour >= 10)
	{
		sprintf(str, "%d:%d", hour, minutes);
	}
}

ISR(TIMER1_OVF_vect)
{
	TCCR1B &= ~(1 << CS12);
	TCCR1B |= (1 << CS12);
	PORTB ^= (1 << PB1);
	seconds += 2.09712;
	interval += 2.09712;
	control_time();
}

ISR(INT0_vect)
{
	PORTB |= (1 << PB0);
	interval = 0;
	control_time();
	lcd_clrscr();
	format_time();
	lcd_puts(str);
}

int main(void)
{
	TIMSK |= (1 << TOIE1);
	sei();
	TCCR1B |= (1 << CS12);
	
	//внешние прерывания
	GICR |= (1 << INT0);
	DDRD = 0;
	PORTD |= (1 << PD2);
	
	// сонный режим
	MCUCR |= (1 << SE);
	
	// пин для дисплея
	DDRB |= (1 << PB0) | (1 << PB1);
	PORTB |= (1 << PB0) | (1 << PB1);
	
	lcd_init(LCD_DISP_ON_BLINK);	
	lcd_home();
	lcd_clrscr();
	format_time();
	lcd_puts(str);
	
	while(1)
	{
		if (interval >= 10)
		{
			PORTB &= ~(1 << PB0);
			asm("sleep"); // погружение мк в сон
		}
	}
}

