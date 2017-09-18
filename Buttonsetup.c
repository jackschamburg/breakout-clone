#include "registers.h"

void SetupButton(void)
{
	// setup clock
	SYSCTL_RCGCGPIO |= 0x20;
	while ( (SYSCTL_PRGPIO & 0x20) != 0x20);
	
	// unlock button
	GPIOF_LOCK  = 0x4C4F434B;
	GPIOF_CR   |= 0x1;
	
	// set direction for pins
	GPIOF_DIR |= 0x1;
	//GPIOF_DIR |= 0xE;
	
	GPIOF_PUR  |= 0x11;
	GPIOF_DR4R |= 0x11;
	
	// set alternate functions
	GPIOF_AFSEL &= ~0xFF;
	
	// turn on digital enable
	GPIOF_DEN |= 0x1F;
	
	//setup interrupts
	GPIOF_IM  &= ~0x11;
	GPIOF_IS  &= ~0x11;
	GPIOF_IBE &= ~0x11;
	GPIOF_IEV |=  0x11;
	GPIOF_IM  |=  0x11;
	//NVIC_PRI7 |= (1<<21);
	NVIC_EN0  |=  (1<<30);
}
