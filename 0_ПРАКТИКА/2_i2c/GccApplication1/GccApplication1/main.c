#include "main.h"

int hour = 15;
int minutes = 55;
double seconds = 0;
double interval = 0;
char data[80];

char get_lcd_data()
{
	return data;
}

void control_time()
{
	if (seconds >= 58.8)
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
	char *output = "";
	if (minutes < 10 && hour < 10)
	{
		output = "Kot el v: 0%d:0%d";
	}
	
	if (minutes < 10 && hour >= 10)
	{
		output = "Kot el v: %d:0%d";
	}
	
	if (minutes >= 10 && hour < 10)
	{
		output = "Kot el v: 0%d:%d";
	}
	
	if (minutes >= 10 && hour >= 10)
	{
		output = "Kot el v: %d:%d";
	}
	sprintf(data, output, hour, minutes);
}

ISR(TIMER1_OVF_vect)
{
	TCCR1B &= ~(1 << CS12);
	TCCR1B |= (1 << CS12);
	PORTB ^= (1 << PB1);
	seconds += 2.1;
	interval += 2.1;
	control_time();
}

ISR(INT0_vect)
{
	PORTB |= (1 << PB0);
	interval = 0;
	control_time();
	lcd_led(0);
	lcd_clrscr();
	format_time();
	lcd_puts(data);
}

ISR(INT1_vect)
{
	PORTB |= (1 << PB0);
	interval = 0;
	lcd_led(0);
	lcd_clrscr();
	lcd_home();
	event_listener();
}


int main(void)
{
	TIMSK |= (1 << TOIE1);
	sei();
	TCCR1B |= (1 << CS12);
	
	//внешние прерывания
	MCUCR = (1 << ISC11);
	GICR |= (1 << INT0) | (1 << INT1);
	DDRD = 0;
	PORTD |= (1 << PD2) | (1 << PD3) | (1 << MENU_BTN) | (1 << UP_BTN) | (1 << DOWN_BTN);
	
	// пин для дисплея
	DDRB |= (1 << PB0) | (1 << PB1);
	PORTB |= (1 << PB0) | (1 << PB1);
	
	lcd_init(LCD_DISP_ON);	
	lcd_home();
	lcd_clrscr();
	format_time();
	lcd_puts(data);
	
	while(1)
	{
		if (interval >= 10)
		{
			lcd_led(1);
			PORTB &= ~(1 << PB0);
		}
	}
}

