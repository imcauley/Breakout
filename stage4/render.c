#include <osbind.h>
#include "render.h"

#define BOARD_START 40
#define BRICK_HEIGHT 16
#define BRICK_WIDTH 32

int main()
{
    UINT16 *base = (UINT16 *) Physbase();
    clear_screen(base);
    Model tester;
    create_bricks(tester.bricks[][]);
}

void render(Model *game)
{
	render_bricks(game->bricks[][]);
}

void render_paddle(Paddle *paddle)
{}
void render_ball(Ball *ball)
{}
void render_bricks(Brick bricks[][])
{
    int r, c;
    UINT32 *base = (UINT32 *) Physbase();
    
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

void render_hud(Header *header, Lives *lives, Score *score)
{}