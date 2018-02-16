#include <stdlib.h>
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
    
    if (ball->y  <= paddle->y && paddle->x <= ball->x <= paddle->x + paddle->width)     /* collision with paddle */
    {    
        ball->y_direction = -1;
        return True;
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
    
    /*if ((ball->y) <= ((bricks + y*BRICK_COLS + x)->height * BRICK_ROWS))
    {
        for (x = 0; x < BRICK_ROWS; x++)
        {
            for (y = 0; y < BRICK_COLS; y++)
            {
                if ((bricks + y*BRICK_COLS + x)->broken == False)
                {
                    if (ball->y + ball->height == (bricks + y*BRICK_COLS + x)->y)           collision with top of a brick 
                    {
                        ball->y_direction *= -1;
                        return True;
                    }
                    
                    if (ball->y == (bricks + y*BRICK_COLS + x)->y + (bricks + y*BRICK_COLS + x)->height)  collision with bottom of a brick 
                    {
                        ball->y_direction *= -1;
                        return True;
                    }   
                    
                    if (ball->x + ball->width == (bricks + y*BRICK_COLS + x)->x)            collision with left of a brick 
                   
                        ball->x_direction *= -1;
                        return True;
                    }
                    
                    if (ball->x == (bricks + y*BRICK_COLS + x)->x + (bricks + y*BRICK_COLS + x)->width)    collision with right of a brick 
                    {
                        ball->x_direction *= -1;
                        return True;
                    }
                }
            }
        }*/
    
    
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
        paddle->x = 0;
        return True;
    }
	else if ((paddle->x + paddle->width) >= 640)
	{
		paddle->x = 640 - paddle->width;
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
