#include "model.h"
#include <osbind.h>
#include <stdio.h>

#define RETURN	0x001C000DL

void asynch_events(Paddle *paddle, Ball *ball)
{
    /*if (left_pressed)
        paddle->direction = -1;
    
    else if (right_pressed)
        paddle->direction = 1;
    
    else
        paddle->direction = 0;
    
    if (space_pressed)
        ball->launch = True;*/
}

void synch_events(Paddle *paddle, Ball *ball, Brick *bricks)
{
    launch_ball(paddle,ball);
    move_ball(ball, bricks, paddle);
    move_paddle(paddle);
}

void condition_events(Paddle *paddle, Ball *ball, Brick *bricks)
{
    ball_collides(ball,bricks,paddle);
}

void run(Paddle *paddle, Ball *ball, Brick *bricks)
{
    long in;
    in = Cnecin();
    printf("%d", in);
    
    while(in != RETURN)
    {
        asynch_events(paddle, ball);
        synch_events(paddle,ball,bricks);
        condition_events(paddle,ball,bricks);
        in = Cnecin();
    }
    return;
}