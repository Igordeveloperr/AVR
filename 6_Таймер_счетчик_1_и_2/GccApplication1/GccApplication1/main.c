#include <avr/io.h>
#define  F_CPU 1000000UL

int main(void)
{
	DDRB = 0b11111111;
	PORTB = 0;
	
	DDRD = 0b11111111;
	PORTD = 0;
	
	TCCR1B = 0;
	TCCR1B |= (1 << CS11) | (1 << CS10);
	TCNT1 = 0;
	
	int t = 0;
	
    while (1) 
    {	
		if (TCNT1 == 0)
		{
			PORTD = 0b10101010;
		}
		if (TCNT1 == 32768)
		{
			PORTD = 0;
			PORTD |= (1 << 0) | (1 << 7);
		}
		if (TCNT1 == 55000)
		{
			PORTD = 0b11111111;
			PORTB &= ~(1 << PB0);
		}
		if (TCNT1 == 65535)
		{
			PORTD = 0;
			t = t + 1;
			TCNT1 = 0;
		}
		
		if (t == 3)
		{
			PORTB |= (1 << PB0);
			t = 0;
		}	
    }
}

