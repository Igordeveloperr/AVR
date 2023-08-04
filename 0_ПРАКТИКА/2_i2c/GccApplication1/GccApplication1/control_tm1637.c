#include "main.h"

uint8_t display_digit[] =
{
	0b10111111,
	0b10000110,
	0b11011011,
	0b11001111,
	0b11100110,
	0b11101101,
	0b11111101,
	0b10000111,
	0b11111111,
	0b11101111
};

uint8_t select_display_digit(uint8_t digit)
{
	if (digit >= 0 && digit < 10)
	{
		return display_digit[digit];
	}
	else
	{
		return TM1637_SPAT_BLANK;
	}
}

void wakeup_display()
{
	TM1637_turnOnAndSetBrightness(BRIGHTNES);
}

void print_time_on_display(uint8_t hour, uint8_t min)
{
	uint8_t d_time[DISP_LEN];
	d_time[0] = hour / DIVIDER;
	d_time[1] = hour % DIVIDER;
	d_time[2] = min / DIVIDER;
	d_time[3] = min % DIVIDER;
	
	uint8_t out_time[TM1637_DIGITS_COUNT];
	for(uint8_t i = 0; i < TM1637_DIGITS_COUNT; i++)
	{
		out_time[i] = select_display_digit(d_time[i]);
	}
	TM1637_setSegments(out_time, TM1637_DIGITS_COUNT, START_POS);
}