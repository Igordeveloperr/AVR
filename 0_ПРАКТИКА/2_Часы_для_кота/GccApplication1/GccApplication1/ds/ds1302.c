#include "ds1302.h"

uint8_t DS1302_Bin8_To_BCD(uint8_t data)
{
   uint8_t nibh;
   uint8_t nibl;

   nibh=data/10;
   nibl=data-(nibh*10);

   return((nibh<<4)|nibl);
}

uint8_t DS1302_BCD_To_Bin8(uint8_t data)
{
unsigned char result;		
	result = ((data>>4) & 0b00000111);
	data &= 0x0F;
	data = data + result*10;
	return data;
}

//посылаем команду или байт данных в часы
void ds1302_write(unsigned char cmd)
{
unsigned char i;
	DS1302_DDR_RTC |= (1<<DS1302_E) | (1<<DS1302_SCLK);
	DS1302_PORT_RTC |= (1<<DS1302_E);//E=1
	_delay_us(1);
	DS1302_DDR_RTC |= (1<<DS1302_IO);//выход
	for(i=0; i<8; i++)
	{
		if((cmd&(1<<i)) == 1<<i)
		{
			DS1302_PORT_RTC |= (1<<DS1302_IO);
		}
		else
		{
			DS1302_PORT_RTC &= ~(1<<DS1302_IO);
		}
		DS1302_PORT_RTC |= (1<<DS1302_SCLK);
		_delay_us(1);
		DS1302_PORT_RTC &= ~(1<<DS1302_IO);
		DS1302_PORT_RTC &= ~(1<<DS1302_SCLK);
	} 
}
//вызываем после записи байта данных в часы
void ds1302_end_write_data()
{
	DS1302_PORT_RTC &= ~(1<<DS1302_E);
}

unsigned char ds1302_read()
{
unsigned char readbyte;
unsigned char i;
	readbyte=0;
	DS1302_DDR_RTC &= ~(1<<DS1302_IO);
	for(i=0;i<8;i++)
	{
		DS1302_PORT_RTC |= 1<<DS1302_SCLK;
		if((DS1302_PIN_RTC & (1<<DS1302_IO))==0)
		{
			readbyte &= ~(1<<i);
		}
		else
		{
			readbyte |= 1<<i;
		}
		_delay_us(1);
		DS1302_PORT_RTC &= ~(1<<DS1302_SCLK);
		_delay_us(1);
	}
	DS1302_PORT_RTC &= ~(1<<DS1302_E);
	_delay_us(1);
	return readbyte;
}

void DS1302_ReadDateTime() {
	//read seconds
	ds1302_write(0x81);
	DateTime.Sec = DS1302_BCD_To_Bin8(ds1302_read());
	//read minutes
	ds1302_write(0x83);
	DateTime.Min = DS1302_BCD_To_Bin8(ds1302_read());
	//read hour
	ds1302_write(0x85);
	DateTime.Hour = ds1302_read();
	DateTime.AMPM = (DateTime.Hour & 0b00100000);
	DateTime.H12_24 = (DateTime.Hour & 0b10000000);
	if (DateTime.H12_24 == H12) {
		DateTime.Hour = DateTime.Hour & 0b00011111;
	}
	else {
		DateTime.Hour = DateTime.Hour & 0b00111111;
	}
	DateTime.Hour = DS1302_BCD_To_Bin8(DateTime.Hour);
	//read day
	ds1302_write(0x87);
	DateTime.Day = DS1302_BCD_To_Bin8(ds1302_read());
	//read month
	ds1302_write(0x89);
	DateTime.Month = DS1302_BCD_To_Bin8(ds1302_read());
	//read weekday
	ds1302_write(0x8B);
	DateTime.WeekDay=ds1302_read();
	//read year
	ds1302_write(0x8D);
	DateTime.Year = DS1302_BCD_To_Bin8(ds1302_read());
}

void DS1302_WriteDateTime() {
uint8_t tmp;
	//set seconds
	ds1302_write(0x80);
	ds1302_write(DS1302_Bin8_To_BCD(DateTime.Sec));
	ds1302_end_write_data();
	//set minutes
	ds1302_write(0x82);
	ds1302_write(DS1302_Bin8_To_BCD(DateTime.Min));
	ds1302_end_write_data();
	//set hour	
	tmp = (DS1302_Bin8_To_BCD(DateTime.Hour) | DateTime.AMPM | DateTime.H12_24);
	ds1302_write(0x84);
	ds1302_write(tmp);
	ds1302_end_write_data();
	//set dade
	ds1302_write(0x86);
	ds1302_write(DS1302_Bin8_To_BCD(DateTime.Day));
	ds1302_end_write_data();
	//set month
	ds1302_write(0x88);
	ds1302_write(DS1302_Bin8_To_BCD(DateTime.Month));
	ds1302_end_write_data();
	//set day (of week)
	ds1302_write(0x8A);
	ds1302_write(DateTime.WeekDay);
	ds1302_end_write_data();
	//set year
	ds1302_write(0x8C);
	ds1302_write(DS1302_Bin8_To_BCD(DateTime.Year));
	ds1302_end_write_data();
}
