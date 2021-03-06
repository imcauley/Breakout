#include "render.h"
#include "model.h"
#include "input.c"
#include <osbind.h>

int main()
{
	UINT8 *base8 = (UINT8 *) Physbase();
	UINT32 *base32 = (UINT32 *) Physbase();
	long test;
	Model game;
	start_game(&game);
	start_render(&game);
	while(test != 0x00100071)
	{
		render(&game);
		if(key_pressed())
		{
			input = get_input();
			if(input = 0x004b0000)
			{
				game.paddle.direction = -1;
				move_paddle(&(game.paddle));
			}
			else if(input = 0x004d0000)
			{
				game.paddle.direction = 1;
				move_paddle(&(game.paddle));
			}
			else
			{
				game.paddle.direction = 0;
			}
		}
	}
	return 0;
}