#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL

/*
	�����������	 �����
	����� - 8 ���
	��� �������� - ���
	���� ���� ���
	������� - 9600 BOD
*/
void UART_init(void)
{
	UBRR0L = 12;
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

/*
	���� ������������ �������� ������
	���������� ����� ��������
*/
void UART_send(char data)
{
	while(!(UCSR0A&(1 << UDRE0)));
	UDR0 = data;
}

/*
	��������� ���������� �� ����� ������
	����� ������ �� �������� � ���������� ��
*/
uint8_t UART_read_com(void)
{
	uint8_t data = -1;
	if(UCSR0A&(1 << RXC0))
	{
		data = UDR0;
	}
	return data;
}

/*
	������������ ������ ����������� ����
*/
void network_error_blink(void)
{
	PORTB |= (1 << PB0) | (1 << PB1);
	_delay_ms(500);
	PORTB &= ~(1 << PB0);
	PORTB &= ~(1 << PB1);
	_delay_ms(500);
	PORTB |= (1 << PB0) | (1 << PB1);
}

/*
	������������ ������������ ����
*/
void activate_diode(void)
{
	PORTB &= ~(1 << PB0);
	PORTB &= ~(1 << PB1);
	uint8_t res = UART_read_com();
	if (res == 48)
	{
		PORTB |= (1 << PB0);
	}
	else if (res == 49)
	{
		PORTB |= (1 << PB1);
	}
	else
	{
		network_error_blink();
	}
}

/*
	������������ �� ����� ������� ��������� ���������
*/
void setup(void)
{
	DDRB |= (1 << PB0) | (1 << PB1);
	UCSR0B |= (1 << RXCIE0);
	sei();
}

/*
	���������� �� ������� ������, ���������� ����� UART
*/
ISR(USART_RX_vect)
{
	activate_diode();
}

int main(void)
{
	setup();
	network_error_blink();
	UART_init();
    while (1) 
    {
		
    }
}

