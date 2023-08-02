#include "main.h"

short active_menu = 0;
short menuItem = 0;

void select_menu_item()
{
	if (menuItem == 0)
	{
	}
	if (menuItem == 1)
	{
		active_menu = 0;
		menuItem = 0;
		lcd_clrscr();
		lcd_home();
		lcd_puts(get_lcd_data());
	}
}

void event_listener()
{
	if ((!(PIND & (1 << MENU_BTN))) && (active_menu == 0))
	{
		active_menu = 1;
	}
	if ((!(PIND & (1 << UP_BTN))) && active_menu)
	{
		cursor_up();
	}
	if ((!(PIND & (1 << DOWN_BTN))) && active_menu)
	{
		cursor_down();
	}
	if ((!(PIND & (1 << MENU_BTN))) && active_menu)
	{
		select_menu_item();
	}
	print_menu();
}

void cursor_up()
{
	if (menuItem > 0)
	{
		menuItem--;
	}
	else
	{
		menuItem = 1;
	}
}

void cursor_down()
{
	if (menuItem < 1)
	{
		menuItem++;
	}
	else
	{
		menuItem = 0;
	}
}

void print_menu()
{
	char* line1, line2 = "";
	if (menuItem == (short)0)
	{
		line1 = "->Set Time";
	}
	else
	{
		line1 = "Set Time";
	}
	if (menuItem == (short)1)
	{
		line2 = "->Exit";
	}
	else
	{
		line2 = "Exit";
	}
	if (active_menu)
	{
		lcd_puts(line1);
		lcd_gotoxy(0,1);
		lcd_puts(line2);
	}
}