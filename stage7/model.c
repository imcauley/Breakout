/*=========================================

Source File:
model.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/


#include <stdlib.h>
#include <stdio.h>
#include "model.h"

#define BRICK_ROWS      5
#define BRICK_COLS      20
#define SCREEN_HEIGHT   400
#define SCREEN_WIDTH    640
#define SCREEN_START    0
#define HEADER_HEIGHT   40
#define NUM_LIVES       3
#define BRICKS_START    120
#define BRICK_WIDTH     32
#define BRICK_HEIGHT    16

void start_game(Model *game)
{
	create_bricks((*game).bricks);
	(*game).paddle.x = 200;
	(*game).paddle.y = 380;
	(*game).paddle.height = 16;
	(*game).paddle.speed = 16;
	(*game).paddle.direction = 1;
	(*game).paddle.width = 64;

	(*game).ball.x = 200;
	(*game).ball.y = 370;
	(*game).ball.height = 8;

	(*game).score.score[0] = 0;
	(*game).score.score[1] = 0;
	(*game).score.score[2] = 0;
	(*game).score.score[3] = 0;

	(*game).ball.width = 8;
	(*game).ball.x_speed = 7;
	(*game).ball.y_speed = 7;
	(*game).ball.x_direction = 1;
	(*game).ball.y_direction = 1;
	(*game).ball.launch = False;
	(*game).ball.launched = False;
    
    (*game).lives.game_over = False;
	(*game).lives.lives[0] = True;
	(*game).lives.lives[1] = True;
	(*game).lives.lives[2] = True;
}

bool game_over(Lives *lives)
{
    int i;
    bool over = True;
    
    for(i = 0; i < NUM_LIVES; i++)
	{
		if(lives->lives[i] == True)
			over = False;
	}
    
    return over;
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
			(bricks[r][c]).width = BRICK_WIDTH;
			(bricks[r][c]).height = BRICK_HEIGHT;
		}
	}
}

void move_ball(Ball *ball, Brick bricks[][], Paddle *paddle)
{
	if(ball->launched == True)
	{
        ball->x += ball->x_speed * ball->x_direction;
        ball->y += ball->y_speed * ball->y_direction;
	}
	else
	{
		ball->x = paddle->x + (1.0/2.0) * paddle->width;
		ball->y = paddle->y + ball->height;
	}
}

bool ball_collides_left(Ball *ball)
{
	if(ball->x <= SCREEN_START)
	{
		return True;
	}
		return False;
}

bool ball_collides_right(Ball *ball)
{
	if(ball->x >= SCREEN_WIDTH)
	{
		return True;
	}
		return False;
}


bool ball_collides_top(Ball *ball, Brick bricks[BRICK_ROWS][BRICK_COLS], Paddle *paddle)
{
    if (ball->y <= HEADER_HEIGHT)
        return True;
	else
		return False;
}

bool ball_collides_bottom(Ball *ball, Brick bricks[BRICK_ROWS][BRICK_COLS], Paddle *paddle)
{
    if (ball->y + ball->height >= SCREEN_HEIGHT)      /* collision with top/bottom walls */
		return True;
	else
		return False;
}


bool ball_collides_paddle(Ball *ball, Brick bricks[BRICK_ROWS][BRICK_COLS], Paddle *paddle)
{
	if (ball->y + ball->height >= paddle->y && (ball->x + ball->width) >= paddle->x
													     && ball->x <= (paddle->x + paddle->width))
		return True;
	else
		return False;
}


char ball_collides_bricks(Ball *ball, Brick bricks[BRICK_ROWS][BRICK_COLS], Paddle *paddle, Score *score)
{
    if (ball->y < BRICKS_START)
    {
        int x_pos = ball-> x / BRICK_WIDTH;
        int y_pos = (ball->y - HEADER_HEIGHT)/ BRICK_HEIGHT;

        if (bricks[y_pos][x_pos].broken == False)
        {
            bricks[y_pos][x_pos].broken = True;
			add_score(score);

            if (ball->y <= bricks[y_pos][x_pos].y + bricks[y_pos][x_pos].height ||
                ball->y + ball->height >= bricks[y_pos][x_pos].y)
                return 'y';

            else
                return 'x';
        }
    }

    return '0';
}
void move_paddle(Paddle *paddle)
{
	paddle->x += (paddle->speed * paddle->direction);
}

bool paddle_collides(Paddle *paddle)
{
    if ((paddle->x) < SCREEN_START)       /* collision with side walls */
    {
        (paddle->x) = SCREEN_START;
        return True;
    }

	else if ((paddle->x + paddle->width) > SCREEN_WIDTH -1)
	{
		paddle->x = (SCREEN_WIDTH - paddle->width - 1);
		return True;
	}
    return False;
}

void launch_ball(Paddle *paddle, Ball *ball)
{
    if (ball->launch == True && ball->launched == False)
    {
        int random = rand() % 2;
		if(random == 0)
			random = -1;
        ball->x_speed = 7;
        ball->y_speed = 7;
        ball->y_direction = 1;
        ball->x_direction = random;
        ball->launch = False;
        ball->launched = True;
    }
}

void add_score(Score *score)
{
	int x;
	for(x = 0; x < 4; x++)
	{
		if(score->score[x] == 9)
		{
			score->score[x] = 0;
		}
		else
		{
			(score->score[x])++;
			break;
		}
	}
}
