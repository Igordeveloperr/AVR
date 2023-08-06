#include "../main.h"

void EEPROM_write(uint8_t address, uint8_t data)
{
	/* ������� ���������� ��������� ������ */
	while(EECR & (1<<EEWE));
	/* ���������� ����� � ������� ������ */
	EEAR = address;
	/* ���������� ������ � ������� ������ */
	EEDR = data;
	/* ��������� ������ � EEPROM */
	EECR |= (1<<EEMWE);
	/* ���������� ������ � EEPROM */
	EECR |= (1<<EEWE);
}

uint8_t EEPROM_read(uint8_t address)
{
	/* ������� ���������� ��������� ������ */
	while(EECR & (1<<EEWE));
	/* ��������� ����� ��� ����� ������ ������ */
	EEAR = address;
	/* �������� ������ �� EEPROM */
	EECR |= (1<<EERE);
	/* */
	return EEDR;
}