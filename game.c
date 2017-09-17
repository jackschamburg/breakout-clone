#include "registers.h"
#include "LCDsetup.h"
#include "game.h"

// GLOBAL VARIABLES
struct Block blocks[20];
struct Paddle paddle = {58,61,70,62, 0x1F};

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
	static struct Ball ball = {8, 59, 2, (char)-2};
	
	
	// Delete old paddle
	for(int b=paddle.y1; b<=paddle.y2; b++)
	{
		for(int a=paddle.x1; a<=paddle.x2; a++)
		{
			LCD_Pixel(a,b,0);
		}
	}
	
	if ( paddle.x_dir < 5 )
	{
		paddle.x1 -= 4;
		paddle.x2 -= 4;
	}
	else if ( paddle.x_dir > 47 )
	{
		paddle.x1 += 4;
		paddle.x2 += 4;
	}
	
	// Draw new paddle
	for(int b=paddle.y1; b<=paddle.y2; b++)
	{
		for(int a=paddle.x1; a<=paddle.x2; a++)
		{
			LCD_Pixel(a,b,1);
		}
	}

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
	unsigned char block_hit_x=0, block_hit_y=0;
	
	if ( LCDstate(ball.x, ball.y+2) )
	{
		ball.y_speed *= -1;
		block_hit_x = ball.x;
		block_hit_y = ball.y+2;
	}
	else if ( LCDstate(ball.x, ball.y-1) )
	{
		ball.y_speed *= -1;
		block_hit_x = ball.x;
		block_hit_y = ball.y-1;
	}
	if ( LCDstate(ball.x+2, ball.y) )
	{
		ball.x_speed *= -1;
		block_hit_x = ball.x+2;
		block_hit_y = ball.y;
	}
	else if ( LCDstate(ball.x-1, ball.y) )
	{
		ball.x_speed *= -1;
		block_hit_x = ball.x-1;
		block_hit_y = ball.y;
	}
	
	// if ball hit block, delete block
	if ( block_hit_x || block_hit_y )
	{
		// find out which ball it is
		int i;
		for ( i=0; i<20; i++ )
		{
			if ( (block_hit_x >= blocks[i].x1) && (block_hit_x <= blocks[i].x2) )
				if ( (block_hit_y >= blocks[i].y1) && (block_hit_y <= blocks[i].y2) )
					break;
		}
		//
		int j,k;
		for(j=blocks[i].y1; j<=blocks[i].y2; j++)
			for(k=blocks[i].x1; k<=blocks[i].x2; k++)
			{
				LCD_Pixel(k,j,0);
			}
	}

	// update location	
	ball.x += ball.x_speed;
	ball.y += ball.y_speed;
	
	// display ball at new location
	LCD_Pixel(ball.x, 	ball.y, 	1);
	LCD_Pixel(ball.x+1, ball.y, 	1);
	LCD_Pixel(ball.x, 	ball.y+1, 1);
	LCD_Pixel(ball.x+1, ball.y+1, 1);
	
	TIMER1_ICR |= 0x11;
}

void Joystick_X_ISR(void)
{
	static int dbug = 0;
	dbug = paddle.x_dir = ADC1_SSFIFO1;
	ADC1_ISC |= 0x2;
}
