#include <osbind.h>
#include "model.h"
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BRICK_HEIGHT 16

int main()
{
    Model tester;
    int c,r,total = 0;
 
    /* successful paddle move */	

    tester.paddle.x = 0;
    tester.paddle.y = 350;
    tester.paddle.speed = 1;
    tester.paddle.direction = 1;
    tester.paddle.width = 60;
    tester.paddle.height = 40;

    move_paddle(&(tester.paddle));
    printf("paddle X should be 1: %i \n", tester.paddle.x);
	
	/* paddle hits left wall */
	tester.paddle.x = 0;
    tester.paddle.y = 0;
    tester.paddle.speed = 2;
    tester.paddle.direction = -1;
    tester.paddle.width = 60;
    tester.paddle.height = 40;
    
    move_paddle(&(tester.paddle));
    printf("paddle x should be 0: %i \n", tester.paddle.x);
	
	/* paddle hits right wall */
	tester.paddle.x = 580;
    tester.paddle.y = 350;
    tester.paddle.speed = 2;
    tester.paddle.direction = 1;
    tester.paddle.width = 60;
    tester.paddle.height = 40;

    move_paddle(&(tester.paddle));
    printf("paddle x should be 580: %i \n", tester.paddle.x);


    /* normal ball movement */
	tester.ball.x = 60;
	tester.ball.y = 300;
	tester.ball.x_speed = 2;
	tester.ball.y_speed = 2;
	tester.ball.x_direction = 1;
	tester.ball.y_direction = 1;
	tester.ball.width = 8;
	tester.ball.height = 8;

	move_ball(&tester.ball, &tester.bricks, &tester.paddle);
	printf("ball x should be 62: %i \n", tester.ball.x);
	printf("ball y should be 302: %i \n", tester.ball.y);
	
	
	/* colliding with wall */
	tester.ball.x = 1;
	tester.ball.y = 10;
	tester.ball.x_speed = 2;
	tester.ball.y_speed = 2;
	tester.ball.x_direction = -1;
	tester.ball.y_direction = 1;
	tester.ball.width = 8;
	tester.ball.height = 8;
	
	move_ball(&tester.ball, &tester.bricks, &tester.paddle);
	printf("ball x speed should be 2: %i \n", tester.ball.x_speed);
	printf("ball y speed should be 2: %i \n", tester.ball.y_speed);
	printf("ball x direction should be 1: %i \n", tester.ball.x_direction);

	/* colliding with paddle */
	tester.paddle.x = 20;
    tester.paddle.y = 350;
	
	tester.ball.x = 36;
	tester.ball.y = 344;
	tester.ball.x_speed = 2;
	tester.ball.y_speed = 2;
	tester.ball.x_direction = 1;
	tester.ball.y_direction = 1;
	tester.ball.width = 8;
	tester.ball.height = 8;
	
	move_ball(&tester.ball, &tester.bricks, &tester.paddle);
	printf("ball y direction should be -1: %i \n", tester.ball.y_direction);

        
    /* destroy brick from bottom */
    (tester.bricks[0][0]).broken = False;
    (tester.bricks[0][0]).x = 0;
    (tester.bricks[0][0]).y = 0;
    (tester.bricks[0][0]).width = 32;
    (tester.bricks[0][0]).height = 16;
    
    tester.ball.x = 1;
	tester.ball.y = 17;
	tester.ball.x_speed = 1;
	tester.ball.y_speed = 3;
	tester.ball.x_direction = 1;
	tester.ball.y_direction = -1;
	tester.ball.width = 8;
	tester.ball.height = 8;
    
    move_ball(&tester.ball, &tester.bricks, &tester.paddle);
    printf("brick broken should be 1: %i\n", tester.bricks[0][0].broken);
    printf("ball y direction should be 1: %i\n", tester.ball.y_direction);
  
    /* number of bricks */
    total = 0;
    c = 0;
    r = 0;
    while(c < BRICK_COLS)
    {
        r = 0;
        while(r < BRICK_ROWS)
        {
            (tester.bricks[r][c]).broken = False;
            r++;
            total++;
        }
        c++;
    }
    printf("number of bricks should be 100: %i\n", total);

    return 0;
}
