#include "../main.h"
// ������� ������������� ���� I2C
void i2c_init(void)
{
TWBR = 2; // // ��������� �������� ����
TWSR = (1 << TWPS1)|(1 << TWPS0); // ������������ �� 64
TWCR |= (1 << TWEN); // ��������� ������ TWI
}

// ������� ������ �������� �� ���� I2C
void i2c_start(void)
{
TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTA); // �������� ������� �����
while(!(TWCR & (1 << TWINT))); // �������� ��������� ����� TWINT
}

// ������� ��������� �������� �� ���� I2C
void i2c_stop(void)
{
TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO); // �������� ������� ����
while(TWCR & (1 << TWSTO)); // �������� ���������� �������� ������� ����
}

// ������� ������ ������ �� ���� I2C
uint8_t i2c_write_byte(uint8_t data)
{
	TWDR = data; // �������� ������ � TWDR
	TWCR = (1 << TWEN)|(1 << TWINT); // ����� ����� TWINT ��� ������ �������� ������
	while(!(TWCR & (1 << TWINT))); // �������� ��������� ����� TWINT
	// �������� �������
	// ���� ����� DS1307+R � ������� "�������������"(0x18)
	// ��� ����� DS1307+W � ������� "�������������"(0x40)
	// ��� ���������� ���� ������ � ������� "�������������"(0x28)
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x40 || (TWSR & 0xF8) == 0x28) return 1; // OK
	else return 0; // ������
}

// ������� ������ ������ �� ���� I2C
uint8_t i2c_read_byte(uint8_t *data, uint8_t ack)
{
	// ���������� "�������������" ����� ������
	if(ack) TWCR |= (1 << TWEA);
	// ���������� "���������������" ����� ������
	// ������� ���������� �� �������� ������ ������
	// ������ ������������ ��� ������������� ���������� �����
	else TWCR &= ~(1 << TWEA);
	// ���������� ������ ������ ����� ������ TWINT
	TWCR |= (1 << TWINT);
	while(!(TWCR & (1 << TWINT))); // �������� ��������� ����� TWINT
	// �������� �������
	// ���� ������ ���� ������ � ������������ "�������������"(0x50)
	// ��� ������ ���� ������ � ������������ "�����������������"(0x58)
	if((TWSR & 0xF8) == 0x50 || (TWSR & 0xF8) == 0x58)
	{
		*data = TWDR; // ������ ������ �� TWDR
		return 1; // OK
	}
	else return 0; // ������
}

// ������� ������ ������ �� DS1307
uint8_t DS1307Read(uint8_t address,uint8_t *data)
{
	uint8_t res;
	i2c_start(); // �����
	res = i2c_write_byte(0b11010000); // ����� DS1307+W
	if(!res)    return 0; // ������
	// �������� ������ ������������ ��������
	res = i2c_write_byte(address);
	if(!res)    return 0; // ������
	i2c_start(); // ��������� �����
	res = i2c_write_byte(0b11010001); // ����� DS1307+R
	if(!res)    return 0; // ������
	// ������ ������ � "����������������"
	res = i2c_read_byte(data,0);
	if(!res)    return 0; // ������
	i2c_stop(); // ����
	return 1; // OK
}

// ������� ������ ������ � DS1307
uint8_t DS1307Write(uint8_t address,uint8_t data)
{
	uint8_t res;
	i2c_start(); // �����
	res = i2c_write_byte(0b11010000); // ����� DS1307+W
	if(!res)    return 0; // ������
	// �������� ������ ������������ ��������
	res = i2c_write_byte(address);
	if(!res)    return 0; // ������
	res = i2c_write_byte(data); // ������ ������
	if(!res)    return 0; // ������
	i2c_stop(); // ����
	return 1; // OK
}