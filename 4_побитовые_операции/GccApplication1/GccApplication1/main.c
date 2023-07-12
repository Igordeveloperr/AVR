#include <avr/io.h>
#include <avr/delay.h>

void blink()
{
	PORTD ^= (1 << 0);
	_delay_ms(400);
}

void run_fire()
{
	for(int i = 6; i < 8 ; i++)
	{
		PORTD |= (1 << i);
		_delay_ms(500);
		PORTD &= ~(1 << i);
		_delay_ms(500);
	}	
}

void btn_click()
{
	if (~PINB & (1 << 0))
	{
		run_fire();
	}
	else
	{
		blink();
	}
}

int main(void)
{
	DDRD = 0b11111111;
	PORTD = 0b00000000;
	DDRB = 0b00000000;
	PORTB |= (1 << 0);
    while (1) 
    {
		btn_click();
    }
}

