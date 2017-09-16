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

void SetupTimer0A(void)
{
	SYSCTL_RCGTIMER |= 1;
	while ((SYSCTL_PRTIMER & 1) != 1);
	
	TIMER0_CTL 			&= ~1;
	TIMER0_CTL			&= ~0x48;
	TIMER0_CTL			|= 4;
	TIMER0_CFG 			|= 0x4;
	TIMER0_TAMR 		|= 0xA;
	TIMER0_TAMR			&= ~0x265;
	TIMER0_TAILR		 = 0xFFFE;
	//TIMER0_TAPR			 = 0xFFFF;
	TIMER0_TAMATCH 	 = 0xAE00;
	//TIMER0_TAPMR		 = 0xFFFF;
	TIMER0_TAMR 		&= ~0x200;
	TIMER0_CTL 			|= 1;
}

void SetupGPIOF(void)
{
	// setup clock
	SYSCTL_RCGCGPIO |= 0x20;
	while ( (SYSCTL_PRGPIO & 0x20) != 0x20);

	// set direction for pins
	GPIOF_DIR |= 1;
	
	// set alternate functions
	GPIOF_AFSEL |= 1;
	
	// set port control
	GPIOF_PCTL |= 7;
	
	// turn on digital enable
	GPIOF_DEN |= 1;
}


void SetupGPIOB(void)
{
	// setup clock
	SYSCTL_RCGCGPIO |= 0x2;
	while ( (SYSCTL_PRGPIO & 0x2) != 0x2);
	
	// set direction for pins
	GPIOB_DIR |= 0x40;
	
	// set alternate functions
	GPIOB_AFSEL |= 0x40;
	
	// set port control
	GPIOB_PCTL |= 0x7000000;
	
	// turn on digital enable
	GPIOB_DEN |= 0x40;
}

void audioTest(void) 
{
	static unsigned char x = 0x40;
	x ^= 0x40;
	GPIOB_DATA = x;
}
