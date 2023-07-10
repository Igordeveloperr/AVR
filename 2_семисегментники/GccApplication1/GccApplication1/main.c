#include <avr/io.h>
#include <avr/delay.h>

void setup()
{
	DDRD = 0b11111111;
}

void print_number()
{
	PORTD = 1 << 0;
	PORTD |= 1 << 1;
	PORTD |= 1 << 6;
	PORTD |= 1 << 3;
	PORTD |= 1 << 4;
}

int main(void)
{
	setup();
    while (1) 
    {
		print_number();
    }
}

