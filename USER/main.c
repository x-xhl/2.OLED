#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "iic.h"
#include "usart.h"
#include "MyI2C.h"
#include "OLED.h"
extern const unsigned char Img15X15[][30];
extern const unsigned char Img32X32[][128];
extern const unsigned char OLED_6X8[][6];
extern const unsigned char Chinese_16X16_Char[][32];
extern unsigned char OLED_Buf[8][128];
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

//	OLED_Show_String(50,17,"Hello",6,0);
	OLED_Show_Char(0,0,'F',6,0);
	
	while(1)
	{
//		for(unsigned int i=0;i<=256;i++)
//		{
//			if(i==256) i=0;
//			OLED_Show_Chinese(i,0,"ÄãºÃÊÀ½ç",1);
//			Delay_ms(10);
//			OLED_Updata();
//		}
		for(unsigned char i=0;i<10;i++)
		{
			OLED_Show_Point(1,i);
		}
		OLED_Updata();
		Delay_ms(500);
		for(unsigned char i=0;i<10;i++)
		{
			OLED_Clear_Point(1,i);
		}
		OLED_Updata();
		Delay_ms(500);
	}	
		
}
