#include "stm32f10x.h"
#include "iic.h"
#include "Delay.h"
#include "OLED.h"
#include "OLED_Data.h"
#include <string.h>

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

void OLED_WriteData(unsigned char *Data,unsigned char Count)
{
	iic_start();
	iic_write_byte(0x78);				//寻址
	iic_receive_ark();
	iic_write_byte(0x40);				//非连续模式，写数据
	iic_receive_ark();
	for(unsigned char i=0;i<Count;i++)
	{
		iic_write_byte(Data[i]);				//数据
		iic_receive_ark();
	}
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

unsigned char OLED_Buf[8][128]={0};
/*
功能：屏幕更新
*/
void OLED_Updata(void)
{
	for(unsigned char i=0;i<8;i++)
	{
		OLED_SetPoint(0,i);
		OLED_WriteData(OLED_Buf[i],128);
	}
}

/*
功能：清屏
*/
void OLED_Clear(void)
{
	for(unsigned char i = 0;i < 8;i++)				//行
	{
		for(unsigned char j = 0;j < 128;j++)				//列
		{
			OLED_Buf[i][j]=0x00;
		}
	}
	OLED_Updata();
}

/*
功能：清屏
*/
void OLED_AreaClear(unsigned char X,unsigned char Y,unsigned char Width,unsigned char Height)
{
	for(unsigned char i = 0;i < (Height-1)/8+1;i++)				//行
	{
		for(unsigned char j = 0;j < Width;j++)				//列
		{
//			OLED_Buf[Y/8+i][X+j] &= ~0xFF<<(Y % 8);
//			OLED_Buf[Y/8+1+i][X+j] &= ~0xFF>>(8- Y % 8);
			OLED_Buf[(Y/8+i)%8][(X+j)%128] &= ~(0xFF<<(Y % 8));
			OLED_Buf[(Y/8+1+i)%8][(X+j)%128] &= ~(0xFF>>(8- Y % 8));
		}
	}
}
/*
功能：输出一个字符
X		:0~119	(size=8),0~121	(size=6)
Y		:0~63
Char:ASCII码32位~126位
size:6/8
*/
void OLED_Show_Char(unsigned char X,unsigned char Y,char Char,unsigned char size,unsigned char Scroll)
{
	switch(size)
	{
		case 6:
			OLED_Show_Img(X,Y,6,6,OLED_6X8[Char-' '],Scroll);
			break;
			
		case 8:
			OLED_Show_Img(X,Y,8,16,OLED_8X16[Char-' '],Scroll);
			break;
	}
}
/*
功能：输出一串字符
X		:0~119	(size=8),0~121	(size=6)
Y		:0~63
Char:ASCII码32位~126位
size:6/8
*/
void OLED_Show_String(unsigned char X,unsigned char Y,char* String,unsigned char size,unsigned char Scroll)
{
	for(unsigned char i = 0;String[i] != '\0';i++)
	{
		OLED_Show_Char(X+i*size,Y,String[i],size,Scroll);
	}
}

/*
功能：输出图像
X			:0~127	
Y			:0~63
*/
void OLED_Show_Img(unsigned char X,unsigned char Y,unsigned char Width,unsigned char Height,const unsigned char* Img,unsigned char Scroll)
{
	if(Scroll)
	{
		OLED_AreaClear(X-1,Y-1,Width,Height);
	}
	OLED_AreaClear(X,Y,Width,Height);
	for(unsigned char i = 0;i < (Height-1)/8+1;i++)
	{
		for(unsigned char j = 0;j < Width;j++)
		{
//			OLED_Buf[Y/8+i][X+j] |=Img[j+i*Width]<<(Y%8);
//			OLED_Buf[Y/8+1+i][X+j] |=Img[j+i*Width]>>(8-Y%8);
			OLED_Buf[(Y/8+i)%8][(X+j)%128] |=Img[j+i*Width]<<(Y%8);
			OLED_Buf[(Y/8+1+i)%8][(X+j)%128] |=Img[j+i*Width]>>(8-Y%8);
		}
	}
}

void OLED_Show_Chinese(unsigned char X,unsigned char Y,char* Chinese,unsigned char Scroll)
{
	char Char[3]={0};
	unsigned char iNum=0;
	unsigned char index;
	for(unsigned char i=0;Chinese[i] != '\0';i++) //取单个汉字编码(GB2312)
	{
		Char[iNum]= Chinese[i];
		iNum++;
		if(iNum>=2)
		{
			iNum=0;
			for(index=0;strcmp(Chinese_16X16_Char[index].Index,"");index++)	//字模库中遍历
			{
				if(strcmp(Chinese_16X16_Char[index].Index,Char)==0)
					break;
			}		
			OLED_Show_Img(X+((i+1)/2-1)*16,Y,16,16,Chinese_16X16_Char[index].Chinese_16X16_Char, Scroll);
		}
	}
}
