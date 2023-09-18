#ifndef PCF8574_H_
#define PCF8574_H_

#define PCF8574_ADDRBASE (0x27) // адрес уст-ва

#define PCF8574_I2CINIT 1 // инициализация i2c

#define PCF8574_MAXDEVICES 1 // макс кол-во утройств
#define PCF8574_MAXPINS 8 // макс кол-во пинов

#define PCF8574_I2CFLEURYPATH "../i2c/i2cmaster.h" // подкл i2c

volatile uint8_t pcf8574_pinstatus[PCF8574_MAXDEVICES];

void pcf8574_init();
extern int8_t pcf8574_getoutput(uint8_t deviceid);
extern int8_t pcf8574_getoutputpin(uint8_t deviceid, uint8_t pin);
extern int8_t pcf8574_setoutput(uint8_t deviceid, uint8_t data);
extern int8_t pcf8574_setoutputpins(uint8_t deviceid, uint8_t pinstart, uint8_t pinlength, int8_t data);
extern int8_t pcf8574_setoutputpin(uint8_t deviceid, uint8_t pin, uint8_t data);
extern int8_t pcf8574_setoutputpinhigh(uint8_t deviceid, uint8_t pin);
extern int8_t pcf8574_setoutputpinlow(uint8_t deviceid, uint8_t pin);
extern int8_t pcf8574_getinput(uint8_t deviceid);
extern int8_t pcf8574_getinputpin(uint8_t deviceid, uint8_t pin);
#endif
