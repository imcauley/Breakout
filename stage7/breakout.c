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

==========================================*/


#include "render.h"
#include "input.c"
#include "events.h"
#include <osbind.h>
#include <stdio.h>
#include <string.h>

#define Q    0x00100071

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

int main()
{
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

	long input = 0;
	unsigned long timeThen, timeNow, timeElapsed = get_time();
	bool swap = False;


	Model game;
	start_game(&game);


	memcpy(current, game.bricks, sizeof(current));

	render_splash_screen(buffer1_32);
	/*
	start_render(background_32, &game);
	simple_render(buffer1_8, buffer1_32, &game);

	printf("\033f");
	fflush(stdout);
*/
/*
	psudo-code game loop:

	while(running):

		if(key_pressed):
			process asynch_events

		if(frame has changed):
			process synch_events
			process condition_events

			if(any bricks have been removed):
				remove bricks
			copy current bricks to brick snapshot

		if(buffer1_active):
			write with buffer1
			render with buffer2
		else:
			write with buffer2
			redner with buffer1

		wait until next frame
*/

	/*
	while(input != Q)
	{
		if(key_pressed() == True)
		{
			input = get_input();
			asynch_events(&game.paddle, &game.ball, input);
		}
	render_splash_screen(buffer1_32);

		timeNow = get_time();
		timeElapsed = timeNow - timeThen;
		if (timeElapsed > 0)
		{
			synch_events(&(game.paddle), &(game.ball), game.bricks);
			condition_events(&(game.paddle), &(game.ball), game.bricks, &(game.score), &(game.lives));
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
				Setscreen(-1,buffer1_8,-1);
				swap = False;
			}
			else
			{
				render_base_8 = buffer1_8;
				render_base_32 = buffer1_32;
				Setscreen(-1,buffer2_8,-1);
				swap = True;
			}
			Vsync();
		}

	}
	Setscreen(-1,buffer1_8,-1);
	Vsync();
	printf("\033e");
	fflush(stdout);
	*/
	return 0;
}
