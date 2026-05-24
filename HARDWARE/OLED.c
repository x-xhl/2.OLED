#include "stm32f10x.h"
#include "iic.h"
#include "Delay.h"
#include "OLED_Data.h"

void OLED_WriteCommand(unsigned char Command)
{
	iic_start();
	iic_write_byte(0x78);				//寻址
	iic_receive_ark();
	iic_write_byte(0x00);				//非连续模式，写命令
	iic_receive_ark();
	iic_write_byte(Command);		//命令
	iic_receive_ark();
  iic_stop();
}

void OLED_WriteData(unsigned char Data)
{
	iic_start();
	iic_write_byte(0x78);				//寻址
	iic_receive_ark();
	iic_write_byte(0x40);				//非连续模式，写数据
	iic_receive_ark();
	iic_write_byte(Data);				//数据
	iic_receive_ark();
  iic_stop();
}

void OLED_Init()
{
	iic_init();	
	Delay_ms(100);
	
	OLED_WriteCommand(0xAE);
	
	OLED_WriteCommand(0xD5);
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);
	
	OLED_WriteCommand(0xA1);
	
	OLED_WriteCommand(0xC8);
	
	OLED_WriteCommand(0xDA);
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);
	OLED_WriteCommand(0xCF);
	
	OLED_WriteCommand(0xD9);
	OLED_WriteCommand(0xF1);
	
	OLED_WriteCommand(0xDB);
	OLED_WriteCommand(0x30);
	
	OLED_WriteCommand(0xA4);
	
	OLED_WriteCommand(0xA6);
	
	OLED_WriteCommand(0x8D);
	OLED_WriteCommand(0x14);
	
	OLED_WriteCommand(0xAF);
	
	Delay_ms(100);
}

/*
功能：设置光标
X：0~127
Page:0~7
*/
void OLED_SetPoint(unsigned char X,unsigned char Page)
{
	OLED_WriteCommand(0x00 | (X & 0x0F));
	OLED_WriteCommand(0x10 | (X & 0xF0) >> 4);
	OLED_WriteCommand(0xB0 | (Page & 0x07));
}	

/*
功能：清屏
*/
void OLED_Clear(void)
{
	for(unsigned char j = 0;j < 8;j++)				//行
	{
		OLED_SetPoint(0,j);
		for(unsigned char i = 0 ;i < 128;i++)		//列
		{
			OLED_WriteData(0x00);
		}
	}
}

/*
功能：输出一个字符
X：0~15(size=8),0~2(size=6)
Page:0~3(size=8),0~7(size=6)
Char:ASCII码32位~126位
size:6/8
*/
void OLED_Show_Char(unsigned char X,unsigned char Page,char Char,unsigned char size)
{
	switch(size)
	{
		case 6:
			OLED_SetPoint(X*6,Page);
			for(unsigned char i = 0;i < 6;i++)
			{
				OLED_WriteData(OLED_6X8[Char-' '][i]);
			}
			break;
			
		case 8:
			//上半部分8*8
			OLED_SetPoint(X*8,Page*2);
			for(unsigned char i = 0;i < 8;i++)
			{
				OLED_WriteData(OLED_8X16[Char-' '][i]);
			}
			//下半部分8*8
			OLED_SetPoint(X*8,Page*2+1);
			for(unsigned char i = 0;i < 8;i++)
			{
				OLED_WriteData(OLED_8X16[Char-' '][8+i]);
			}
			break;
	}
}
/*
功能：输出一串字符
X：0~15(size=8),0~2(size=6)
Page:0~3(size=8),0~7(size=6)
Char:ASCII码32位~126位
size:6/8
*/
void OLED_Show_String(unsigned char X,unsigned char Page,char* String,unsigned char size)
{
		for(unsigned char i = 0;String[i] != '\0';i++)
		{
			OLED_Show_Char(X+i,Page,String[i],size);
		}
}
