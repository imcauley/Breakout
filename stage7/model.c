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
#include <time.h>
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

/*=== game_over ===========================================================

Purpose: checks if the user has run out of lives

Inputs:
	lives: pointer array of lives

Outputs:
	over: bool of whether the game is over or not

Limitations/Known bugs: N/A
=============================================================================*/

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

/*=== create_bricks =========================================================

Purpose: Initializes the array of bricks

Inputs:
	bricks: array of bricks

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

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

/*=== move_ball ===========================================================

Purpose: Updates the balls position based on its speed and direction,
		 or along the paddle if the ball hasn't been launched yet.

Inputs:
	*ball: 		pointer to the ball
	*paddle:	pointer to the paddle

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void move_ball(Ball *ball, Paddle *paddle)
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

/*=== ball_collides_left ======================================================

Purpose: Checks if the ball has collided with the left wall.

Inputs:
	*ball: 	pointer to the ball

Outputs:
	True if it has collided, false otherwise.

Limitations/Known bugs: N/A
=============================================================================*/

bool ball_collides_left(Ball *ball)
{
	if(ball->x <= SCREEN_START)
	{
		return True;
	}
		return False;
}

/*=== ball_collides_right =====================================================

Purpose: Checks if the ball has collided with the right wall.

Inputs:
	*ball: pointer to the ball

Outputs:
	True if it has collided, false otherwise.

Limitations/Known bugs: N/A
=============================================================================*/

bool ball_collides_right(Ball *ball)
{
	if(ball->x >= SCREEN_WIDTH)
	{
		return True;
	}
		return False;
}

/*=== ball_collides_top =======================================================

Purpose: Checks if the ball has collided with the top of the screen
		 (Ie the header)

Inputs: 
	*ball: pointer to the ball

Outputs:
	True if it has collided, false otherwise.

Limitations/Known bugs: N/A
=============================================================================*/

bool ball_collides_top(Ball *ball)
{
    if (ball->y <= HEADER_HEIGHT)
        return True;
	else
		return False;
}

/*=== ball_collides_bottom ====================================================

Purpose: Checks if the ball has collided with the bottom of the screen

Inputs:
	*ball: pointer to the ball

Outputs:
	True if it collided, false otherwise.
	
Limitations/Known bugs: N/A
=============================================================================*/

bool ball_collides_bottom(Ball *ball)
{
    if (ball->y + ball->height >= SCREEN_HEIGHT)
		return True;
	else
		return False;
}

/*=== ball_collides_paddle ====================================================

Purpose: Checks if the ball has collided with the paddle

Inputs:
	*ball: 		pointer to the ball
	*paddle:	pointer to the paddle

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

bool ball_collides_paddle(Ball *ball, Paddle *paddle)
{
	if (ball->y + ball->height >= paddle->y && 
	   (ball->x + ball->width) >= paddle->x && 
	    ball->x <= (paddle->x + paddle->width))
		return True;
	else
		return False;
}

/*=== ball_collides_bricks ===================================================

Purpose: Checks if the ball has collided with a brick, if it has the score is
		 updated and the brick is set to broken.

Inputs:
	*ball: 		pointer to the ball
   bricks:		the array of bricks
   *score:		pointer to the score
   
Outputs:
	Returns 'y' if it was a vertical collision, 'x' if it was a horizontal
	collision, '0' if no collision.

Limitations/Known bugs: N/A
=============================================================================*/

char ball_collides_bricks(Ball *ball, Brick bricks[BRICK_ROWS][BRICK_COLS], Score *score)
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

/*=== move_paddle ===========================================================

Purpose: Updates the paddles position based on its speed and direction

Inputs:
	*paddle: pointer to the paddle

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void move_paddle(Paddle *paddle)
{
	paddle->x += (paddle->speed * paddle->direction);
}

/*=== paddle_collides ===========================================================

Purpose: Checks if the paddle has collided with a wall, if it has it moves the
		 paddle back to before the wall.

Inputs:
	*paddle: pointer to the paddle

Outputs:
	True if the paddle collided, false otherwise.

Limitations/Known bugs: N/A
=============================================================================*/

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

/*=== launch_ball ===========================================================

Purpose: Launches the ball from the paddle if it wasn't already launched.

Inputs:
	*paddle: pointer to the paddle
	*ball:   pointer to the ball

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void launch_ball(Paddle *paddle, Ball *ball)
{
	srand(time(NULL));
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

/*=== add_score ===========================================================

Purpose: increments the score

Inputs:
	*score: pointer to the score

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

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
