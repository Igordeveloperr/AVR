

#ifndef _DYSPLAY_TM1637_H_
#define _DYSPLAY_TM1637_H_




#define CLK 5 //обзываем пины
#define DIO 4

#define DispPort PORTC // обзываем порт
#define DDR DDRC




	//************definitions for TM1637*********************
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44
	
#define STARTADDR  0xc0 
	/**** definitions for the clock point of the 4-Digit Display *******/
#define POINT_ON   1
#define POINT_OFF  0
	/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7
//--------------------------------------------------------//
//Special characters index of tube table
#define INDEX_NEGATIVE_SIGN	16
#define INDEX_BLANK			17
/************def
ions for type of the 4-Digit Display*********************/
#define D4036B 0
#define D4056A 1
		
		uint8_t Cmd_SetData;
		uint8_t Cmd_SetAddr;
		uint8_t Cmd_DispCtrl;
		uint8_t _PointFlag; 	//_PointFlag=1:the clock point on
		uint8_t _DispType;
		//int8_t coding(int8_t DispData);
		uint8_t Clkpin;
		uint8_t Datapin;
		uint8_t DecPoint;
		uint8_t BlankingFlag;
		uint8_t anim1[16][4] = {{73,0,0,0},
								{73,73,0,0},
								{73,73,73,0},
								{73,73,73,73},
								{0,73,73,73},
								{0,0,73,73},
								{0,0,0,73},
								{0,0,0,0},
								{54,0,0,0},
								{54,54,0,0},
								{54,54,54,0},
								{54,54,54,54},
								{0,54,54,54},
								{0,0,54,54},
								{0,0,0,54},
								{0,0,0,0}};
		uint8_t anim2[11][4] = {
		{64,64,64,64},
		{0,64,64,70},
		{0,0,64,79},
		{0,0,9,79},
		{0,9,9,79},
		{9,9,9,9},
		{57,9,9,9},
		{121,9,9,0},
		{121,73,0,0},
		{121,64,0,0},
		{112,64,64,0}};
static uint8_t TubeTab[] = {0x3f,0x06,0x5b,0x4f,// знакогенератор
                           0x66,0x6d,0x7d,0x07,
                           0x7f,0x6f,0x77,0x7c,
                           0x39,0x5e,0x79,0x71,
                           0x40,0x00};//0~9,A,b,C,d,E,F,"-"," "  



void TM1637_writeByte(int8_t wr_data)// служебна€ функци€ записи данных по протоколу I2C, с подтверждением (ACK)
{
  uint8_t i;
    for(i=0;i<8;i++)        
  {
   DispPort &= ~(1<<Clkpin);
    if(wr_data & 0x01)
	{ DispPort |= 1<<Datapin;}
    else {DispPort &= ~(1<<Datapin);}
	_delay_us(3);
    wr_data = wr_data>>1;      
    DispPort |= 1<<Clkpin;
	_delay_us(3);  
  }  
 
  DispPort &= ~(1<<Clkpin);
  _delay_us(5);
  DDR &= ~(1<<Datapin);// если помен€ете порт на какой-то другой кроме PORTC, то тут тоже все DDRC на другие DDRx мен€ть надо будет
  while((PINC & (1<<Datapin))); 
  DDR |= (1<<Datapin);
  DispPort |= 1<<Clkpin;
  _delay_us(2);
  DispPort &= ~(1<<Clkpin);  
}

void TM1637_start(void) // просто функци€ "старт" дл€ протокола I2C
{
   DispPort |= 1<<Clkpin; 
   DispPort |= 1<<Datapin;
 _delay_us(2);
  DispPort &= ~(1<<Datapin); 
} 

void TM1637_stop(void) // просто функци€ "стоп" дл€ протокола I2C
{
  DispPort &= ~(1<<Clkpin);
 _delay_us(2);
  DispPort &= ~(1<<Datapin);
_delay_us(2);
  DispPort |= 1<<Clkpin;;
_delay_us(2);
  DispPort |= 1<<Datapin;
}

void TM1637_coding_all(uint8_t DispData[])//шифратор 
{
	uint8_t PointData;
	if(_PointFlag == POINT_ON)PointData = 0x80;
	else PointData = 0;
	for(uint8_t i = 0;i < 4;i ++)
	{
		if(DispData[i] == 0x7f)DispData[i] = 0x00;
		else DispData[i] = TubeTab[DispData[i]];// + PointData; // закоментированно, так как у моего диспле€ нет дес€тичных точек
	//DispData[i] += 0x80;
	}
	if((_DispType == D4056A)&&(DecPoint != 3))
	{
	DispData[DecPoint] += 0x80;
	DecPoint = 3;
	}
}
int8_t TM1637_coding(uint8_t DispData)// шифратор всех знакомест
{
	uint8_t PointData;
	if(_PointFlag == POINT_ON)PointData = 0x80;
	else PointData = 0;
	if(DispData == 0x7f) DispData = 0x00 + PointData;
	else DispData = TubeTab[DispData] + PointData;
	return DispData;
}

