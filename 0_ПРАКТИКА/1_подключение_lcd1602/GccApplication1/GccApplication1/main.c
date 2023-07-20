#include <avr/io.h>

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


int main(void)
{	
	DDRC = (1 << PC0) | (1 << PC1) | (1 << PC2);
	DDRD = 0b11111111;
	lcd_init();
	send_text("Hello world!");
	next_line();
	send_text("I'm Gokhlia");
}

