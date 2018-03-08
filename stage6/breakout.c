#include "render.h"
#include "input.c"
#include "events.h"
#include <osbind.h>
#include <stdio.h>
#include <string.h>

unsigned long get_time()
{
	unsigned long *timer = (long *)0x462;	/* address of longword auto-inc’ed 70 x per s */
	unsigned long timeNow;
	long old_ssp;
	old_ssp = Super(0);				/* enter privileged mode */
	timeNow = *timer;
	Super(old_ssp); 				/* exit privileged mode as soon as possible */
	return timeNow;
}

int main()
{
	UINT8 *base8 = (UINT8 *) Physbase();
	UINT16 *base16 = (UINT16 *) Physbase();
	UINT32 *base32 = (UINT32 *) Physbase();
	long input;
	unsigned long timeThen, timeNow, timeElapsed = 0;
	Model game;
	/*start_game(&game);
	start_render(&game);*/
	game.paddle.speed = 3;
	
	while(input != 0x00100071)
	{
		timeNow = get_time();
		timeElapsed = timeNow - timeThen;
		printf ("%ld\n", timeElapsed);
		printf("\ntest0\n");
		/*render(&game);*/
		if(!key_pressed())
		{
			printf("\ntest1\n");
			input = get_input();
			printf("\ntest2\n");
			asynch_events(&game.paddle, &game.ball, input);
			printf("\ntest3\n");
		}
		if (timeElapsed > 0)
		{
			printf("\ntest4\n");
			synch_events(&game.paddle, &game.ball, &game.bricks);
			printf("\ntest5\n");
			timeThen = timeNow;
			printf("\ntest6\n");
		}
		/*memcpy(&snap,&game,sizeof(game));*/

	}
	return 0;
}