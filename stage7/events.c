/*=========================================

Source File:
events.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/

#include "model.h"
#include "events.h"
#include <osbind.h>
#include <stdio.h>
#include "effects.h"

#define RETURN	0x001C000DL
#define LEFT 	0x4b
#define RIGHT	0x4d
#define SPACE	0x39

#define REVERSE	 -1
#define NUM_LIVES 3

#define SCREEN_WIDTH 640
#define HEADER_HEIGHT 40

/*=== asynch_events ===========================================================

Purpose: process any asynchronous events

Inputs:
	*paddle  -  pointer to model paddle
	*ball 	 -  pointer to model ball
	input	 -  longword of keyboard input

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

void asynch_events(Paddle *paddle, Ball *ball, UINT8 input)
{
	if (input == LEFT)
		paddle->direction = -1;

	else if (input == RIGHT)
		paddle->direction = 1;

	if (input == SPACE)
	{
        ball->launch = True;
		launch_ball(paddle, ball);
	}
}

/*=== synch_events ===========================================================

Purpose: process all syncronous events

Inputs:     
	*paddle  -  pointer to model paddle
	*ball 	 -  pointer to model ball
	bricks	 -  pointer to list of bricks

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/


void synch_events(Paddle *paddle, Ball *ball, Brick bricks[][])
{
    launch_ball(paddle,ball);
    move_ball(ball, paddle);
    move_paddle(paddle);
    paddle->direction = 0;
}

/*=== condition_events ===========================================================

Purpose: process all cascading events

Inputs:
	*paddle: pointer to the paddle
	*ball:   pointer to the ball
	bricks:  the array of bricks
	*score:  pointer to the score
	*lives:  pointer to the lives

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void condition_events(Paddle *paddle, Ball *ball, Brick bricks[][], Score *score, Lives *lives)
{
	char block_collision;

	if (paddle_collides(paddle))
    {
		paddle->direction *= -1;
		move_paddle(paddle);
	}

	else if (ball_collides_paddle(ball, paddle))
	{
		ball->y_direction *= REVERSE;
		ball->y = (paddle->y - ball->height);
		if (ball->launched)
			play_bounce();
	}

	else if (ball_collides_bottom(ball))
	{
		die(ball, lives);
	}

    else if (ball_collides_left(ball))
	{
		ball->x = 0;
		ball->x_direction *= REVERSE;
		play_bounce();
	}
	else if (ball_collides_right(ball))
	{
		ball->x = (SCREEN_WIDTH-2) - ball->width;
		ball->x_direction *= REVERSE;
		play_bounce();
	}
	else if (ball_collides_top(ball))
	{
		ball->y = (HEADER_HEIGHT + 1);
		ball->y_direction *= REVERSE;
		play_bounce();
	}
	block_collision = ball_collides_bricks(ball, bricks, score);     /* x or y for collisions */
	if (block_collision == 'x')
	{
		ball->x_direction *= REVERSE;
		play_brick_destroyed();
	}
	else if (block_collision == 'y')
	{
		ball->y_direction *= REVERSE;
		play_brick_destroyed();
	}
    
    if (game_over(lives))
        lives->game_over = True;
}

/*=== die ===========================================================

Purpose: removes a life in the model and resets ball

Inputs:     
	*ball	 -	pointer to ball
	*lives	 -  pointer to models lives

Outputs:
	None

Limitations/Known bugs: N/A
=============================================================================*/


void die(Ball *ball, Lives *lives)
{
	int i;
	for(i = 0; i < NUM_LIVES; i++)
	{
		if(lives->lives[i] == True)
		{
			lives->lives[i] = False;
			ball->launch = False;
			ball->launched = False;
			break;
		}
	}
}
