#include "registers.h"

void SetupInterrupts(void);

void SetupTimer1A(void);

void SetupTimer2A(void);

void SetupGPIOF(void);

void setupSystick(void);

void SetupGPIOB(void);

void audioTest(void);

//void SetupGPIOF(void)
//{
//	// setup clock
//	SYSCTL_RCGCGPIO |= 0x20;
//	while ( (SYSCTL_PRGPIO & 0x20) != 0x20);
//	
//	// unlock button
//	GPIOF_LOCK  = 0x4C4F434B;
//	GPIOF_CR   |= 0x1;
//	
//	// set direction for pins
//	GPIOF_DIR &= ~0x11;
//	GPIOF_DIR |= 0xE;
//	
//	GPIOF_PUR  |= 0x11;
//	GPIOF_DR4R |= 0x11;
//	
//	// set alternate functions
//	GPIOF_AFSEL &= ~0x1B;
//	GPIOF_AFSEL |= 4;
//	
//	// set port control
//	GPIOF_PCTL |= 0x700;
//	
//	// turn on digital enable
//	GPIOF_DEN |= 0x1F;
//}


//void setupSystick(void)
//{
//	NVIC_ST_CTRL &= ~1;
//	NVIC_ST_RELOAD = 50;
//	NVIC_ST_CURRENT &= ~1;
//	NVIC_ST_CTRL |= 6;
//	NVIC_ST_CTRL |= 1;
//}
