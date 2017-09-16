#include "registers.h"
#include "LCDsetup.h"
#include "timersetup.h"
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
	
	// setup blocks
	SetupGameEnvironment();
	
	SetupGPIOB();
	SetupTimer0A();
	//setupSystick();
	
	// START GAME
	SetupTimer1A(); 
	
	// While not updating the game
	while(1)
	{
		//GameEngine();
		LCD_Refresh();
		//Delay(20);
	}
}
