#include "stm32f10x.h"

void Delay_us(uint32_t us)
{
	uint32_t temp;
	SysTick->LOAD = 9 * us;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	do
	{
		temp = SysTick->CTRL;
	}while(!(temp & 0x00010000));
	SysTick->CTRL = 0x00;
}

void Delay_ms(uint32_t ms)
{
	uint32_t temp;
	SysTick->LOAD = 9000 * ms;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	do
	{
		temp = SysTick->CTRL;
	}while(!(temp & 0x00010000));
	SysTick->CTRL = 0x00;
}
