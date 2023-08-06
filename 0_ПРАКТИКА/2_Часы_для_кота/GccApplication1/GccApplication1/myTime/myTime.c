#include "../main.h"

void control_seconds(uint8_t* seconds, uint8_t* minutes)
{
	if (*seconds >= SEC_OVF)
	{
		*minutes = *minutes + 1;
		*seconds = 0;
	}
}

void control_min(uint8_t* minutes, uint8_t* hour)
{
	if (*minutes >= MIN_OVF)
	{
		*hour = *hour + 1;
		*minutes = 0;
	}
}

void control_hour(uint8_t* seconds, uint8_t* minutes, uint8_t* hour)
{
	if (*hour == HOUR_OVF && *minutes >= 59 && *seconds >= 59)
	{
		*hour = 0;
		*minutes = 0;
		*seconds = 0;
	}
}