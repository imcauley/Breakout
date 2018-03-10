#include "render.h"
#include "input.c"
#include "events.h"
#include <osbind.h>
#include <stdio.h>
#include <string.h>

UINT8 buffer2[38256];

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
	int difference;

	base = buffer;

	difference = (int) buffer;
  difference %= 256;
	difference = 256 - difference;
	base += difference;
	return base;
}

UINT32 *get_base32(UINT8 buffer[])
{
	UINT32 *base;
	int difference;

	base = (UINT32 *) buffer;

	difference = (int) buffer;
  difference %= 256;
	difference = 256 - difference;
	base += difference;
	return base;
}
/*
	bool swap

	while(!gameOver)
	{
		asynch_events
		if(clock_tick)
		{
			synch_events
		}


		Vsync()
		render()
		if(swap) --swaps to the back buffer
		{
			set_screen(screen1)
			base = screen2
		}
		else
		{
			set_screen(screen2)
			base = screen1
		}
	}
*/

int main()
{
	UINT8 *base8 = (UINT8 *) Physbase();
	UINT16 *base16 = (UINT16 *) Physbase();
	UINT32 *base32 = (UINT32 *) Physbase();

	UINT8 *base8_2 = get_base(buffer2);
	UINT32 *base32_2 = get_base32(buffer2);

	long input = 0;
	unsigned long timeThen, timeNow, timeElapsed = 0;
	Model game;
	start_game(&game);
	game.paddle.speed = 10;
	/*etscreen(-1, base8_2, -1);*/

	simple_render(base8, base32, &game);
	game.paddle.direction = 1;


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
		}

		simple_render(base8, base32, &game);
		Vsync();


	}

	return 0;
}
