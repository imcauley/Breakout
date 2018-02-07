#include <osbind.h>
#include "model.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BRICK_HEIGHT 16

int main()
{
    struct Model tester;
 
    /* successful paddle move */	
	tester.paddle.x = 0;
	tester.paddle.y = 0;
	tester.paddle.speed = 1;
	tester.paddle.direction = 1;
	tester.paddle.width = 60;
	tester.paddle.height = 20;
	
    move_paddle(&tester.paddle);
    printf("successful paddle move. %i = 1", tester.paddle.x)
    
    /* hits left side */ 
    tester.paddle = {0, 0, 1, -1, 60, 20}
    move_paddle(&tester.paddle);
    printf("successful paddle move. %i = 0", tester.paddle.x)

    
    /* hits right side */ 
    tester.paddle = {600, 0, 1, 1, 60, 20}
    move_paddle(&tester.paddle);
    printf("successful paddle move. %i = 600", tester.paddle.x)

	return 0;
}
