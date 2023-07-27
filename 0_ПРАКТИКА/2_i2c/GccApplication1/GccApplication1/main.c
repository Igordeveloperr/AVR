#include <avr/io.h>
#include <avr/delay.h>
#include "main.h"

void i2c_start()
{
	DDRC |= (1 << SDA);
	_delay_ms(1);
	DDRC |= (1 << SCL);
}

void i2c_stop()
{
	DDRC |= (1 << SDA);
	_delay_ms(1);
	DDRC &= ~(1 << SCL);
	_delay_ms(1);
	DDRC &= ~(1 << SDA);
}

uint8_t i2c_send(uint8_t data)
{
	uint8_t i;
	for(i = 8; i > 0; i--)
	{
		// если бит 1, то на шину 1, иначе 0
		if (data & (1 << i))
		{
			DDRC &= ~(1 << SDA);
		}
		else
		{
			DDRC |= (1 << SDA);
		}
		_delay_ms(1);
		// тактируем передачу бита
		DDRC &= ~(1 << SCL);
		_delay_ms(1);
		DDRC |= (1 << SCL);
	}
	DDRC &= ~(1 << SDA);
	_delay_ms(1);
	DDRC &= ~(1 << SCL);
	_delay_ms(1);
	i = (SDA & (1 << SDA));
	DDRC |= (1 << SCL);
	return i;
}

int main(void)
{
			i2c_start();
			i2c_send(0x38);
			i2c_send(0x0E);
			i2c_send(0x06);
					//i2c_send(0x40);	// адрес дисплея
					//i2c_send(0); // R/W bit в ноль
					//i2c_send(0xF1); // данные
			i2c_stop();
    while (1) 
    {
    }
}

