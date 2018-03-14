#include "model.h"
#include <osbind.h>
#include <stdio.h>

#define RETURN	0x001C000DL
#define LEFT 	0x004b0000L
#define RIGHT	0x004d0000L
#define SPACE	0x00390020L

void asynch_events(Paddle *paddle, Ball *ball, long input)
{
	if (input == LEFT)
		paddle->direction = -1;

	else if (input == RIGHT)
		paddle->direction = 1;

	if (input == SPACE)
        ball->launch = True;
}

void synch_events(Paddle *paddle, Ball *ball, Brick bricks[][])
{
    launch_ball(paddle,ball);
    move_ball(ball, bricks, paddle);
    move_paddle(paddle);
    paddle->direction = 0;
}

void condition_events(Paddle *paddle, Ball *ball, Brick bricks[][], Score *score)
{
	char block_collision;

	if (paddle_collides(paddle))
    {
		paddle->direction *= -1;
		move_paddle(paddle);
	}

	else if (ball_collides_paddle(ball, bricks, paddle))
	{
		ball->y_direction *= -1;
		ball->y = (paddle->y - ball->height);
	}

	else if (ball_collides_bottom(ball, bricks, paddle))
	{
		ball->y = 400 - ball->height;
		ball->y_direction *= -1;
	}

  else if (ball_collides_left(ball))
	{
		ball->x = 0;
		ball->x_direction *= -1;
	}
	else if (ball_collides_right(ball))
	{
		ball->x = 638 - ball->width;
		ball->x_direction *= -1;
	}
	else if (ball_collides_top(ball, bricks, paddle))
	{
		ball->y = 41;
		ball->y_direction *= -1;
	}
	block_collision = ball_collides_bricks(ball, bricks, paddle, score);     /* x or y for collisions */
	if (block_collision == 'x')
	{
		ball->x_direction *= -1;
	}
	else if (block_collision == 'y')
	{
		ball->y_direction *= -1;
	}
}
