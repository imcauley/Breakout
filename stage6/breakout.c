#include "render.h"
#include "input.c"
#include "events.h"
#include <osbind.h>
#include <stdio.h>
#include <string.h>

UINT8 buffer2[32500];

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

	long input = 0;
	unsigned long timeThen, timeNow, timeElapsed = 0;
	bool swap = 0;

	
	Model game;
	start_game(&game);

	Setscreen(-1,buffer2_8,-1);
	while(input != 0x00100071)
	{
		timeNow = get_time();
		timeElapsed = timeNow - timeThen;

		if(key_pressed() == True)
		{
			input = get_input();
			asynch_events(&game.paddle, &game.ball, input);
		}

		if (timeElapsed > 0)
		{
			synch_events(&(game.paddle), &(game.ball), game.bricks);
			timeThen = timeNow;
			
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
			
			simple_render(render_base_8, render_base_32, &game);
		}
		add_score(&(game.score));
		
	}
	Setscreen(-1,buffer1_8,-1);

	return 0;
}
