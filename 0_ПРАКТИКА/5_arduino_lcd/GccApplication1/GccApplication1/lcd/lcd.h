#ifndef LCD_H_
#define LCD_H_


void lcd_ini(void); // инициализация
void lcd_str(char* str); // отправка строки на дисплей
void lcd_pos(uint8_t line, uint8_t pos); // установка позиции курсора
void lcd_num(uint8_t num, uint8_t line, uint8_t pos); // вывод числа на дисплей
void lcd_animation(void);


#endif