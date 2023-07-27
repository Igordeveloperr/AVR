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
	}
}

ISR(INT0_vect)
{
	control_time();
	lcd_clear();
	format_time();
	lcd_str(str);
}

int main(void)
{
	TIMSK |= (1 << TOIE1);
	sei();
	TCCR1B |= (1 << CS10);
	
	//������� ����������
	MCUCR |= (1 << ISC01);
	GICR |= (1 << INT0);
	DDRD = 0;
	PORTD |= (1 << PD2);
	
	// ������ �����
	MCUCR |= (1 << SE);
	MCUCR &= ~(1 << SM2);
	MCUCR &= ~(1 << SM1);
	MCUCR &= ~(1 << SM0);
	
	lcd_ini();	
	lcd_clear();
	format_time();
	lcd_str(str);
	
	while(1)
	{
	}
}

