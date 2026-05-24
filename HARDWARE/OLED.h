#ifndef __OLED_H
#define __OLED_H


void OLED_Init(void);
void OLED_WriteCommand(unsigned char Command);
void OLED_WriteData(unsigned char *Data,unsigned char Count);
void OLED_SetPoint(unsigned char X,unsigned char Page);
void OLED_Updata(void);
void OLED_Clear(void);
void OLED_Show_Char(unsigned char X,unsigned char Y,char Char,unsigned char size);
void OLED_Show_String(unsigned char X,unsigned char Y,char* String,unsigned char size);
void OLED_Show_Img(unsigned char X,unsigned char Y,unsigned char Width,unsigned char Height,const unsigned char* Img);
void OLED_Show_Chinese(unsigned char X,unsigned char Y,char* Chinese);
#endif
