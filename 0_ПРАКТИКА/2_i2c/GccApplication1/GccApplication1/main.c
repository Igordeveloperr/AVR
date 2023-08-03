#include "main.h"

int hour = 18;
int minutes = 50;
double seconds = 0;
double interval = 0;

int get_hour()
{
	return hour;
}

int get_min()
{
	return minutes;
}

void control_time()
{
	if (seconds >= 60)
	{
		minutes++;
		seconds = 0;
	}
	if (minutes >= 60)
	{
		hour++;
		minutes = 0;
	}
	if (hour == 23 && minutes >= 60)
	{
		hour = 0;
		minutes = 0;
		seconds = 0;
	}
}

void activate_sleep_mode()
{
	if (interval >= 10)
	{	
		TM1637_turnOff();
		sleep_enable();
		sleep_cpu();
	}
}

ISR(TIMER1_OVF_vect)
{
	TCCR1B &= ~(1 << CS12);
	TCCR1B |= (1 << CS12);
	PORTB ^= (1 << PB1);
	seconds += 2.5;
	interval += 2.5;
	control_time();
}

ISR(INT0_vect)
{
	sleep_disable();
	control_time();
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


int main(void)
{
	ACSR |= (1 << ACD); // ÎÒÊËÞ×ÅÍÈÅ ÀÖÏ
	
	TIMSK |= (1 << TOIE1);
	TCCR1B |= (1 << CS12);
	
	//âíåøíèå ïðåðûâàíèÿ
	GICR |= (1 << INT0) | (1 << INT1);
	MCUCR = (1 << ISC11) | (1 << ISC01);
	DDRD = 0;
	PORTD |= (1 << PD2) | (1 << PD3) | (1 << MENU_BTN) | (1 << UP_BTN) | (1 << DOWN_BTN);
	
	// ïèí äëÿ äèîäà
	DDRB |= (1 << PB1);
	PORTB |= (1 << PB1);
	
	sei();
	
	TM1637_init();
	TM1637_turnOnAndSetBrightness(BRIGHTNES);
	print_time_on_display();
	set_sleep_mode(SLEEP_MODE_IDLE);
	
	while(1)
	{
		activate_sleep_mode();
	}
}

