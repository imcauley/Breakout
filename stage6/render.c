#include <osbind.h>
#include "render.h"

#define BOARD_START 40
#define BRICK_HEIGHT 16
#define BRICK_WIDTH 32
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400



void render(Model *game, Model *snap)
{
	UINT8 *base8 = (UINT8 *) Physbase();
	UINT32 *base32 = (UINT32 *) Physbase();
	int col, row;
	
	render_clear(snap);
	render_paddle(base32, &((*game).paddle));
	render_ball(base8, &((*game).ball));
	for(row = 0; row < BRICK_ROWS; row++)
	{
		for(col =0; col < BRICK_COLS; col++)
		{
			if(((*game).bricks[row][col].broken) && !((*snap).bricks[row][col].broken))
			{
				remove_brick(base32, row, col);
			}
		}
	}
}

void start_render(Model *game)
{
	UINT8 *base8 = (UINT8 *) Physbase();
	UINT16 *base16 = (UINT16 *) Physbase();
	UINT32 *base32 = (UINT32 *) Physbase();
	
	clear_screen(base32);
	render_bricks(base32, (*game).bricks);
	render_paddle(base32, &((*game).paddle));
	render_ball(base8, &((*game).ball));
	
}

void render_clear(Model *game)
{
	UINT8 *base8 = (UINT8 *) Physbase();
	UINT32 *base32 = (UINT32 *) Physbase();
	
	Paddle *paddle = &(game->paddle);
	Ball *ball = &(game->ball);
	
	draw_64rect(base32, paddle->x, paddle->y, paddle->height, True);
	draw_8rect(base8, ball->x, ball->y, ball->height, True);
}

void render_paddle(UINT32 *base, Paddle *paddle)
{
	draw_64rect(base, paddle->x, paddle->y, paddle->height, False);
}

void render_ball(UINT8 *base, Ball *ball)
{
	draw_8rect(base, ball->x, ball->y, ball->height, False);
}

void render_bricks(UINT32 *base, Brick bricks[][])
{

    int r, c;
    
    UINT32 brick_bitmap[BRICK_HEIGHT] =
    {
        0xFFFFFFFF,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0xFFFFFFFF
    };
    
    
    for(r = 0; r < BRICK_ROWS; r++)
    {
        for(c = 0; c < BRICK_COLS; c++)
        {
            if(True)
            {
                plot_bitmap_32(base, (c*BRICK_WIDTH), ((r*BRICK_HEIGHT) + BOARD_START), 
                    brick_bitmap, BRICK_HEIGHT);
            }
        }
    }

    
}

void remove_brick(UINT32 *base, int row, int col)
{
	UINT32 clear_bitmap[BRICK_HEIGHT] =
	{
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF
	};
	
	plot_bitmap_32(base, (col*BRICK_WIDTH), ((row*BRICK_HEIGHT) + BOARD_START), 
                    clear_bitmap, 16);
}

void render_hud(UINT8 *base8, Header *header, Lives *lives, Score *score)
{
	plot_char(base8, 2, 16, 35);
	plot_char(base8, 3, 16, 19);
	plot_char(base8, 4, 16, 31);
	plot_char(base8, 5, 16, 34);
	plot_char(base8, 6, 16, 21);
	
	plot_char(base8, 8, 16, 0);
	plot_char(base8, 9, 16, 0);
	plot_char(base8, 10, 16, 0);
	plot_char(base8, 11, 16, 0);
}