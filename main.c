#include "registers.h"
#include "LCDsetup.h"
#include "timersetup.h"
#include "ADCsetup.h"
#include "Buttonsetup.h"
#include "game.h"

//extern unsigned char inBounds;

int main(void)
{
	//setup LCD
	Setup_LCD_GPIO();
	LCD_Init();
	LCD_Blank();
	
	//setup joystick
	SetupADC();
	
	//setup audio
	SetupGPIOB();
	SetupTimer0A();
	
	//setup restart button
	SetupButton();
	
	// setup blocks
	SetupGameEnvironment();
	
	//START GAME
	SetupTimer1A(); 
		
	// game loop
	while(1)
	{
		//GameEngine();
		LCD_Refresh();
		ADC1_PSSI |= 2;
	}
	
	// spin on spot
	while(1);
}
