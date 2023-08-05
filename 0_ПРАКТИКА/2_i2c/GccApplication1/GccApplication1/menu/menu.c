#include "../main.h" 

uint8_t hr = 0;
uint8_t min = 0;
uint8_t wait_time = 0;

void update_menu()
{
	TM1637_clear();
	_delay_ms(WAIT);
}

uint8_t set_time_up(uint8_t val, uint8_t max_val)
{
	uint8_t result;
	if (val < max_val)
	{
		result = val + 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

uint8_t set_time_down(uint8_t val, uint8_t max_val)
{
	uint8_t result;
	if (val > 0)
	{
		result = val - 1;
	}
	else
	{
		result = max_val;
	}	
	return result;
}

void tune_hour()
{
	if (!(PIND & (1 << UP_BTN)))
	{
		wait_time = 0;
		hr = set_time_up(hr, HOUR_OVF);
	}
			
	if (!(PIND & (1 << DOWN_BTN)))
	{
		wait_time = 0;
		hr = set_time_down(hr, HOUR_OVF);
	}
}

void tune_min()
{
	if (!(PIND & (1 << UP_BTN)))
	{
		wait_time = MAX_WAIT_TIME;
		min = set_time_up(min, MIN_OVF-1);
	}
			
	if (!(PIND & (1 << DOWN_BTN)))
	{
		wait_time = MAX_WAIT_TIME;
		min = set_time_down(min, MIN_OVF-1);
	}
}

void event_listener()
{
	update_menu();
	while(!(PIND & (1 << MENU_BTN)))
	{
		if (wait_time < MAX_WAIT_TIME)
		{
			tune_hour();
		}
		else
		{
			tune_min();
		}
		wait_time++;
		_delay_ms(WAIT);
		print_time_on_display(hr,min);
	}
	wait_time = 0;
	update_menu();
}

void setup_time(uint8_t* seconds, uint8_t* minutes, uint8_t* hour)
{
	*seconds = 0;
	*minutes = min;
	*hour = hr;
}
