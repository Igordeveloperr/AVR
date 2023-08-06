#include "main.h"

uint8_t hour = 23;
uint8_t minutes = 59;
uint8_t seconds = 0;

uint8_t cat_hour = 0;
uint8_t cat_minutes = 0;

uint8_t interval = 0;

/* ���������� ������� ������ */
void activate_sleep_mode()
{
	if (interval >= MAX_INTERVAL)
	{	
		TM1637_turnOff();
		OCR2 = 1;
		/* ��� ����� ������ */
		while (ASSR != ASSR_REG_REDY);
		sleep_enable();
		sleep_cpu();
	}
}

/* ������ ������� */
ISR(TIMER2_OVF_vect)
{
	TCNT2 = 0;
	PORTB ^= (1 << PB1);
	seconds += STEP;
	interval += STEP;
	control_seconds(&seconds, &minutes);
	control_min(&minutes, &hour);
	control_hour(&seconds, &minutes, &hour);
}

/* ����� �� ��� + ����� ����� ��� �� */
ISR(INT0_vect)
{
	sleep_disable();
	cat_hour = hour;
	cat_minutes = minutes;
	EEPROM_write(HOUR_ADDRESS, cat_hour);
	EEPROM_write(MIN_ADDRESS, cat_minutes);
	wakeup_display();
	print_time_on_display(cat_hour, cat_minutes);
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

/* ��������� Timer/Counter2 */
void start_timer2_async()
{
	ASSR |= (1 << AS2); // ���� ����������� �����
	/* ���� �������� ������� �� ������ */
	TCCR2 = 0;
	OCR2 = 0;
	TCNT2 = 0;
	/* �������� ������� = 128 */
	TCCR2 |= (1 << CS22) | (1 << CS20);
	/* ��� ����� ������ ��� ������ � ����������� ������ */
	while (ASSR != ASSR_REG_REDY);
	/* ������ ����� ���������� */
	TIFR |= (1 << OCF2) | (1 << TOV2);
	/* ������� ���������� �� ������������ ������� */
	TIMSK |= (1 << TOIE2);
}

/* ��������� ������� ���������� */
void setup_ext_interrapt()
{
	GICR |= (1 << INT0) | (1 << INT1);
	DDRD = 0;
	PORTD |= (1 << INT0_PIN) | (1 << INT1_PIN) | (1 << MENU_BTN) | (1 << UP_BTN) | (1 << DOWN_BTN) | (1 << VIEW_BTN);
}

int main(void)
{
	ACSR |= (1 << ACD); // ���������� ���
	start_timer2_async();
	setup_ext_interrapt();
	sei();
	
	cat_hour = EEPROM_read(HOUR_ADDRESS);
	cat_minutes = EEPROM_read(MIN_ADDRESS);
	
	TM1637_init();
	TM1637_turnOnAndSetBrightness(BRIGHTNES);
	print_time_on_display(hour, minutes);
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	
	DDRB |= (1 << PB1);
	PORTB &= ~(1 << PB1);
	
	while(1)
	{
		activate_sleep_mode();
	}
}

