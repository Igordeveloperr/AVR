#include <avr/io.h>
#define F_CPU 1000000UL
#include "avr/delay.h"

void EEPROM_write(uint8_t address, uint8_t data)
{
	/* ожидаем завершение процедуры записи */
	while(EECR & (1<<EEWE));
	/* записываем адрес в регистр адреса */
	EEAR = address;
	/* записываем данные в регистр данных */
	EEDR = data;
	/* разрешаем запись в EEPROM */
	EECR |= (1<<EEMWE);
	/* производим запись в EEPROM */
	EECR |= (1<<EEWE);
}

uint8_t EEPROM_read(uint8_t address)
{
	/* ожидаем завершение процедуры записи */
	while(EECR & (1<<EEWE));
	/* указываем адрес где лежат нужные данные */
	EEAR = address;
	/* получаем данные из EEPROM */
	EECR |= (1<<EERE);
	/* */
	return EEDR;
}

int main(void)
{
	uint8_t count1, count2 = 0;
	
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);
	DDRD = 0;
	PORTD |= (1 << PD0) | (1 << PD1);
	PORTB = EEPROM_read(0x00);
	PORTC = EEPROM_read(0x01);
	
    while (1) 
    {
		if (!(PIND & (1 << PD0)))
		{
			if(count1 < 10)
			{
				count1++;
			}
			else
			{
				count1 = 0;
			}
			PORTB = count1;
			EEPROM_write(0x00, count1);
		}
		_delay_ms(300);
		
		if (!(PIND & (1 << PD1)))
		{
			if(count2 < 10)
			{
				count2++;
			}
			else
			{
				count2 = 0;
			}
			PORTC = count2;
			EEPROM_write(0x01, count2);
		}
		
		_delay_ms(300);
		
    }
}

