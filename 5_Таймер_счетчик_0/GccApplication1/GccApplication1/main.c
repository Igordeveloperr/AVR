#include <avr/io.h>
#include <avr/delay.h>

void switch_leds()
{
	if (PIND == 0xff)
	{
		PORTD = 0b00000001;
	}
	else
	{
		PORTD |= PORTD << 2;
	}
}

int main(void)
{
	int count = 0;
	DDRD = 0b11111111;
	PORTD = 0b00000001;
	
	// инициализация таймера 0
	TCCR0 |= (1 << 0) | (1 << 2);
	
	// обнуляем занчение таймера
	TCNT0 = 0;
	
    while (1) 
    {
		// типа раз в 1 секунду короч
		if (count == 2)
		{
			switch_leds();
			count = 0;
		}
		
		
		if (TCNT0 == 255)
		{
			count++;
			TCNT0 = 0;
		}
    }
}

