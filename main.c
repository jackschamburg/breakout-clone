#include "registers.h"
#include "LCDsetup.h"
#include "timersetup.h"
#include "ADCsetup.h"
#include "game.h"

int main(void)
{
 	SetupGPIOF();
	__asm("CPSID I");
	SetupInterrupts();
	__asm("CPSIE I");
	
	Setup_LCD_GPIO();
	LCD_Init();
	LCD_Blank();
	
	SetupADC();
	
	
	// setup blocks
	SetupGameEnvironment();
	
	//setup audio
	//SetupGPIOB();
	//SetupTimer0A();
	
	// START GAME
	SetupTimer1A(); 
	
	// While not updating the game
	while(1)
	{
		//GameEngine();
		LCD_Refresh();
		ADC1_PSSI |= 2;
		//Delay(20);
	}
}
