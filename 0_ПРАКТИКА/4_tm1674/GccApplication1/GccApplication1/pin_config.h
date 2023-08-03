/**
 *  TM1637 v0.0.1 (2020.02.16)
 *  https://github.com/TeWu/TM1637
 **/


#ifndef _TM1637_PIN_CONFIG_H_
#define _TM1637_PIN_CONFIG_H_ 1

#include <avr/io.h>


//
// ===! REMEMBER !===
// TM1637_CLK and TM1637_DIO pins must be pulled up to VCC by EXTERNAL pullup resistors.
// This library CAN NOT work without those pullup resistors!
// Developed and tested with 10k pullup resistors @ 3.3V VCC.
//


#define TM1637_DDR  DDRC
#define TM1637_PORT PORTC
#define TM1637_PIN  PINC
#define TM1637_DIO  PC4
#define TM1637_CLK  PC5


#endif /* _TM1637_PIN_CONFIG_H_ */