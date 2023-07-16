#include <avr/io.h>
// ���������� ����������
#include <avr/interrupt.h>
#include <avr/delay.h>

// ��������� ����������
ISR(INT1_vect)
{
	PORTC |= (1 << PC0);
	_delay_ms(900);
	PORTC &= ~(1 << PC0);
}

void animation()
{
	if (PINB == 0b00001000)
	{
		PORTB = 0;
		PORTB |= (1 << PB0);
	}
	else
	{
		PORTB = PORTB << 1;
	}
	_delay_ms(200);
}

int main(void)
{
	// ����������� ������� ����������
	GICR = 0;
	GICR |= (1 << INT1) | (1 << INT0);
	// ��������� ������� ����������
	MCUCR = 0;
	MCUCR |= (1 << ISC11);
	
	// �������� ���������� ����������
	sei();
	
	// ������ � ������� i/o
	DDRD = 0;
	PORTD = 0;
	PORTD |= (1 << PD3);
	
	DDRB = 0b11111111;
	PORTB = 0;
	PORTB |= (1 << PB0);
	
	DDRC = 0;
	DDRC |= (1 << PC0);
	PORTC = 0;
	
    while (1) 
    {
		animation();
    }
}

