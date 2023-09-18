#include "../main.h"

// задержеки через асемблер
#define lcd_e_delay()   __asm__ __volatile__( "rjmp 1f\n 1:" );
#define lcd_e_toggle()  toggle_e()


volatile uint8_t dataport = 0;

static void toggle_e(void);

// сама реализация задержек
static inline void _delayFourCycles(unsigned int __count)
{
    if ( __count == 0 )    
        __asm__ __volatile__( "rjmp 1f\n 1:" );    
    else
        __asm__ __volatile__ (
    	    "1: sbiw %0,1" "\n\t"                  
    	    "brne 1b"                              
    	    : "=w" (__count)
    	    : "0" (__count)
    	   );
}

// тупа оборачиваем функцию в макрос
#define delay(us)  _delayFourCycles( ( ( 1*(F_CPU/4000) )*us)/1000 )

// переключение пина для начала записи команды
static void toggle_e(void)
{
	pcf8574_setoutputpinhigh(LCD_PCF8574_DEVICEID, LCD_E_PIN);
    lcd_e_delay();
    pcf8574_setoutputpinlow(LCD_PCF8574_DEVICEID, LCD_E_PIN);
}


// отправка байта для контроллера LCD
static void lcd_write(uint8_t data,uint8_t rs) 
{
	if (rs) //отправка данных (RS=1, RW=0)
		dataport |= _BV(LCD_RS_PIN);
	else // отпрака инструкций(RS=0, RW=0)
		dataport &= ~_BV(LCD_RS_PIN);
	dataport &= ~_BV(LCD_RW_PIN);
	pcf8574_setoutput(LCD_PCF8574_DEVICEID, dataport);

	// отправка старшего полубайта
    dataport &= ~_BV(LCD_DATA3_PIN);
    dataport &= ~_BV(LCD_DATA2_PIN);
    dataport &= ~_BV(LCD_DATA1_PIN);
    dataport &= ~_BV(LCD_DATA0_PIN);
	if(data & 0x80) dataport |= _BV(LCD_DATA3_PIN);
	if(data & 0x40) dataport |= _BV(LCD_DATA2_PIN);
	if(data & 0x20) dataport |= _BV(LCD_DATA1_PIN);
	if(data & 0x10) dataport |= _BV(LCD_DATA0_PIN);
	pcf8574_setoutput(LCD_PCF8574_DEVICEID, dataport);
	lcd_e_toggle();

	// отправка младшего полубайта
	dataport &= ~_BV(LCD_DATA3_PIN);
	dataport &= ~_BV(LCD_DATA2_PIN);
	dataport &= ~_BV(LCD_DATA1_PIN);
	dataport &= ~_BV(LCD_DATA0_PIN);
	if(data & 0x08) dataport |= _BV(LCD_DATA3_PIN);
	if(data & 0x04) dataport |= _BV(LCD_DATA2_PIN);
	if(data & 0x02) dataport |= _BV(LCD_DATA1_PIN);
	if(data & 0x01) dataport |= _BV(LCD_DATA0_PIN);
	pcf8574_setoutput(LCD_PCF8574_DEVICEID, dataport);
	lcd_e_toggle();

	// завершаем передачу
	dataport |= _BV(LCD_DATA0_PIN);
	dataport |= _BV(LCD_DATA1_PIN);
	dataport |= _BV(LCD_DATA2_PIN);
	dataport |= _BV(LCD_DATA3_PIN);
	pcf8574_setoutput(LCD_PCF8574_DEVICEID, dataport);
}

