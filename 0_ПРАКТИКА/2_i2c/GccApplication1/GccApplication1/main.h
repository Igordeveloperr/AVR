#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 1000000UL
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
#define STEP 1
#define MAX_INTERVAL 10

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "./tm1637/TM1637.h"
#include "./control_tm1637/control_tm1637.h"
#include "./myTime/myTime.h"
#include "./menu/menu.h"
#include "./EEPROM/eeprom.h"

#endif