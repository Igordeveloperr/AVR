#include "main.h"

int hour = 17;
int minutes = 34;
double seconds = 0;
char str[80];
double interval = 0;
short avtive_menu = 0;



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
	char *out = "";
	if (minutes < 10 && hour < 10)
	{
		out = "Kot el v: 0%d:0%d";
	}
	
	if (minutes < 10 && hour >= 10)
	{
		out = "Kot el v: %d:0%d";
	}
	
	if (minutes >= 10 && hour < 10)
	{
		out = "Kot el v: 0%d:%d";
	}
	
	if (minutes >= 10 && hour >= 10)
	{
		out = "Kot el v: %d:%d";
	}
	sprintf(str, out, hour, minutes);
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

ISR(INT1_vect)
{
	if (!(PIND & (1 << MENU_BTN)))
	{
		avtive_menu = 1;
		lcd_clrscr();
	}
}

int main(void)
{
	TIMSK |= (1 << TOIE1);
	sei();
	TCCR1B |= (1 << CS12);
	
	//внешние прерывания
	MCUCR = 0;
	GICR |= (1 << INT0) | (1 << INT1);
	DDRD = 0;
	PORTD |= (1 << PD2) | (1 << PD3) | (1 << MENU_BTN) | (1 << UP_BTN) | (1 << DOWN_BTN);
	
	// сонный режим
	MCUCR |= (1 << SE);
	
	// пин для дисплея
	DDRB |= (1 << PB0) | (1 << PB1);
	PORTB |= (1 << PB0) | (1 << PB1);
	
	lcd_init(LCD_DISP_ON);	
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

