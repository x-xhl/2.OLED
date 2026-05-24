#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "iic.h"
#include "usart.h"
#include "MyI2C.h"
#include "OLED.h"

int main(void)
{
//	Led_Init();
//	iic_init();	
//	iic_start();
//	iic_write_byte(0x78);
//	unsigned char ark=iic_receive_ark();
//	iic_stop();
//	if(ark==0)
//		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
//	else
//		GPIO_SetBits(GPIOB,GPIO_Pin_13);
	OLED_Init();
	OLED_Clear();
	
//	OLED_SetPoint(0,0);
//	OLED_WriteData(0x01);
//	OLED_WriteData(0x03);
//	OLED_WriteData(0x07);
//	OLED_WriteData(0x0f);
//	OLED_WriteData(0x1f);
//	OLED_WriteData(0x3f);
//	OLED_WriteData(0x7f);
//	OLED_WriteData(0xff);
//	OLED_SetPoint(127,7);
//	OLED_WriteData(0xff);
//	OLED_SetPoint(128,7);
//	OLED_WriteData(0x55);
//	OLED_Show_Char(0,0,'1',8);
//	OLED_Show_Char(1,0,'1',8);
//	OLED_Show_Char(2,0,'1',8);
//	OLED_Show_Char(3,0,'1',8);

//	OLED_Show_Char(5,0,'2',6);
//	OLED_Show_Char(6,0,'2',6);
//	OLED_Show_Char(2,2,'3',8);
//	OLED_Show_Char(0,3,'4',8);
//	OLED_Show_Char(1,2,'5',8);
//	OLED_Show_Char(20,7,'6',6);
	OLED_Show_String(0,0,"hello",6);
	OLED_Show_String(0,1,"world",6);
	OLED_Show_String(4,0,"Hello",8);
	OLED_Show_String(0,1,"Hello",8);
	while(1)
	{
		
	}	
}
