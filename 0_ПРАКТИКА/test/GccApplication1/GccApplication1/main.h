#ifndef MAIN_H_
#define MAIN_H_
// стандартная частота работы МК
#define F_CPU 16000000UL

// подключаем все либы
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <compat/twi.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcdpcf8574/lcdpcf8574.h"
#include "pcf8574/pcf8574.h"
#include "i2c/i2cmaster.h"

#endif 