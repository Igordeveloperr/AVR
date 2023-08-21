#include "../main.h"
// Функция инициализация шины I2C
void i2c_init(void)
{
TWBR = 2; // // Настройка скорости шины
TWSR = (1 << TWPS1)|(1 << TWPS0); // Предделитель на 64
TWCR |= (1 << TWEN); // Включение модуля TWI
}

// Функция начала передачи по шине I2C
void i2c_start(void)
{
TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTA); // Передача условия СТАРТ
while(!(TWCR & (1 << TWINT))); // Ожидание установки флага TWINT
}

// Функция окончания передачи по шине I2C
void i2c_stop(void)
{
TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO); // Передача условия СТОП
while(TWCR & (1 << TWSTO)); // Ожидание завершения передачи условия СТОП
}

// Функция записи данных по шине I2C
uint8_t i2c_write_byte(uint8_t data)
{
	TWDR = data; // Загрузка данных в TWDR
	TWCR = (1 << TWEN)|(1 << TWINT); // Сброс флага TWINT для начала передачи данных
	while(!(TWCR & (1 << TWINT))); // Ожидание установки флага TWINT
	// Проверка статуса
	// Если адрес DS1307+R и принято "подтверждение"(0x18)
	// или адрес DS1307+W и принято "подтверждение"(0x40)
	// или передается байт данных и принято "подтверждение"(0x28)
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x40 || (TWSR & 0xF8) == 0x28) return 1; // OK
	else return 0; // ОШИБКА
}

// Функция чтения данных по шине I2C
uint8_t i2c_read_byte(uint8_t *data, uint8_t ack)
{
	// Возвращаем "подтверждение" после приема
	if(ack) TWCR |= (1 << TWEA);
	// Возвращаем "неподтверждение" после приема
	// Ведомое устройство не получает больше данных
	// обычно используется для распознования последнего байта
	else TWCR &= ~(1 << TWEA);
	// Разрешение приема данных после сброса TWINT
	TWCR |= (1 << TWINT);
	while(!(TWCR & (1 << TWINT))); // Ожидание установки флага TWINT
	// Проверка статуса
	// Если принят байт данных и возвращается "подтверждение"(0x50)
	// или принят байт данных и возвращается "ненеподтверждение"(0x58)
	if((TWSR & 0xF8) == 0x50 || (TWSR & 0xF8) == 0x58)
	{
		*data = TWDR; // Читаем данные из TWDR
		return 1; // OK
	}
	else return 0; // ОШИБКА
}

// Функция чтения данных из DS1307
uint8_t DS1307Read(uint8_t address,uint8_t *data)
{
	uint8_t res;
	i2c_start(); // СТАРТ
	res = i2c_write_byte(0b11010000); // адрес DS1307+W
	if(!res)    return 0; // ОШИБКА
	// Передача адреса необходимого регистра
	res = i2c_write_byte(address);
	if(!res)    return 0; // ОШИБКА
	i2c_start(); // Повторный СТАРТ
	res = i2c_write_byte(0b11010001); // адрес DS1307+R
	if(!res)    return 0; // ОШИБКА
	// Чтение данных с "неподтверждением"
	res = i2c_read_byte(data,0);
	if(!res)    return 0; // ОШИБКА
	i2c_stop(); // СТОП
	return 1; // OK
}

// Функция записи данных в DS1307
uint8_t DS1307Write(uint8_t address,uint8_t data)
{
	uint8_t res;
	i2c_start(); // СТАРТ
	res = i2c_write_byte(0b11010000); // адрес DS1307+W
	if(!res)    return 0; // ОШИБКА
	// Передача адреса необходимого регистра
	res = i2c_write_byte(address);
	if(!res)    return 0; // ОШИБКА
	res = i2c_write_byte(data); // Запись данных
	if(!res)    return 0; // ОШИБКА
	i2c_stop(); // СТОП
	return 1; // OK
}