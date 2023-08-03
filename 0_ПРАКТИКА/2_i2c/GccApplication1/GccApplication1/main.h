#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#define MENU_BTN PD4
#define UP_BTN PD5
#define DOWN_BTN PD6
#define BRIGHTNES 1
#define DISP_LEN 4
#define START_POS 0
#define DIVIDER 10

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "TM1637.h"
#include "control_tm1637.h"

int get_hour();
int get_min();

#endif