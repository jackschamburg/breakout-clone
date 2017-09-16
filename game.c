#include "registers.h"
#include "LCDsetup.h"
#include "game.h"

// GLOBAL VARIABLES
struct Block blocks[20];

void Delay(unsigned int Ms)
{
	volatile unsigned int i;
	volatile unsigned int j;

	for(i=0; i<Ms; i++)
		for (j=0; j<16000; j++);
}


void SetupGameEnvironment(void)
{
	unsigned char x,y, bid = 0;
	// create blocks in structs
	for ( y = 6; y < 20; y += 10 )
		for ( x = 6; x < 122; x += 12 )
		{
			blocks[bid].x1 = x;
			blocks[bid].y1 = y;
			blocks[bid].x2 = x+6;
			blocks[bid].y2 = y+4;
			
			// display them on screen
			unsigned char i,j;
			for(j=blocks[bid].y1; j<=blocks[bid].y2; j++)
				for(i=blocks[bid].x1; i<=blocks[bid].x2; i++)
				{
					LCD_Pixel(i,j,1);
				}
			bid++;
		}
	LCD_Refresh();
}

void GameEngine(void)
{
	static struct Ball ball = {6,6, 2, 2};

	// clear ball at old location
	LCD_Pixel(ball.x, 	ball.y, 	0);
	LCD_Pixel(ball.x+1, ball.y, 	0);
	LCD_Pixel(ball.x, 	ball.y+1, 0);
	LCD_Pixel(ball.x+1, ball.y+1, 0);

	// check if next to wall
	if ( ball.x+2 >= 128 || ball.x-1 <= 1 )
		ball.x_speed *= -1;
	if ( ball.y+2 >= 64  || ball.y-1 <= 1 )
		ball.y_speed *= -1;
	
	// check if next to block in direction its going
	//if ( ball.x+2

	// update location
	ball.x += ball.x_speed;
	ball.y += ball.y_speed;
	
	// display ball at new location
	LCD_Pixel(ball.x, 	ball.y, 	1);
	LCD_Pixel(ball.x+1, ball.y, 	1);
	LCD_Pixel(ball.x, 	ball.y+1, 1);
	LCD_Pixel(ball.x+1, ball.y+1, 1);
	
		
	GPIOF_ICR  |= 0x11;
	TIMER1_ICR |= 0x11;
}
