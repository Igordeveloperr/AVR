#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define F_CPU 32768UL;

int hour = 0;
int minutes = 0;
int seconds = 0;
char str[80];

void execute_cmd()
{
	TCCR0 |= (1 << CS00); // timer on
	while (TCNT0 != 255)
	{
		PORTC |= (1 << PC2);
	}
	PORTC &= ~(1 << PC2);
	TCNT0 = 0;
	TCCR0 &= ~(1 << CS00); // timer off
}

void lcd_init()
{
	PORTD = 0x38;
	execute_cmd();	
	PORTD = 0x0E;
	execute_cmd();
	PORTD = 0x06;
	execute_cmd();
}

void send_char(unsigned char ch)
{
	PORTD = ch;
	execute_cmd();
}

void send_text(char *str)
{
	PORTC |= (1 << PC0); // RS open
	for (int i = 0; str[i]!=0; i++)
	{
		send_char(str[i]);
	}
	PORTC &= ~(1 << PC0); // RS close
}

void next_line()
{
	PORTD = 0xC0;
	execute_cmd();
}

void clear_lcd()
{
	PORTD = 0x01;
	execute_cmd();
}

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
	TCNT1 = 0;
}

int main(void)
{	
	DDRC = (1 << PC0) | (1 << PC1) | (1 << PC2);
	DDRD = 0b11111111;
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

