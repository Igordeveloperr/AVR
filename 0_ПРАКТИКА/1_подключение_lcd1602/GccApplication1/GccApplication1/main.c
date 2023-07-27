#include "main.h"

int hour = 0;
int minutes = 0;
int seconds = 0;
char str[80];


void control_time()
{
	if (hour == 23 && minutes >= 60)
	{
		hour = 0;
		minutes = 0;
		seconds = 0;
	}
	
	if (minutes >= 60)
	{
		hour++;
		minutes = 0;
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
	TCCR1B &= ~(1 << CS10);
	TCCR1B |= (1 << CS10);
	seconds += 2;
	if (seconds == 60)
	{
		minutes++;
		seconds = 0;
		control_time();
		//clear_lcd();
		format_time();
		//send_text(str);
	}
}

int main(void)
{	
	lcd_ini();

	TIMSK |= (1 << TOIE1);
	sei();
	TCCR1B |= (1 << CS10);
	
	send_byte(0x01, 1);
	//clear_lcd();
	format_time();
	lcd_str(str);
	
	while(1)
	{
		
	}
}

