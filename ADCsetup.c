#include "registers.h"
#include "ADCsetup.h"

void SetupADC(void)
{
	//SetupSWare
	SYSCTL_RCGCADC |= 2;
	while( (SYSCTL_PRADC & 2 ) != 2 );
	
	//GPIO setup for E2
	SYSCTL_RCGCGPIO |= 0x10;
	while( (SYSCTL_PRGPIO & 0x10) != 0x10 );
	GPIOE_DIR 	&= ~4;
	GPIOE_AFSEL	|=  4;
	GPIOE_DEN		&= ~4;
	GPIOE_AMSEL |=  4;
	
	//ADC Setup
	ADC1_ACTSS	&= ~2;
	ADC1_PC			 =  7;
	ADC1_SSMUX1  =  1;
	ADC1_EMUX		 =  0;
	ADC1_SSCTL1 |=  6;
	ADC1_SSCTL1 &= ~9;
	
	//Setup Interrupts
	__asm("CPSID I");
	ADC1_IM		&= ~2;
	NVIC_EN1	|= (1<<17);
	ADC1_ISC	|= 2;
	ADC1_IM		|= 2;
	__asm("CPSIE I");
	ADC1_ACTSS	|=  2;       
}
