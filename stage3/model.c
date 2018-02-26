#include <stdlib.h>
#include <stdio.h>
#include "model.h"

void move_ball(Ball *ball, Brick bricks[], Paddle *paddle)
{
        ball->x += ball->x_speed * ball->x_direction;
        ball->y += ball->y_speed * ball->y_direction;
        
        if (ball_collides(ball, bricks, paddle))
        {
                move_ball(ball, bricks, paddle);         /* collision occurred, this will move ball back 
                                                            with direction reversed */
        }
}

bool ball_collides(Ball *ball, Brick *bricks, Paddle *paddle)
{
    int x;
    int y;
    
    if (ball->y  <= paddle->y)
    {
		if((ball->x >= paddle->x) && (ball->x <= (paddle->x + paddle->width))) 
		{
			ball->y_direction = -1;
			return True;
		}
    }
	
    if (ball->x <= 0 || ball->x + ball->width >= 640)       /* collision with side walls */
    {
        ball->x_direction *= -1;
        return True;
    }
    
    if (ball->y <= 0 || ball->y + ball->height >= 400)      /* collision with top/bottom walls */
    {
        ball->y_direction *= -1;
        return True;
    }
	
    return False;
}

void move_paddle(Paddle *paddle)
{
	paddle->x += (paddle->speed * paddle->direction);
    paddle_collides(paddle);
}

bool paddle_collides(Paddle *paddle)
{
    if ((paddle->x) <= 0)       /* collision with side walls */
    {
        (paddle->x) = 0;
        return True;
    }
	else if ((paddle->x + paddle->width) >= 640)
	{
		paddle->x = (640 - paddle->width);
		return True;
	}
    return False;
}
        
void launch_ball(Paddle *paddle, Ball *ball)
{
    int random = rand() % 2;
    ball->x = paddle->x + (1.0/2.0) * paddle->width;
    ball->y = paddle->y + ball->height;
    ball->x_speed = 10;
    ball->y_speed = 10;
    ball->y_direction = 1;
    ball->x_direction = random;
}
