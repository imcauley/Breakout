#include <stdlib.h>
#include <stdio.h>
#include "model.h"

#define BRICK_ROWS 5
#define BRICK_COLS 20

void start_game(Model *game)
{
	create_bricks((*game).bricks);
	(*game).paddle.x = 0;
	(*game).paddle.y = 380;
	(*game).paddle.height = 16;
	(*game).paddle.speed = 3;
	
	(*game).ball.x = 0;
	(*game).ball.y = 370;
	(*game).ball.height = 8;
}

void create_bricks(Brick bricks[BRICK_ROWS][BRICK_COLS])
{
	int r,c = 0;
	
	for(r=0;r < BRICK_ROWS;r++)
	{
		for(c=0;c < BRICK_COLS; c++)
		{
			(bricks[r][c]).x = (r * 20);
			(bricks[r][c]).y = c * BRICK_ROWS;
			(bricks[r][c]).broken = False;
			(bricks[r][c]).width = 32;
			(bricks[r][c]).height = 16;
		}
	}
}

void move_ball(Ball *ball, Brick *bricks, Paddle *paddle)
{
        ball->x += ball->x_speed * ball->x_direction;
        ball->y += ball->y_speed * ball->y_direction;
               
        ball_collides(ball, bricks, paddle);
}

bool ball_collides(Ball *ball, Brick bricks[BRICK_ROWS][BRICK_COLS], Paddle *paddle)
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
    
    if (ball->y <= 120)                                   
    {
        unsigned int x_pos = ball-> x / 32;
        unsigned int y_pos = ball-> y / 16;
        
        if (bricks[x_pos][y_pos].broken == False)
        {
            bricks[x_pos][y_pos].broken = True;
            
            if (ball->y <= bricks[x_pos][y_pos].y + bricks[x_pos][y_pos].height ||
                ball->y + ball->height >= bricks[x_pos][y_pos].y) 
                ball->y_direction *= -1;
            else
                ball->x_direction *= -1;
            return True;
        }
    }
    
    /*if ((ball->y) <= 120)
    {
        for (x = 0; x < BRICK_ROWS; x++)
        {
            for (y = 0; y < BRICK_COLS; y++)
            {
                if (bricks[x][y].broken == False)
                {
                    if (ball->y + ball->height == (bricks[x][y].y))       
                    {
                        bricks[x][y].broken = True;
                        ball->y_direction *= -1;
                        return True;
                    }
                    
                    if (ball->y == (bricks[x][y].y + (bricks[x][y].height)))  
                    {
                        bricks[x][y].broken = True;
                        ball->y_direction *= -1;
                        return True;
                    }   
                    
                    if (ball->x + ball->width == (bricks[x][y].x))        
                    {
                        bricks[x][y].broken = True;
                        ball->x_direction *= -1;
                        return True;
                    }
                    
                    if (ball->x == (bricks[x][y].x + (bricks[x][y].width)))   
                    {
                        bricks[x][y].broken = True;
                        ball->x_direction *= -1;
                        return True;
                    }
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
    if ((paddle->x) < 0)       /* collision with side walls */
    {
        (paddle->x) = 0;
        return True;
    }
    
	else if ((paddle->x + paddle->width) > 640)
	{
		paddle->x = (640 - paddle->width);
		return True;
	}
    return False;
}
        
void launch_ball(Paddle *paddle, Ball *ball)
{
    if (ball->launch == True && ball->launched == False)
    {
        int random = rand() % 2;
        ball->x = paddle->x + (1.0/2.0) * paddle->width;
        ball->y = paddle->y + ball->height;
        ball->x_speed = 10;
        ball->y_speed = 10;
        ball->y_direction = 1;
        ball->x_direction = random;
        ball->launch = False;
        ball->launched = True;
    }
}
