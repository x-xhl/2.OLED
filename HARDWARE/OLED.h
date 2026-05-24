#ifndef __OLED_H
#define __OLED_H


void OLED_Init(void);
void OLED_WriteCommand(unsigned char Command);
void OLED_WriteData(unsigned char Data);
void OLED_SetPoint(unsigned char X,unsigned char Page);
void OLED_Clear(void);
void OLED_Show_Char(unsigned char X,unsigned char Page,char Char,unsigned char size);
void OLED_Show_String(unsigned char X,unsigned char Page,char* String,unsigned char size);
#endif
