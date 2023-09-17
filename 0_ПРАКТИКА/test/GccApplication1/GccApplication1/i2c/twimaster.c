#include "../main.h"

// инициализация интерфейса i2c
void i2c_init(void)
{
  // предделитель тактовой частоты равен 1 
  TWSR = 0;     
  // рассчет скорости передачи данных                   
  TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
}

// передача условия СТАРТ на шину
unsigned char i2c_start(unsigned char address)
{
    uint8_t   twst;
	
	// отправка условия СТАРТ
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// ожидание завершения передачи условия СТАРТ
	while(!(TWCR & (1<<TWINT)));
	// проверка значений регистра
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;
	// отправка адреса устрой-ва
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);
	// ожидание ответа от ведомого уст-ва
	while(!(TWCR & (1<<TWINT)));
	// проверка полученных значений
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

	return 0;

}

// ждем, если устрой-во занято, а потом передаем условие СТАРТ на шину
void i2c_start_wait(unsigned char address)
{
    uint8_t   twst;

    for(;;)
    {
	    // отправка условия СТАРТ
	    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    	// ожидание завершения передачи условия СТАРТ
    	while(!(TWCR & (1<<TWINT)));
    	// проверка значений регистра
    	twst = TW_STATUS & 0xF8;
    	if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
    	// отправка адреса устрой-ва
    	TWDR = address;
    	TWCR = (1<<TWINT) | (1<<TWEN);
    	 // ожидание ответа от ведомого уст-ва
    	while(!(TWCR & (1<<TWINT)));
    	// проверка занято ли ведомое уст-во
    	twst = TW_STATUS & 0xF8;
    	if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) ) 
    	{    	    
    	    // устройство занято, отправьте условие остановки для прекращения операции записи
	        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	        // ждем освобождения шины
	        while(TWCR & (1<<TWSTO));
    	    continue;
    	}
    	break;
     }
}

// тупа повторяем условие СТАРТ
unsigned char i2c_rep_start(unsigned char address)
{
    return i2c_start(address);
}

// передача условия СТОП на шину
void i2c_stop(void)
{
    // отправка условия СТОП
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	// ждем выполнения условия остановки
	while(TWCR & (1<<TWSTO));
}

// отправка данных, если функция вернет 0, то все успешно, иначе нет
unsigned char i2c_write( unsigned char data )
{	
    uint8_t   twst;
    
	// отправляем данные на уст-во
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	// ждем завершения передачи
	while(!(TWCR & (1<<TWINT)));
	// записываем ответ от ведомого уст-ва
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;
}

// читаем данные и продолжаем вещание
unsigned char i2c_readAck(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));    

    return TWDR;
}

// читаем данные и после их получения передаем услови СТОП
unsigned char i2c_readNak(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
    return TWDR;
}
