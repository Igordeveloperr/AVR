#ifndef EEPROM_H_
#define EEPROM_H_
#define HOUR_ADDRESS 0x00
#define MIN_ADDRESS 0x01

void EEPROM_write(uint8_t address, uint8_t data);
uint8_t EEPROM_read(uint8_t address);

#endif