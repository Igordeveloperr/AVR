#ifndef _I2CMASTER_H
#define _I2CMASTER_H

// флаг, отвечающий за чтение данных по i2c
#define I2C_READ    1

// флаг, отвечающий за отправку данных по i2c
#define I2C_WRITE   0

// частота тактирования линии в Герцах
#define SCL_CLOCK 100000L

// инициализация интерфейса
void i2c_init(void);

// передача условия СТОП на шину
void i2c_stop(void);

// передача условия СТАРТ на шину
unsigned char i2c_start(unsigned char addr);

// повторный старт(перезапуск)
unsigned char i2c_rep_start(unsigned char addr);

// ждем, если устрой-во занято, а потом передаем условие СТАРТ на шину
void i2c_start_wait(unsigned char addr);

 // отправка данных
unsigned char i2c_write(unsigned char data);

// читаем данные и продолжаем вещание
unsigned char i2c_readAck(void);

// читаем данные и после их получения передаем услови СТОП
unsigned char i2c_readNak(void);

// читаем данные с шины
unsigned char i2c_read(unsigned char ack);

// выбираем какой варинт чтения данных будет
#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak(); 
#endif
