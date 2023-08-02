#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#define MENU_BTN PD4
#define UP_BTN PD5
#define DOWN_BTN PD6

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "pcf.h"
#include "lcd.h"
#include "lcd_pcf.h"
#include "menu.h"

char get_lcd_data();

#endif