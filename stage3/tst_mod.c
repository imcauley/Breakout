#include <osbind.h>
#include "model.h"
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BRICK_HEIGHT 16

int main()
{
    Model tester;
 
    /* successful paddle move */	

    tester.paddle.x = 0;
    tester.paddle.y = 0;
    tester.paddle.speed = 1;
    tester.paddle.direction = 1;
    tester.paddle.width = 60;
    tester.paddle.height = 40;

    move_paddle(&(tester.paddle));
    printf("paddle x should be 1: %i \n", tester.paddle.x);
	
	
	/* paddle hits left wall */
	tester.paddle.x = 0;
    tester.paddle.y = 0;
    tester.paddle.speed = 1;
    tester.paddle.direction = -2;
    tester.paddle.width = 60;
    tester.paddle.height = 40;

    move_paddle(&(tester.paddle));
    printf("paddle x should be 0: %i \n", tester.paddle.x);
	
	/* paddle hits right wall */
	tester.paddle.x = 580;
    tester.paddle.y = 0;
    tester.paddle.speed = 1;
    tester.paddle.direction = 2;
    tester.paddle.width = 60;
    tester.paddle.height = 40;

    move_paddle(&(tester.paddle));
    printf("paddle x should be 640: %i \n", tester.paddle.x);


    /* normal ball movement */
	tester.ball.x = 60;
	tester.ball.y = 60;
	tester.ball.x_speed = 2;
	tester.ball.y_speed = 2;
	tester.ball.x_direction = 1;
	tester.ball.y_direction = 1;
	tester.ball.width = 16;
	tester.ball.height = 16;
	
	move_ball(&(tester.ball), tester.bricks)
	printf("ball x should be 62: %i \n", tester.ball.x);
	printf("ball y should be 62: %i \n", tester.ball.y);
	
    return 0;
}
