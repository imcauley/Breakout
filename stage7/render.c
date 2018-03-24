/*=========================================

Source File:
render.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/


#include <osbind.h>
#include "render.h"

#define BOARD_START 40
#define BRICK_HEIGHT 16
#define BRICK_WIDTH 32
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

/*=== simple_render ===========================================================

Purpose: renders an entire frame from a given model

Inputs:
	*base8 	 -	8 bit width of the frame buffer
	*base 32 -  32 bit width of the frame buffer
	*game	 - 	current model of game

Outputs: 
	None

Limitations/Known bugs:
	- Too slow to use for every frame
	
=============================================================================*/

void simple_render(UINT8 *base8, UINT32 *base32, Model *game)
{
	clear_screen(base32);
	render_bricks(base32, (*game).bricks);
	render_paddle(base32, &((*game).paddle));
	render_ball(base8, &((*game).ball));
	render_hud(base8, &((*game).header), &((*game).lives), &((*game).score));
}

/*=== title ===========================================================

Purpose:

Inputs:     

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

void render(UINT8 *base8, UINT32 *base32, Model *game)
{
    if (game->lives.game_over == True)
    {
        clear_screen(base32);
        render_game_over(base8, &(game->score));
    }
    else
	{
        render_paddle(base32, &((*game).paddle));
        render_ball(base8, &((*game).ball));
        render_hud(base8, &((*game).header), &((*game).lives), &((*game).score));
    }
}

/*=== title ===========================================================

Purpose:

Inputs:     

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

void start_render(UINT32 *base32, Model *game)
{
	int x;
	clear_screen(base32);
	render_bricks(base32, (*game).bricks);
	for(x = 780; x < 800; x++)
	{
		*(base32 + (x)) = 0x00000000;
	}
}

/*=== title ===========================================================

Purpose:

Inputs:     

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

void render_clear(UINT8 *base8, UINT32 *base32, Model *game)
{
	Paddle *paddle = &(game->paddle);
	Ball *ball = &(game->ball);

	draw_64rect(base32, paddle->x, paddle->y, paddle->height, True);
	draw_8rect(base8, ball->x, ball->y, ball->height, True);
}

/*=== title ===========================================================

Purpose:

Inputs:     

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

void render_paddle(UINT32 *base, Paddle *paddle)
{
	draw_64rect(base, paddle->x, paddle->y, paddle->height, False);
}

/*=== title ===========================================================

Purpose:

Inputs:     

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

void render_ball(UINT8 *base, Ball *ball)
{
	draw_8rect(base, ball->x, ball->y, ball->height, False);
}

/*=== title ===========================================================

Purpose:

Inputs:     

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/


void render_bricks(UINT32 *base, Brick bricks[BRICK_ROWS][BRICK_COLS])
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
            if(!(bricks[r][c]).broken)
            {
                plot_bitmap_32(base, (c*BRICK_WIDTH), ((r*BRICK_HEIGHT) + BOARD_START),
                    brick_bitmap, BRICK_HEIGHT);
            }
			else
			{
				remove_brick(base, r, c);
			}
        }
    }


}

/*=== title ===========================================================

Purpose:

Inputs:     

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/


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

/*=== title ===========================================================

Purpose:

Inputs:     

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/


void render_hud(UINT8 *base8, Header *header, Lives *lives, Score *score)
{
	plot_char(base8, 2, 16, 35);
	plot_char(base8, 3, 16, 19);
	plot_char(base8, 4, 16, 31);
	plot_char(base8, 5, 16, 34);
	plot_char(base8, 6, 16, 21);

	plot_char(base8, 8, 16, (score->score[3]));
	plot_char(base8, 9, 16, (score->score[2]));
	plot_char(base8, 10, 16, (score->score[1]));
	plot_char(base8, 11, 16, (score->score[0]));

	plot_char(base8, 65, 16, 28);
	plot_char(base8, 66, 16, 25);
	plot_char(base8, 67, 16, 38);
	plot_char(base8, 68, 16, 21);
	plot_char(base8, 69, 16, 35);

	if(lives->lives[0] == True)
	{
		plot_char(base8, 71, 16, 40);
	}
	if(lives->lives[1] == True)
	{
		plot_char(base8, 72, 16, 40);
	}
	if(lives->lives[2] == True)
	{
		plot_char(base8, 73, 16, 40);
	}
}


/*=== title ===========================================================

Purpose:

Inputs:     

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/


void render_game_over(UINT8 *base8, Score *score)
{
    plot_char(base8, 36, 200, 23);      /*game*/
    plot_char(base8, 37, 200, 17);
    plot_char(base8, 38, 200, 29);
    plot_char(base8, 39, 200, 21);
    
    plot_char(base8, 41, 200, 31);      /*over*/
    plot_char(base8, 42, 200, 38);
    plot_char(base8, 43, 200, 21);
    plot_char(base8, 44, 200, 34);
    
    plot_char(base8, 35, 215, 22);      /*final*/
    plot_char(base8, 36, 215, 25);
    plot_char(base8, 37, 215, 30);
    plot_char(base8, 38, 215, 17);
    plot_char(base8, 39, 215, 28);
    
    plot_char(base8, 41, 215, 35);        /*score:*/
	plot_char(base8, 42, 215, 19);
	plot_char(base8, 43, 215, 31);
	plot_char(base8, 44, 215, 34);
	plot_char(base8, 45, 215, 21);
    plot_char(base8, 46, 215, 10);
    
    plot_char(base8, 38, 240, (score->score[3]));
	plot_char(base8, 39, 240, (score->score[2]));
	plot_char(base8, 40, 240, (score->score[1]));
	plot_char(base8, 41, 240, (score->score[0]));
}  
