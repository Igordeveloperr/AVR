#ifndef DS3231_H_
#define DS3231_H_

#define DS3231_I2C_SLAVE_ADDRESS      0xD0

#define RTC_REG_SECOND                0x00
#define RTC_REG_MINUTE                0x01
#define RTC_REG_HOUR                  0x02
#define RTC_REG_DAY                   0x03
#define RTC_REG_DATE                  0x04
#define RTC_REG_MONTH                 0x05
#define RTC_REG_YEAR                  0x06
#define RTC_REG_CONTROL               0x0E
#define RTC_REG_STATUS                0x0F
#define RTC_REG_TEMPERATURE_MSB       0x11
#define RTC_REG_TEMPERATURE_LSB       0x12

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_write_byte(uint8_t data);
uint8_t i2c_read_byte(uint8_t *data, uint8_t ack);
uint8_t DS1307Read(uint8_t address, uint8_t *data);
uint8_t DS1307Write(uint8_t address, uint8_t data);

#endif /* DS3231_H_ */
