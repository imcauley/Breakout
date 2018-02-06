#include <stdlib.h>
#include "model.h"

void move_ball(Ball *ball, Brick *bricks)
{
    if (ball->position->y )
    ball->position->x += ball->x_speed * ball->x_direction;
    ball->position->y += ball->y_speed * ball->y_direction;
}

bool ball_collides(Ball *ball, Brick *bricks, Paddle *paddle)
{
    return False;
}

void move_paddle(Paddle *paddle)
{
    paddle->position->x += paddle->speed * paddle->direction;
}

void launch_ball(Paddle *paddle, Ball *ball)
{
    int random = rand() % 2;
    ball->position->x = paddle->posiiton->x + (1.0/2.0) * paddle->width;
    ball->position->y = paddle->position->y + 8         /* 8 being balls height */
    ball->x_speed = 10;
    ball->y_speed = 10;
    ball->y_direction = 1;
    ball->x_direction = random;
}