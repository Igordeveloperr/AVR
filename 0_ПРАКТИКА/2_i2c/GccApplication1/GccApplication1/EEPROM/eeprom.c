#include "../main.h"

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