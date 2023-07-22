#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define F_CPU 32768UL;

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

ISR(TIMER1_OVF_vect)
{
	PORTB |= (1 << PB0);
	seconds += 2;
	clear_lcd();
	sprintf(str, "%d", seconds);
	send_text(str);
}

int main(void)
{	
	DDRB = (1 << PB0);
	DDRC = (1 << PC0) | (1 << PC1) | (1 << PC2);
	DDRD = 0b11111111;
	lcd_init();

	TIMSK |= (1 << TOIE1);
	sei();
	TCCR1B |= (1 << CS10);
	while(1)
	{
		
	}
}

