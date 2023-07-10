#include <avr/io.h>


int main(void)
{
	DDRB = 0b01111111;
    while (1) 
    { 
		PORTB |= (1 << 7);
		
		if (~PINB & (1 << 7))
		{
			PORTB |= (1 << 4);
		}
		else
		{
			PORTB &= ~(1 << 4);
		}
		
    }
}

