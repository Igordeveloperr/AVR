#ifndef	DS1302_H
#define	DS1302_H

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DS1302_E 0
#define DS1302_SCLK 1
#define DS1302_IO 2
#define DS1302_DDR_RTC DDRC
#define DS1302_PORT_RTC PORTC
#define DS1302_PIN_RTC PINC

#define AM 0
#define PM 0b00100000

#define H12 0b10000000
#define H24 0

typedef	struct
	{
	uint8_t		Sec;
	uint8_t		Min;
	uint8_t		Hour;
	uint8_t		Month;
	uint8_t		Day;
	uint8_t		Year;
	uint8_t		WeekDay;
	uint8_t		AMPM;
	uint8_t		H12_24;
	} tpDateTime;

tpDateTime	DateTime;

void DS1302_ReadDateTime();
void DS1302_WriteDateTime();

#endif

