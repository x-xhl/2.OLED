#ifndef __OLED_H
#define __OLED_H


void OLED_Init(void);
void OLED_WriteCommand(unsigned char Command);
void OLED_WriteData(unsigned char *Data,unsigned char Count);
void OLED_SetPoint(unsigned char X,unsigned char Page);
void OLED_Updata(void);
void OLED_Clear(void);
void OLED_AreaClear(unsigned char X,unsigned char Y,unsigned char Width,unsigned char Height);
void OLED_Show_Char(unsigned char X,unsigned char Y,char Char,unsigned char size,unsigned char Scroll);
void OLED_Show_String(unsigned char X,unsigned char Y,char* String,unsigned char size,unsigned char Scrol);
void OLED_Show_Img(unsigned char X,unsigned char Y,unsigned char Width,unsigned char Height,const unsigned char* Img,unsigned char Scroll);
void OLED_Show_Chinese(unsigned char X,unsigned char Y,char* Chinese,unsigned char Scroll);
void OLED_Show_Point(unsigned char X,unsigned char Y);
void OLED_Clear_Point(unsigned char X,unsigned char Y);
#endif