// чтение байта
static uint8_t lcd_read(uint8_t rs) 
{
    uint8_t data;

    if (rs) // запись данных (RS=1, RW=0) 
    	dataport |= _BV(LCD_RS_PIN);
    else // запись инструкций (RS=0, RW=0)
    	dataport &= ~_BV(LCD_RS_PIN);
    dataport |= _BV(LCD_RW_PIN);
    pcf8574_setoutput(LCD_PCF8574_DEVICEID, dataport);

    pcf8574_setoutputpinhigh(LCD_PCF8574_DEVICEID, LCD_E_PIN);
	lcd_e_delay();
	// чтение страшего полубайта
	data = pcf8574_getoutputpin(LCD_PCF8574_DEVICEID, LCD_DATA0_PIN) << 4;   
	pcf8574_setoutputpinlow(LCD_PCF8574_DEVICEID, LCD_E_PIN);

	lcd_e_delay();                  

	pcf8574_setoutputpinhigh(LCD_PCF8574_DEVICEID, LCD_E_PIN);
	lcd_e_delay();
	// чтение младшего полубайта
	data |= pcf8574_getoutputpin(LCD_PCF8574_DEVICEID, LCD_DATA0_PIN) &0x0F; 
	pcf8574_setoutputpinlow(LCD_PCF8574_DEVICEID, LCD_E_PIN);

    return data;
}

// ждем пока ЖК освободится
static uint8_t lcd_waitbusy(void)

{
    register uint8_t c;
    
    // ждем
    while ( (c=lcd_read(0)) & (1<<LCD_BUSY)) {}
    // задержка
    delay(2);
	// получаем адрес
    return (lcd_read(0)); 
}


// перемещение курсора по строкам
static inline void lcd_newline(uint8_t pos)
{
    register uint8_t addressCounter;


#if LCD_LINES==1
    addressCounter = 0;
#endif
#if LCD_LINES==2
    if ( pos < (LCD_START_LINE2) )
        addressCounter = LCD_START_LINE2;
    else
        addressCounter = LCD_START_LINE1;
#endif
#if LCD_LINES==4
    if ( pos < LCD_START_LINE3 )
        addressCounter = LCD_START_LINE2;
    else if ( (pos >= LCD_START_LINE2) && (pos < LCD_START_LINE4) )
        addressCounter = LCD_START_LINE3;
    else if ( (pos >= LCD_START_LINE3) && (pos < LCD_START_LINE2) )
        addressCounter = LCD_START_LINE4;
    else 
        addressCounter = LCD_START_LINE1;
#endif
    lcd_command((1<<LCD_DDRAM)+addressCounter);
}

// служебная функция для отправки команд дисплею
void lcd_command(uint8_t cmd)
{
    lcd_waitbusy();
    lcd_write(cmd,0);
}

// отправка байта на дисплей
void lcd_data(uint8_t data)
{
    lcd_waitbusy();
    lcd_write(data,1);
}

// перемещение курсора по координатам
void lcd_gotoxy(uint8_t x, uint8_t y)
{
#if LCD_LINES==1
    lcd_command((1<<LCD_DDRAM)+LCD_START_LINE1+x);
#endif
#if LCD_LINES==2
    if ( y==0 ) 
        lcd_command((1<<LCD_DDRAM)+LCD_START_LINE1+x);
    else
        lcd_command((1<<LCD_DDRAM)+LCD_START_LINE2+x);
#endif
#if LCD_LINES==4
    if ( y==0 )
        lcd_command((1<<LCD_DDRAM)+LCD_START_LINE1+x);
    else if ( y==1)
        lcd_command((1<<LCD_DDRAM)+LCD_START_LINE2+x);
    else if ( y==2)
        lcd_command((1<<LCD_DDRAM)+LCD_START_LINE3+x);
    else
        lcd_command((1<<LCD_DDRAM)+LCD_START_LINE4+x);
#endif
}

// тырим координаты
int lcd_getxy(void)
{
    return lcd_waitbusy();
}

// очистка дисплея
void lcd_clrscr(void)
{
    lcd_command(1<<LCD_CLR);
}

// вкл и откл подсветки
void lcd_led(uint8_t onoff)
{
	if(onoff)
		dataport &= ~_BV(LCD_LED_PIN);
	else
		dataport |= _BV(LCD_LED_PIN);
	pcf8574_setoutput(LCD_PCF8574_DEVICEID, dataport);
}

