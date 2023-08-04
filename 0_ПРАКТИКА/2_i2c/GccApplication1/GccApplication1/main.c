#include "main.h"

uint8_t hour = 12;
uint8_t minutes = 5;
uint8_t seconds = 0;
uint8_t interval = 0;

/* часы по значению */
uint8_t get_hour()
{
	return hour;
}

/* минуты по значению */
uint8_t get_min()
{
	return minutes;
}

/* секунды по значению */
uint8_t get_sec()
{
	return seconds;
}

/* реализация спящего режима */
void activate_sleep_mode()
{
	if (interval >= MAX_INTERVAL)
	{	
		TM1637_turnOff();
		OCR2 = 1;
		/* жду сброс флагов */
		while (ASSR != ASSR_REG_REDY);
		sleep_enable();
		sleep_cpu();
	}
}

/* отсчет времени */
ISR(TIMER2_OVF_vect)
{
	TCNT2 = 0;
	seconds += STEP;
	interval += STEP;
	control_seconds(&seconds, &minutes);
	control_min(&minutes, &hour);
	control_hour(&seconds, &minutes, &hour);
}

/* выход из сна + метка когда кот ел */
ISR(INT0_vect)
{
	sleep_disable();
	control_seconds(&seconds, &minutes);
	control_min(&minutes, &hour);
	control_hour(&seconds, &minutes, &hour);
	interval = 0;
	wakeup_display();
	print_time_on_display();
}

ISR(INT1_vect)
{
	/*_delay_us(1);
	lcd_wakeup();
	event_listener();
	interval = 0;*/
}

/* настройка Timer/Counter2 */
void start_timer2_async()
{
	ASSR |= (1 << AS2); // вклю асинхронный режим
	/* чищу регистры таймера от мусора */
	TCCR2 = 0;
	OCR2 = 0;
	TCNT2 = 0;
	/* делитель частоты = 256 */
	TCCR2 |= (1 << CS22) | (1 << CS21);
	/* жду сброс флагов для старта в асинхронном режиме */
	while (ASSR != ASSR_REG_REDY);
	/* чистим флаги прерываний */
	TIFR |= (1 << OCF2) | (1 << TOV2);
	/* включаю прерывание по переполнению таймера */
	TIMSK |= (1 << TOIE2);
}

/* настройка внешних прерываний */
void setup_ext_interrapt()
{
	GICR |= (1 << INT0) | (1 << INT1);
	MCUCR |= (1 << ISC11);
	DDRD = 0;
	PORTD |= (1 << INT0_PIN) | (1 << INT1_PIN) | (1 << MENU_BTN) | (1 << UP_BTN) | (1 << DOWN_BTN);
}

int main(void)
{
	ACSR |= (1 << ACD); // ОТКЛЮЧЕНИЕ АЦП
	start_timer2_async();
	setup_ext_interrapt();
	sei();
	
	TM1637_init();
	TM1637_turnOnAndSetBrightness(BRIGHTNES);
	print_time_on_display();
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	
	while(1)
	{
		activate_sleep_mode();
	}
}

