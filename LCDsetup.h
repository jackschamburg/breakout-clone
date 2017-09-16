#include "registers.h"

// LCD Macros
#define CSport  (*((volatile unsigned long *)0x400043FC))
#define RSTport (*((volatile unsigned long *)0x400043FC))
#define A0port  (*((volatile unsigned long *)0x400043FC))
#define CLKport (*((volatile unsigned long *)0x400243FC))
#define DATport (*((volatile unsigned long *)0x400243FC))
#define CSbit  0x80
#define RSTbit 0x40
#define A0bit  0x20
#define CLKbit 0x20
#define DATbit 0x10

extern void Delay(unsigned int);

void LCD_Init(void);

void LCD_Cmd_Out(unsigned char c);

void LCD_Dat_Out(unsigned char d);

void LCD_Char_Out(unsigned char c);

void LCD_Contrast(unsigned char res_ratio, unsigned char contrast);

void LCD_Refresh(void);

void LCD_Blank(void);

void LCD_Pixel(unsigned char x, unsigned char y, unsigned char colour);

void Setup_LCD_GPIO(void);