void TM1637_display_all(uint8_t DispData[]) // полезн€шка! отображает содержимое массива пр€мо на экране. 
											//не забываем, что можем отображать только числа от 0x00 до 0x0F или по-русски от 0 до 15
{
  uint8_t SegData[4];
  uint8_t i;
  for(i = 0;i < 4;i ++)
  {
    SegData[i] = DispData[i];
  }
  TM1637_coding_all(SegData);
  TM1637_start();
  TM1637_writeByte(ADDR_AUTO);
  TM1637_stop();
  TM1637_start();
  TM1637_writeByte(Cmd_SetAddr);
  for(i=0;i < 4;i ++)
  {
    TM1637_writeByte(SegData[i]);
  }
  TM1637_stop();
  TM1637_start();
  TM1637_writeByte(Cmd_DispCtrl);
  TM1637_stop();
}

void TM1637_display_all_direct(uint8_t DispData[]) // управл€ет каждым сегментом по отдельности. по байту на знакоместо
{
	uint8_t SegData[4];
	uint8_t i;
	for(i = 0;i < 4;i ++)
	{
		SegData[i] = DispData[i];
	}
	//TM1637_coding_all(SegData);
	TM1637_start();
	TM1637_writeByte(ADDR_AUTO);
	TM1637_stop();
	TM1637_start();
	TM1637_writeByte(Cmd_SetAddr);
	for(i=0;i < 4;i ++)
	{
		TM1637_writeByte(SegData[i]);
	}
	TM1637_stop();
	TM1637_start();
	TM1637_writeByte(Cmd_DispCtrl);
	TM1637_stop();
}
void TM1637_display(uint8_t BitAddr,int8_t DispData)// отображает один символ (от 0 до 15)в определенном месте  (от 0 до 3)
{
  int8_t SegData;
  SegData = TM1637_coding(DispData);
  TM1637_start();
  TM1637_writeByte(ADDR_FIXED);
  TM1637_stop();
  TM1637_start();
  TM1637_writeByte(BitAddr|0xc0);
  TM1637_writeByte(SegData);
  TM1637_stop();
  TM1637_start();
  TM1637_writeByte(Cmd_DispCtrl);
  TM1637_stop();
}
void TM1637_display_int_decimal(int16_t Decimal)// функци€ с минимальными изменени€ми скопированна€ с ардуиновской библиотеки. выводит целые числа от -999 до 9999
{
	uint8_t temp[4];
	if((Decimal > 9999)||(Decimal < -999))return;
	if(Decimal < 0)
	{
		temp[0] = INDEX_NEGATIVE_SIGN;
		Decimal = (Decimal & 0x7fff);
		temp[1] = Decimal/100;
		Decimal %= 100;
		temp[2] = Decimal / 10;
		temp[3] = Decimal % 10;
		if(BlankingFlag)
		{
			if(temp[1] == 0)
			{
				temp[1] = INDEX_BLANK;
				if(temp[2] == 0) temp[2] = INDEX_BLANK;
			}
		}
	}
	else
	{
		temp[0] = Decimal/1000;
		Decimal %= 1000;
		temp[1] = Decimal/100;
		Decimal %= 100;
		temp[2] = Decimal / 10;
		temp[3] = Decimal % 10;
		if(BlankingFlag)
		{
			if(temp[0] == 0)
			{
				temp[0] = INDEX_BLANK;
				if(temp[1] == 0)
				{
					temp[1] = INDEX_BLANK;
					if(temp[2] == 0) temp[2] = INDEX_BLANK;
				}
			}
		}
	}
	BlankingFlag = 1;
	TM1637_display_all(temp);
} 

void TM1637_display_float_decimal(double Decimal) // функци€ с минимальными изменени€ми скопированна€ с ардуиновской библиотеки. 
{												// выводит числа с дес€тичной точкой от -999 до 9999
  int16_t temp;
  if(Decimal > 9999)return;
  else if(Decimal < -999)return;
  uint8_t i = 3;
  if(Decimal > 0)
  {
	for( ;i > 0; i --)
	{
	  if(Decimal < 1000)Decimal *= 10;
	  else break;
	}
	temp = (int)Decimal;
	if((Decimal - temp)>0.5)temp++;
  }
   else
  {
	for( ;i > 1; i --)
	{
	  if(Decimal > -100)Decimal *= 10;
	  else break;
	}
	temp = (int)Decimal;
	if((temp - Decimal)>0.5)temp--;
  }
  DecPoint = i;
  BlankingFlag = 0;
  TM1637_display_int_decimal(temp);
}

void TM1637_clearDisplay(void) // чистит дисплей
{
  TM1637_display(0x00,0x7f);
  TM1637_display(0x01,0x7f);
  TM1637_display(0x02,0x7f);
  TM1637_display(0x03,0x7f);  
}
void TM1637_in(uint8_t DispType,uint8_t Clk, uint8_t Data)// инициализирует переменные, назначает порт и пины дл€ св€зи с дисплеем, а потом чистит дисплей
{
	Clkpin = Clk;
	Datapin = Data;
	DDR |= (1<<Clkpin) | (1<<Datapin);
	_DispType = DispType;
	BlankingFlag = 1;
	DecPoint = 3;
	TM1637_clearDisplay();
}
void TM1637_set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr)// по большому счету только дл€ установки €ркости нужна
{
  Cmd_SetData = SetData;
  Cmd_SetAddr = SetAddr;
  Cmd_DispCtrl = 0x88 + brightness;
}
void TM1637_point(uint8_t PointFlag)//не знаю зачем скопировал, пусть будет
{
	_PointFlag = PointFlag;
}







#endif


