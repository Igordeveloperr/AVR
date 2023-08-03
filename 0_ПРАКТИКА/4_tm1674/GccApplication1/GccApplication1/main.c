/**
 *  TM1637 v0.0.1 (2020.02.16)
 *  https://github.com/TeWu/TM1637
 **/


#include <util/delay.h>
#define F_CPU 8000000UL
#define BRIGHTNES 4
#include "dysplay_TM1637.h"


int main(void)// пример использования вышеописанных функций

{
	unsigned char one = 0, dec = 0, hun = 0, tau = 0;


	TM1637_init(1,5,4);//устанавливаем пины SCL и SDA
	TM1637_set(2,0,0xC0);// ставим яркость 2
	_delay_ms(2000);//не знаю зачем, но тупим немного
	while(1)
	{

		TM1637_display(3,one);
		TM1637_display(2,dec);
		TM1637_display(1,hun);
		TM1637_display(0,tau);
		TM1637_point(POINT_ON);
		_delay_ms(1000);

		++one;
		if(one > 9){++dec; one = 0;}
		if(dec > 5){++hun; dec = 0;}
		if(hun > 9){++tau; hun = 0;}
		if((tau ==2) && (hun > 3)){one = 0, dec = 0, hun = 0, tau = 0;}


		
		
		

	}
}
