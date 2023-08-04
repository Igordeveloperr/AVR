#include "main.h" 

uint8_t hr = 0;
uint8_t min = 0;
uint8_t wait_time = 0;

void event_listener()
{
	TM1637_clear();
	_delay_ms(1000);
	while(!(PIND & (1 << MENU_BTN)))
	{
		if (wait_time < 6)
		{
			if (!(PIND & (1 << UP_BTN)))
			{
				wait_time = 0;
				hr++;
			}
			
			if (!(PIND & (1 << DOWN_BTN)))
			{
				wait_time = 0;
				hr--;
			}
		}
		else
		{
			if (!(PIND & (1 << UP_BTN)))
			{
				wait_time = 6;
				min++;
			}
			
			if (!(PIND & (1 << DOWN_BTN)))
			{
				wait_time = 6;
				min--;
			}
		}
		wait_time++;
		_delay_ms(500);
		print_time_on_display(hr,min);
	}
}

void setup_time(uint8_t* seconds, uint8_t* minutes, uint8_t* hour)
{
	*seconds = 0;
	*minutes = min;
	*hour = hr;
}

void close_menu()
{
	
}