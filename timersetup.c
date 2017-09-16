#include "timersetup.h" 

void SetupInterrupts(void)
{
	GPIOF_IM  &= ~0x11;
	GPIOF_IS  &= ~0x11;
	GPIOF_IBE &= ~0x11;
	GPIOF_IEV |=  0x11;
	GPIOF_IM  |=  0x11;
	NVIC_EN0  |=  (1<<30);
}

void SetupTimer1A(void)
{
	SYSCTL_RCGTIMER |= 2;
	while ((SYSCTL_PRTIMER & 2) != 2);
	
	TIMER1_CTL 			&=~ 1;
	TIMER1_CFG 			|= 4;
	TIMER1_TAMR 		&= ~0x242;
	TIMER1_TAMR 		|= 0x32;
	TIMER1_TAILR		 = 65041;
	TIMER1_TAPR			 = 41;
	TIMER1_IMR			 = 1;
	TIMER1_ICR			|= 0x10;
	NVIC_EN0 				|= (1<<21);
	TIMER1_CTL 			|= 1;
}

void SetupTimer2A(void)
{
	SYSCTL_RCGTIMER |= 4;
	while ((SYSCTL_PRTIMER & 4) != 4);
	
	TIMER2_CTL 			&= ~1;
	TIMER2_CTL			&= ~40;
	TIMER2_CFG 			|= 4;
	TIMER2_TAMR 		|= 0xA;
	TIMER2_TAMATCH	&= ~5;
	TIMER2_TAILR		 = 0xFFFF;
	TIMER2_TAMATCH 	 = 0xFFFE;
	TIMER2_TAMR 		&= ~0x200;
	TIMER2_CTL 			|= 1;
}

void SetupGPIOF(void)
{
	// setup clock
	SYSCTL_RCGCGPIO |= 0x20;
	while ( (SYSCTL_PRGPIO & 0x20) != 0x20);
	
	// unlock button
	GPIOF_LOCK  = 0x4C4F434B;
	GPIOF_CR   |= 0x1;
	
	// set direction for pins
	GPIOF_DIR &= ~0x10;
	GPIOF_DIR |= 0xF;
	
	GPIOF_PUR  |= 0x11;
	GPIOF_DR4R |= 0x11;
	
	// set alternate functions
	GPIOF_AFSEL &= ~0x1B;
	GPIOF_AFSEL |= 4;
	
	// set port control
	GPIOF_PCTL |= 0x700;
	
	// turn on digital enable
	GPIOF_DEN |= 0x1F;
}


//void SetupGPIOB(void)
//{
//	// setup clock
//	SYSCTL_RCGCGPIO |= 0x2;
//	while ( (SYSCTL_PRGPIO & 0x2) != 0x2);
//	
//	// set direction for pins
//	GPIOB_DIR |= 0x40;
//	
//	// set alternate functions
//	GPIOB_AFSEL |= 0x40;
//	
//	// set port control
//	GPIOB_PCTL |= 0x4000000;
//	
//	// turn on digital enable
//	GPIOB_DEN |= 0x40;
//}

void audioTest(void) 
{
	static unsigned char x = 0x40;
	x ^= 0x40;
	GPIOB_DATA = x;
}
