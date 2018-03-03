#include <osbind.h>
#include "render.h"

#define BOARD_START 40
#define BRICK_HEIGHT 16
#define BRICK_WIDTH 32
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

void render(Model *game)
{
	UINT16 *base16 = (UINT16 *) Physbase();
	UINT32 *base32 = (UINT32 *) Physbase();
	clear_screen(base16);
	render_bricks(base32, (*game).bricks);
	render_paddle(&((*game).paddle));
	render_ball(&((*game).ball));
}

void render_paddle(Paddle *paddle)
{}
void render_ball(Ball *ball)
{}
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
                    brick_bitmap, 16);
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
void render_hud(Header *header, Lives *lives, Score *score)
{}