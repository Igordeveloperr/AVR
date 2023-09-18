#ifndef LCD_H
#define LCD_H

#define LCD_PCF8574_INIT 1 //������������� pcf

#define LCD_PCF8574_DEVICEID 0 //id ���-��
#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_2LINES 

// ��������� ������ �����: ���������/���������� �������� �������, ����������� ����������� ������� ���������/�����������
#define LCD_ENTRY_DEC            0x04   // �������� ������� ���������, ������ ������������ �� �������
#define LCD_ENTRY_DEC_SHIFT      0x05   // ��������� ������ �������, ����������� ������� �� �������
#define LCD_ENTRY_INC_           0x06   // �������� ������� ���������, ���. ����������� ������� � �����������
#define LCD_ENTRY_INC_SHIFT      0x07   // ��������� �������� �������, ���������� ����������� ����������� �������

// ���������/���������� �������, ���������/���������� �������, �������� ������ � ������� �������
#define LCD_DISP_OFF             0x08   // ������� ��������
#define LCD_DISP_ON              0x0C   // ������� ���, ������ ����
#define LCD_DISP_ON_BLINK        0x0D   // ������� ���, ������ ����, ���� �������� �����
#define LCD_DISP_ON_CURSOR       0x0E   // ������� ���, ������ ���
#define LCD_DISP_ON_CURSOR_BLINK 0x0F   // ������� ���, ������ ���, ���� �������� �����

// ����������� �������/�������� �������
#define LCD_MOVE_CURSOR_LEFT     0x10   // ������ ������
#define LCD_MOVE_CURSOR_RIGHT    0x14   // ������ �������
#define LCD_MOVE_DISP_LEFT       0x18   // ����� �����
#define LCD_MOVE_DISP_RIGHT      0x1C   // ����� ������

// ����� �������: ��������� ����� ������ ���������� � ���������� ����� �����������
#define LCD_FUNCTION_4BIT_1LINE  0x20   // 4-������ ���������, ���� ������, 5x7 �����
#define LCD_FUNCTION_4BIT_2LINES 0x28   // 4-������ ���������, ������������, 5x7 �����
#define LCD_FUNCTION_8BIT_1LINE  0x30   // 8-������ ���������, ���� ������, 5x7 �����
#define LCD_FUNCTION_8BIT_2LINES 0x38   // 8-������ ���������, ������������, 5x7 �����

#define LCD_LINES           2	  // ���-�� �����
#define LCD_DISP_LENGTH    16     // ���-�� �������� � ������
#define LCD_LINE_LENGTH  0x40	  // ���������� ����� ������ �������
#define LCD_START_LINE1  0x00     // DDRM ����� ��� 1 ������
#define LCD_START_LINE2  0x40     // DDRM ����� ��� 2 ������
#define LCD_WRAP_LINES      1     // ������� ������



#define LCD_DATA0_PIN    4            // ��� ��� ������
#define LCD_DATA1_PIN    5            // ��� ��� ������
#define LCD_DATA2_PIN    6            // ��� ��� ������
#define LCD_DATA3_PIN    7            // ��� ��� ������
#define LCD_RS_PIN       0            // ��� ����� RS
#define LCD_RW_PIN       1            // ��� ����� RW
#define LCD_E_PIN        2            // ��� ����� ������������
#define LCD_LED_PIN      3            // ��� ���������


// ������� ����� �������� ������ HD44780U.
#define LCD_CLR               0      // ��������� �������
#define LCD_HOME              1      // ������� ������ �����
#define LCD_ENTRY_MODE        2      // ��������� ������ �����
#define LCD_ENTRY_INC         1      // ���������
#define LCD_ENTRY_SHIFT       0      // ��� ��������
#define LCD_ON                3      // ��� �������
#define LCD_ON_DISPLAY        2      // ���� �������
#define LCD_ON_CURSOR         1      // ���� ������
#define LCD_ON_BLINK          0      // ������� �������
#define LCD_MOVE              4      // ������������ �������
#define LCD_MOVE_DISP         3      // ������������ �������
#define LCD_MOVE_RIGHT        2      // ������������ ������� �������
#define LCD_FUNCTION          5      // ��������� �������
#define LCD_FUNCTION_8BIT     4      // 8 ������ �����
#define LCD_FUNCTION_2LINES   3      // ��������� �����
#define LCD_FUNCTION_10DOTS   2      // ������
#define LCD_CGRAM             6      // ��������� ������ CG RAM
#define LCD_DDRAM             7      // ��������� ������ DD RAM
#define LCD_BUSY              7      // ������� �����

// ����������� �����
#define LCD_MODE_DEFAULT     ((1<<LCD_ENTRY_MODE) | (1<<LCD_ENTRY_INC) )

// ������������� �������
void lcd_init(uint8_t dispAttr);

// ������� �������
void lcd_clrscr(void);

// ������ � ������ ���������
void lcd_home(void);

// ����������� ������� �� �����������
void lcd_gotoxy(uint8_t x, uint8_t y);

// ��� � ���� ���������
void lcd_led(uint8_t onoff);

// ����������� ������� � ������� ������� �������
void lcd_putc(char c);

// ����� ������ �� �������
void lcd_puts(const char *s);

// ����� ������ �� ������
void lcd_puts_p(const char *progmem_s);

// ��������� ������� ��� �������� ������ �������
void lcd_command(uint8_t cmd);

// �������� ����� �� �������
void lcd_data(uint8_t data);

// ������� ��� ��������������� ���������� ��������� ��������� � ������ ���������
#define lcd_puts_P(__s)         lcd_puts_p(PSTR(__s))

#endif