// курсов в начало координат
void lcd_home(void)
{
    lcd_command(1<<LCD_HOME);
}

// отображение символа в текущей позиции курсора
void lcd_putc(char c)
{
    uint8_t pos;

    pos = lcd_waitbusy();
    if (c=='\n')
    {
        lcd_newline(pos);
    }
    else
    {
#if LCD_WRAP_LINES==1
#if LCD_LINES==1
        if ( pos == LCD_START_LINE1+LCD_DISP_LENGTH ) {
            lcd_write((1<<LCD_DDRAM)+LCD_START_LINE1,0);
        }
#elif LCD_LINES==2
        if ( pos == LCD_START_LINE1+LCD_DISP_LENGTH ) {
            lcd_write((1<<LCD_DDRAM)+LCD_START_LINE2,0);    
        }else if ( pos == LCD_START_LINE2+LCD_DISP_LENGTH ){
            lcd_write((1<<LCD_DDRAM)+LCD_START_LINE1,0);
        }
#elif LCD_LINES==4
        if ( pos == LCD_START_LINE1+LCD_DISP_LENGTH ) {
            lcd_write((1<<LCD_DDRAM)+LCD_START_LINE2,0);    
        }else if ( pos == LCD_START_LINE2+LCD_DISP_LENGTH ) {
            lcd_write((1<<LCD_DDRAM)+LCD_START_LINE3,0);
        }else if ( pos == LCD_START_LINE3+LCD_DISP_LENGTH ) {
            lcd_write((1<<LCD_DDRAM)+LCD_START_LINE4,0);
        }else if ( pos == LCD_START_LINE4+LCD_DISP_LENGTH ) {
            lcd_write((1<<LCD_DDRAM)+LCD_START_LINE1,0);
        }
#endif
        lcd_waitbusy();
#endif
        lcd_write(c, 1);
    }
}

// вывод строки на дисплей
void lcd_puts(const char *s)
{
    register char c;

    while ( (c = *s++) ) {
        lcd_putc(c);
    }
}

// вывод строки из памяти
void lcd_puts_p(const char *progmem_s)
{
    register char c;

    while ( (c = pgm_read_byte(progmem_s++)) ) {
        lcd_putc(c);
    }
}

// инициализация дисплея
void lcd_init(uint8_t dispAttr)
{
	#if LCD_PCF8574_INIT == 1
	//инициализация pcf
	pcf8574_init();
	#endif

	dataport = 0;
	pcf8574_setoutput(LCD_PCF8574_DEVICEID, dataport);

    delay(16000);

    // первоначальная запись на ЖК-дисплей — 8 бит
    dataport |= _BV(LCD_DATA1_PIN);  // _BV(LCD_FUNCTION)>>4;
    dataport |= _BV(LCD_DATA0_PIN);  // _BV(LCD_FUNCTION_8BIT)>>4;
    pcf8574_setoutput(LCD_PCF8574_DEVICEID, dataport);

	// дрючим дисплей чтобы он начал работать
    lcd_e_toggle();
    delay(4992);
    lcd_e_toggle();      
    delay(64);        
    lcd_e_toggle();      
    delay(64);          

    // переходим в 4 битный режим
    dataport &= ~_BV(LCD_DATA0_PIN);
    pcf8574_setoutput(LCD_PCF8574_DEVICEID, dataport);
    lcd_e_toggle();
    delay(64); 
    

    lcd_command(LCD_FUNCTION_DEFAULT);      // настраиваем кол-во строк
    lcd_command(LCD_DISP_OFF);              // вырубаем дисплей
    lcd_clrscr();                           // чистим экран
    lcd_command(LCD_MODE_DEFAULT);          // запускаемся в стандартном режиме
    lcd_command(dispAttr);                  // отправляем настройки
}
