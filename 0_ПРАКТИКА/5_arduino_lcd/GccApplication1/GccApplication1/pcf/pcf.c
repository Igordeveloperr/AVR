#include "../main.h"

// ADDRESS PCF8574 - 0b01000000 ��� 0b01110000

void pcf_write(uint8_t byte){
	i2c_start();
	i2c_write(0x27);// ����� �� ������
	i2c_write(byte);
	i2c_stop();
}