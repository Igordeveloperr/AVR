#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 1000000UL
#define MENU_BTN PD4
#define UP_BTN PD5
#define DOWN_BTN PD6
#define BRIGHTNES 1
#define DISP_LEN 4
#define START_POS 0
#define DIVIDER 10
#define ASSR_REG_REDY 8
#define INT0_PIN PD2
#define INT1_PIN PD3
#define SEC_OVF 60
#define MIN_OVF 60
#define HOUR_OVF 23

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "TM1637.h"
#include "control_tm1637.h"

uint8_t get_hour();
uint8_t get_min();
uint8_t get_sec();

#endif