#include "stm32f10x.h"
#include "Delay.h"

#define iic_GPIO 		GPIOB
#define Pin_SCL 		GPIO_Pin_1
#define Pin_SDA 		GPIO_Pin_0
#define iic_SCL_H()	GPIO_SetBits(iic_GPIO,Pin_SCL)//GPIO_WriteBit(iic_GPIO,Pin_SCL, 1)
#define iic_SCL_L()	GPIO_ResetBits(iic_GPIO,Pin_SCL)//GPIO_WriteBit(iic_GPIO,Pin_SCL, 0)
#define iic_SDA_H()	GPIO_SetBits(iic_GPIO,Pin_SDA)//GPIO_WriteBit(iic_GPIO,Pin_SDA, 1)
#define iic_SDA_L()	GPIO_ResetBits(iic_GPIO,Pin_SDA)//GPIO_WriteBit(iic_GPIO,Pin_SDA, 0)

void iic_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=Pin_SCL|Pin_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(iic_GPIO,&GPIO_InitStructure);
	GPIO_SetBits(iic_GPIO,Pin_SCL|Pin_SDA);
}

void iic_start(void)
{
	iic_SDA_H();
	iic_SCL_H();
	iic_SDA_L();
	iic_SCL_L();
}

void iic_stop(void)
{
	iic_SDA_L();
	iic_SCL_H();
	iic_SDA_H();
}

/*
发送应答函数
ark=0产生应答
ark=1不产生应答
*/
void iic_send_ark(char ark)
{
	if(ark==0) 
		iic_SDA_L();
	else 
		iic_SDA_H();
	iic_SCL_H();
	iic_SCL_L();
}

/*
接收应答函数
返回0有应答
返回1无应答
*/
unsigned char iic_receive_ark(void)
{
	uint8_t AckBit;
	iic_SDA_H();
	iic_SCL_H();
	AckBit=GPIO_ReadInputDataBit(iic_GPIO,Pin_SDA);
	iic_SCL_L();
	return AckBit;
}
/*
发送1字节函数
返回1成功发送
返回0发送无效
*/
void iic_write_byte(unsigned char Byte)
{
	for(int i=0;i<8;i++)
	{
		if(Byte & 0x80)
			iic_SDA_H();
		else
			iic_SDA_L();
		iic_SCL_H();
		Byte <<= 1;
		iic_SCL_L();	
	}	
}

unsigned char iic_receive_byte(char ark)
{
	unsigned char Date=0x00;
	iic_SDA_H();
	for(int i=0;i<8;i++)
	{
		iic_SCL_H();	
		Date <<= 1;
		if(GPIO_ReadInputDataBit(iic_GPIO,Pin_SDA)==1)
			Date++;	
		iic_SCL_L();
	}
	iic_send_ark(ark);
	return Date;
}
