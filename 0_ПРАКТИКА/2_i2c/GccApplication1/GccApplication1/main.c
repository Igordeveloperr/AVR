#include "main.h"

int hour = 11;
int minutes = 9;
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
	if (seconds >= 58.8)
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
	}
}

ISR(TIMER1_OVF_vect)
{
	TCCR1B &= ~(1 << CS12);
	TCCR1B |= (1 << CS12);
	PORTB ^= (1 << PB1);
	seconds += 2.1;
	interval += 2.1;
	activate_sleep_mode();
	control_time();
}

ISR(INT0_vect)
{
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
	TIMSK |= (1 << TOIE1);
	sei();
	TCCR1B |= (1 << CS12);
	
	//внешние прерывания
	MCUCR = (1 << ISC11) | (1 << ISC01);
	GICR |= (1 << INT0) | (1 << INT1);
	DDRD = 0;
	PORTD |= (1 << PD2) | (1 << PD3) | (1 << MENU_BTN) | (1 << UP_BTN) | (1 << DOWN_BTN);
	
	// пин для диода
	DDRB |= (1 << PB1);
	PORTB |= (1 << PB1);
	
	TM1637_init();
	TM1637_turnOnAndSetBrightness(BRIGHTNES);
	print_time_on_display();
	while(1)
	{
	}
}

