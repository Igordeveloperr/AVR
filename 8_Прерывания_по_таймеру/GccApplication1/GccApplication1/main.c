#include <avr/io.h>
#define F_CPU 1000000UL
#include <avr/interrupt.h>
#include <avr/delay.h>

int pins[] = {PC0, PC1, PC2, PC3};

// обработка переполнения таймера прерыванием
ISR(TIMER1_OVF_vect){
	PORTB |= (1 << PB0);
	_delay_ms(200);
	PORTB &= ~(1 << PB0);
	_delay_ms(200);
	TCNT1 = 0;
}

void ran_fire()
{
	for (int i = 0; i < sizeof(pins) / sizeof(int); i++)
	{
		PORTC |= (1 << pins[i]);
		_delay_ms(200);
		PORTC &= ~(1 << pins[i]);
		_delay_ms(200);
	}
}

int main(void)
{
	DDRC = 0b0001111;
	PORTC = 0;
	DDRB = 0b00000001;
	
	// включаем прерывание по таймеру
	TIMSK = 0;
	TIMSK |= (1 << TOIE1);
	sei();
	
	// настройка самого таймера
	TCCR1B = 0;
	TCCR1B |= (1 << CS11) | (1 << CS10);
	
    while (1) 
    {
		ran_fire();
    }
}

