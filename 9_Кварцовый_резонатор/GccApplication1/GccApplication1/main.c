#include <avr/io.h>
#include <avr/delay.h>
#define F_CPU 8000000UL

int main(void)
{
	DDRD |= (1 << PD0);
	PORTD &= ~(1 << PD0);
	
    while (1) 
    {
		PORTD ^= (1 << PD0);
		_delay_ms(200);
    }
}

