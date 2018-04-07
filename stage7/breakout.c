/*=========================================

Source File:
breakout.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

KNOWN BUGS:
-When the ball is on the paddle and the paddle
	is against a wall the ball will go into the
	paddle
-Occasionally when the ball touches the bottom
	corner it will be drawn on the top of the
	screen
-If the ball hits the side of the paddle the 
	direction of the ball will be changed in 
	the y direction, not the x direction

==========================================*/


#include "render.h"
#include "input.c"
#include "events.h"
#include "rast_asm.h"
#include "in_asm.h"
#include <osbind.h>
#include <stdio.h>
#include <string.h>

typedef void (*Vector) ();

#define Q    0x90
#define KEY_ISR_NUM	70

UINT8 buffer2[32256];
UINT8 background[32256];


unsigned long get_time()
{
	unsigned long *timer;	/* address of longword auto-inc’ed 70 x per s */
	unsigned long timeNow;
	long old_ssp;
	old_ssp = Super(0);				/* enter privileged mode */
	timer = (unsigned long *)0x462;
	timeNow = *timer;
	Super(old_ssp); 				/* exit privileged mode as soon as possible */
	return timeNow;
}

/*=== get_base ===========================================================

Purpose: offset the screen base to be 256 bit aligned

Inputs: start of buffer

Outputs:  new start of buffer

Limitations/Known bugs: N/A
=============================================================================*/

UINT8 *get_base(UINT8 buffer[])
{
	UINT8 *base;
	unsigned int difference;
	base = buffer;
	difference = (int) base;
	difference %= 0x100;
	difference = 0x100 - difference;
	return base + difference;
}

Vector install_vector(int num, Vector vector)
{
  Vector orig;
  Vector *vectp = (Vector *) ((long) num << 2);
  long old_ssp = Super(0);

  orig = *vectp;
  *vectp = vector;

  Super(old_ssp);
  return orig;
}

long goto_super()
{
	return Super(0); 
}

int main()
{
	long old_ssp;
	/* buffer1: space in memory dedicated to the first screen buffer*/
	UINT8 *buffer1_8 = (UINT8 *) get_video_base();
	UINT32 *buffer1_32 = (UINT32 *) get_video_base();


	/* buffer2: space in memory dedicated to the second screen buffer*/
	UINT8 *buffer2_8 = get_base(buffer2);
	UINT32 *buffer2_32 = (UINT32 *) buffer2_8;

	/* background:  buffer specially dedicated to storing the background */
	UINT8 *background_8 = get_base(background);
	UINT32 *background_32 = (UINT32 *) background_8;

	/* pointer to where the renderer is writing to */
	UINT8 *render_base_8 = buffer2_8;
	UINT32 *render_base_32 = buffer2_32;

	/* current:  what the bricks where last screenshot */
	Brick current[5][20];
	int x,y = -1;
	bool hold = False;
	UINT8 hold_mask;
	UINT8 mouse_mask;
	UINT8 input = 0;
	unsigned long timeThen, timeNow, timeElapsed = get_time();
	bool swap = False;

	Vector orig_key = install_vector(KEY_ISR_NUM, key_isr);
	Model game;
	start_game(&game);


	memcpy(current, game.bricks, sizeof(current));
	
	start_queue();
	

	start_render(background_32, &game);
	simple_render(buffer1_8, buffer1_32, &game);



	while(input != Q)
	{
		if(queue_is_empty() == False)
		{
			input = get_input();
			mouse_mask = input & 0xF8;
			/* check for mouse input */
			if(mouse_mask == 0xF8)
			{
				while(queue_is_empty() == False)
				{
					deque();
				}
			}
			/* check for keyboard input */
			else
			{
				hold_mask = input & 0x80;
				if(hold_mask == 0x00)
				{
					hold = True;
				}
				else
				{
					hold = False;
				}
			}
		}
		
		

		timeNow = get_time();
		timeElapsed = timeNow - timeThen;
		if (timeElapsed > 0)
		{
			if(hold == True)
			{
				asynch_events(&game.paddle, &game.ball, input);
			}
			synch_events(&(game.paddle), &(game.ball), game.bricks);
			condition_events(&(game.paddle), &(game.ball), 
							 game.bricks, &(game.score), &(game.lives));
			timeThen = timeNow;

			for(x = 0; x < 5; x++)
			{
				for(y = 0; y < 20; y++)
				{
					if(current[x][y].broken != ((game.bricks)[x][y]).broken)
					{
						remove_brick(background_32, x, y);
					}
				}
			}
			memcpy(current, game.bricks, sizeof(current));

			memcpy(render_base_8, background_8, 32000);
			render(render_base_8, render_base_32, &game);

			if(swap == True)
			{
				render_base_8 = buffer2_8;
				render_base_32 = buffer2_32;
				old_ssp = Super(0);
				set_screen_base(buffer1_8);
				Super(old_ssp);
				swap = False;
			}
			else
			{
				render_base_8 = buffer1_8;
				render_base_32 = buffer1_32;
				old_ssp = Super(0);
				set_screen_base(buffer2_8);
				Super(old_ssp);
				swap = True;
			}
			Vsync();
		}

	}
	
	
	old_ssp = Super(0);
	set_screen_base(buffer1_8);
	Super(old_ssp);
	
	Vsync();
	
	install_vector(KEY_ISR_NUM, orig_key);
	return 0;
}
