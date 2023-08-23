#include "main.h"

uint8_t hour = 13;
uint8_t minutes = 34;
uint8_t seconds = 0;
uint8_t cat_hour = 0;
uint8_t cat_minutes = 0;
uint8_t interval = 0;

/* реализация спящего режима */
void activate_sleep_mode()
{
	DS1302_ReadDateTime();
	if ((DateTime.Sec - interval) >= MAX_INTERVAL)
	{	
		interval = DateTime.Sec;
		TM1637_turnOff();
		sleep_enable();
		sleep_cpu();
	}
}

/* выход из сна + метка когда кот ел */
ISR(INT0_vect)
{
	sleep_disable();
	DS1302_ReadDateTime();
	cat_hour = DateTime.Hour;
	cat_minutes = DateTime.Min;
	EEPROM_write(HOUR_ADDRESS, cat_hour);
	EEPROM_write(MIN_ADDRESS, cat_minutes);
	wakeup_display();
	TM1637_setSegments(EAT_WORD, DISP_LEN, START_POS);
	interval = 0;
}

ISR(INT1_vect)
{
	sleep_disable();

	if (VIEW_BTN_CLICK)
	{
		wakeup_display();
		print_time_on_display(cat_hour, cat_minutes);
	}
	
	if(MENU_BTN_CLICK)
	{
		wakeup_display();
		event_listener();
		setup_time(&seconds, &minutes, &hour);
		print_time_on_display(hour, minutes);
	}
	interval = 0;
}

/* настройка внешних прерываний */
void setup_ext_interrapt()
{
	GICR |= (1 << INT0) | (1 << INT1);
	DDRD = 0;
	PORTD |= (1 << INT0_PIN) | (1 << INT1_PIN) | (1 << MENU_BTN) | (1 << UP_BTN) | (1 << DOWN_BTN) | (1 << VIEW_BTN);
}

int main(void)
{
	cli();
	ACSR |= (1 << ACD); // ОТКЛЮЧЕНИЕ АЦП
	setup_ext_interrapt();
	sei();
	
	DDRB |= (1 << PB0);
	PORTB |= (1 << PB0);
	
	cat_hour = EEPROM_read(HOUR_ADDRESS);
	cat_minutes = EEPROM_read(MIN_ADDRESS);
	
	TM1637_init();
	TM1637_turnOnAndSetBrightness(BRIGHTNES);
	TM1637_setSegments(HI_WORD, DISP_LEN, START_POS);
	_delay_ms(WAIT1S);
	
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	
	while(1)
	{
		activate_sleep_mode();
	}
}

