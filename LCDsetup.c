#include "LCDsetup.h"

volatile unsigned char LCDmat[1024];
extern void Delay(unsigned int);

void LCD_Init(void)
{
	CSport		&= ~CSbit;
	RSTport		&= ~RSTbit;
	Delay(50);
	RSTport		|=	RSTbit;
	Delay(50);
	
	LCD_Cmd_Out(0xA2);
	LCD_Cmd_Out(0xA0);
	LCD_Cmd_Out(0xC0);
	LCD_Cmd_Out(0xC8);
	LCD_Cmd_Out(0x20|0x3);
	LCD_Cmd_Out(0x28|0x4);
	Delay(50);
	LCD_Cmd_Out(0x28|0x6);
	Delay(50);
	LCD_Cmd_Out(0x28|0x7);
	Delay(50);
	LCD_Cmd_Out(0x26);
	LCD_Cmd_Out(0x81);
	LCD_Cmd_Out(31);
	LCD_Cmd_Out(0x40);
	LCD_Cmd_Out(0xAF);
	
	CSport |= CSbit;
	
	// set contrast
	LCD_Contrast(5, 50);
	LCD_Cmd_Out(0xF0);
}

void LCD_Cmd_Out(unsigned char c)
{
	A0port &= ~A0bit;
	LCD_Char_Out(c & 0xFF);
}

void LCD_Dat_Out(unsigned char d)
{
	A0port |= A0bit;
	LCD_Char_Out(d & 0xFF);
}

void LCD_Char_Out(unsigned char c)
{
	CSport &= ~CSbit;
	
	unsigned int counter = 0;
	
	for (counter=0; counter < 8; counter++)
	{
		if ( (c & 0x80) == 0 )
			DATport &= ~DATbit;
		else
			DATport |=  DATbit;
		
		// pulse clock
		CLKport |=  CLKbit;
		CLKport &= ~CLKbit;
		
		c = c << 1;
	}
	
	CSport |= CSbit;
}

void LCD_Contrast(unsigned char res_ratio, unsigned char contrast)
{
	if ( res_ratio > 7 )
		res_ratio = 7;
	if ( contrast > 63 )
		contrast = 63;
	
	LCD_Cmd_Out(res_ratio | 0x20);
	LCD_Cmd_Out(0x81);
	LCD_Cmd_Out(contrast);
}

void LCD_Refresh(void)
{
	int x,y;
	
	for (y=0;y<8; y++)
	{
		LCD_Cmd_Out(y | 0xB0);
		LCD_Cmd_Out(0);
		LCD_Cmd_Out(0x10);
		
    for(x=0; x<128; x++)
			LCD_Dat_Out(LCDmat[y*128+x]);
	}
}

void LCD_Blank(void)
{
	unsigned int i;
	
	for(i=0; i<1024; i++)
		LCDmat[i] = 0;
	
	LCD_Refresh();
}

void LCD_Pixel(unsigned char x, unsigned char y, unsigned char colour)
{
	x--;
	if ( y < 33 )
		y += 32;
	else
		y -= 32;
	
	y--;

	if(colour == 1)
		LCDmat[x + (y/8) * 128] |= (1 << (y%8));
  else
		LCDmat[x + (y/8) * 128] &= ~(1 << (y%8));
}

void Setup_LCD_GPIO(void)
{
	// setup GPIO A
	SYSCTL_RCGCGPIO |= 1;
	while ( (SYSCTL_PRGPIO & 1) != 1);
	
	GPIOA_DIR   |=  0xE0;
	GPIOA_AFSEL &= ~0xE0;
	GPIOA_DEN		|=  0xE0;
	
	// setup GPIO E
	SYSCTL_RCGCGPIO |= 0x10;
	while ( (SYSCTL_PRGPIO & 0x10) != 0x10);
	
	GPIOE_DIR    |=  0x38;
	GPIOE_AFSEL  &= ~0x38;
	GPIOE_DEN    |=  0x38;
	
}

unsigned char LCDstate(unsigned char x, unsigned char y)
{
	
	x--;
	if ( y < 33 )
		y += 32;
	else
		y -= 32;
	y--;

	return ((LCDmat[x + (y/8) * 128] & (1 << (y%8))) >> (y%8));
	
}
