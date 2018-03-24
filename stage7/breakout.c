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
	UINT8 *buffer1_8 = (UINT8 *) Physbase();
	UINT32 *buffer1_32 = (UINT32 *) Physbase();

	UINT8 *buffer2_8 = get_base(buffer2);
	UINT32 *buffer2_32 = (UINT32 *) buffer2_8;

	UINT8 *render_base_8 = buffer2_8;
	UINT32 *render_base_32 = buffer2_32;

	UINT8 *background_8 = get_base(background);
	UINT32 *background_32 = (UINT32 *) background_8;
	int x,y = -1;

	Brick current[5][20];

	long input = 0;
	unsigned long timeThen, timeNow, timeElapsed = get_time();
	bool swap = False;


	Model game;
	start_game(&game);

	memcpy(current, game.bricks, sizeof(current));

	start_render(background_32, &game);
	simple_render(buffer1_8, buffer1_32, &game);

	printf("\033f");
	fflush(stdout);

	while(input != Q)
	{
		if(key_pressed() == True)
		{
			input = get_input();
			asynch_events(&game.paddle, &game.ball, input);
		}

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

	return 0;
}
