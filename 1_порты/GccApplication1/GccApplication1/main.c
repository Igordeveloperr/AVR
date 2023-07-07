#include <avr/io.h>
#include <avr/delay.h>

const short LED_COUNT = 8;

void setup()
{
	DDRC = 0b0100011;
	PORTC = (1 << 0);	
	DDRD = 0b00001000;
	DDRB = 0b11111111;
}

void running_fire()
{
	for(short i = 0; i < LED_COUNT; i++)
	{
		PORTB |= PORTB << 1;
		_delay_ms(300);
	}
}

int main(void)
{
	setup();
	running_fire();	
    while (1) 
    {
		_delay_ms(300);
		PORTD = (1 << 3);
		_delay_ms(300);
		PORTD = (0 << 3);
		
		PORTC |= (1 << 5);
		PORTC |= (1 << 1);
		
    }
}

