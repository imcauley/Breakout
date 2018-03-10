#include "model.h"
#include <osbind.h>
#include <stdio.h>

#define RETURN	0x001C000DL

void asynch_events(Paddle *paddle, Ball *ball, long input)
{
  if (input == 0x004b0000)
    paddle->direction = -3;

  else if (input == 0x004d0000)
    paddle->direction = 3;



    if (input == 0x00390020)
        ball->launch = True;
}

void synch_events(Paddle *paddle, Ball *ball, Brick bricks[][])
{
    /*launch_ball(paddle,ball);*/
    /*move_ball(ball, bricks, paddle);*/
    move_paddle(paddle);
    paddle->direction = 0;
}

void condition_events(Paddle *paddle, Ball *ball, Brick bricks[][])
{
    ball_collides(ball,bricks,paddle);
}
