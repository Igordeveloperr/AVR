#ifndef LCD_H
#define LCD_H

#define LCD_PCF8574_INIT 1 //инициализация pcf

#define LCD_PCF8574_DEVICEID 0 //id уст-ва
#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_2LINES 

// установка режима ввода: включение/выключение смещения дисплея, направление перемещения курсора уменьшать/увеличивать
#define LCD_ENTRY_DEC            0x04   // смещение дисплея выключено, курсор перемещается по наклону
#define LCD_ENTRY_DEC_SHIFT      0x05   // включение сдвига дисплея, перемещение курсора по наклону
#define LCD_ENTRY_INC_           0x06   // смещение дисплея выключено, вкл. перемещение курсора в направлении
#define LCD_ENTRY_INC_SHIFT      0x07   // включение смещения дисплея, увеличение направления перемещения курсора

// включение/выключение дисплея, включение/выключение курсора, мигающий символ в позиции курсора
#define LCD_DISP_OFF             0x08   // дисплей выключен
#define LCD_DISP_ON              0x0C   // дисплей вкл, курсор выкл
#define LCD_DISP_ON_BLINK        0x0D   // дисплей вкл, курсор выкл, есть мигающий симвл
#define LCD_DISP_ON_CURSOR       0x0E   // дисплей вкл, курсор вкл
#define LCD_DISP_ON_CURSOR_BLINK 0x0F   // дисплей вкл, курсор вкл, есть мигающий симвл

// перемещение курсора/смещение дисплея
#define LCD_MOVE_CURSOR_LEFT     0x10   // курсор налево
#define LCD_MOVE_CURSOR_RIGHT    0x14   // курсор направо
#define LCD_MOVE_DISP_LEFT       0x18   // сдвиг влево
#define LCD_MOVE_DISP_RIGHT      0x1C   // сдвиг вправо

// набор функций: установка длины данных интерфейса и количества строк отображения
#define LCD_FUNCTION_4BIT_1LINE  0x20   // 4-битный интерфейс, одна строка, 5x7 точек
#define LCD_FUNCTION_4BIT_2LINES 0x28   // 4-битный интерфейс, двухстрочный, 5x7 точек
#define LCD_FUNCTION_8BIT_1LINE  0x30   // 8-битный интерфейс, одна строка, 5x7 точек
#define LCD_FUNCTION_8BIT_2LINES 0x38   // 8-битный интерфейс, двухстрочный, 5x7 точек

#define LCD_LINES           2	  // кол-во строк
#define LCD_DISP_LENGTH    16     // кол-во символов в строке
#define LCD_LINE_LENGTH  0x40	  // внутренняя длина строки дисплея
#define LCD_START_LINE1  0x00     // DDRM адрес для 1 строки
#define LCD_START_LINE2  0x40     // DDRM адрес для 2 строки
#define LCD_WRAP_LINES      1     // перенос строки



#define LCD_DATA0_PIN    4            // пин для данных
#define LCD_DATA1_PIN    5            // пин для данных
#define LCD_DATA2_PIN    6            // пин для данных
#define LCD_DATA3_PIN    7            // пин для данных
#define LCD_RS_PIN       0            // пин линии RS
#define LCD_RW_PIN       1            // пин линии RW
#define LCD_E_PIN        2            // пин линии тактирования
#define LCD_LED_PIN      3            // пин подсветки


// Позиции битов регистра команд HD44780U.
#define LCD_CLR               0      // отчистить дисплей
#define LCD_HOME              1      // вернуть курсор домой
#define LCD_ENTRY_MODE        2      // установка режима ввода
#define LCD_ENTRY_INC         1      // инкремент
#define LCD_ENTRY_SHIFT       0      // вкл смещение
#define LCD_ON                3      // вкл курсора
#define LCD_ON_DISPLAY        2      // выкл дисплей
#define LCD_ON_CURSOR         1      // выкл курсор
#define LCD_ON_BLINK          0      // мигание курсора
#define LCD_MOVE              4      // передвижение курсора
#define LCD_MOVE_DISP         3      // передвижение курсора
#define LCD_MOVE_RIGHT        2      // передвижение курсора направо
#define LCD_FUNCTION          5      // настройка функций
#define LCD_FUNCTION_8BIT     4      // 8 битный режим
#define LCD_FUNCTION_2LINES   3      // активация строк
#define LCD_FUNCTION_10DOTS   2      // шрифты
#define LCD_CGRAM             6      // установка адреса CG RAM
#define LCD_DDRAM             7      // установка адреса DD RAM
#define LCD_BUSY              7      // дисплей занят

// стандартный режим
#define LCD_MODE_DEFAULT     ((1<<LCD_ENTRY_MODE) | (1<<LCD_ENTRY_INC) )

// инициализация дисплея
void lcd_init(uint8_t dispAttr);

// очистка дисплея
void lcd_clrscr(void);

// курсов в начало координат
void lcd_home(void);

// перемещение курсора по координатам
void lcd_gotoxy(uint8_t x, uint8_t y);

// вкл и откл подсветки
void lcd_led(uint8_t onoff);

// отображение символа в текущей позиции курсора
void lcd_putc(char c);

// вывод строки на дисплей
void lcd_puts(const char *s);

// вывод строки из памяти
void lcd_puts_p(const char *progmem_s);

// служебная функция для отправки команд дисплею
void lcd_command(uint8_t cmd);

// отправка байта на дисплей
void lcd_data(uint8_t data);

// макросы для автоматического сохранения строковой константы в памяти программы
#define lcd_puts_P(__s)         lcd_puts_p(PSTR(__s))

#endif
