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
	OLED_Show_String(5,10,"Hello,world",6);
	OLED_Show_String(5,16,"Hello,world",8);
	//OLED_Show_Chinese(16,16,"ƒ„∫√ ¿ΩÁ—Ω");
	//OLED_Show_Img(2,10,32,32,Img32X32[0]);
	OLED_Updata();
	
	while(1)
	{
		
	}	
}
