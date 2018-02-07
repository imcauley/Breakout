#include <osbind.h>
#include "raster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BRICK_HEIGHT 16

int main()
{
    Model testSnapshot = 
{
    {
        {{0, 40}, false, 32, 16},
        {{16, 40}, false, 32, 16}
    },                                 /* bricks */
    {{320,200}, 10,10, 1, 1, 8, 8},    /* ball */
    {{320,379}, 10, 1, 60, 20},        /* paddle */
    {{0,40}, 640, 360},                /* board */
    {{560, 5}, "0958"},                /* score */
    {{500, 5}, "XXX"},                 /* lives */
    {{0,39}}                           /* header */
}
 
    /* successful paddle move */
    testSnapshot.paddle = {0, 0, 1, 1, 60, 20}
    move_paddle(&testSnapshot.paddle);
    printf("successful paddle move. %i = 1", testSnapshot.paddle.x)
    
    /* hits left side */ 
    testSnapshot.paddle = {0, 0, 1, -1, 60, 20}
    move_paddle(&testSnapshot.paddle);
    printf("successful paddle move. %i = 0", testSnapshot.paddle.x)

    
    /* hits right side */ 
    testSnapshot.paddle = {600, 0, 1, 1, 60, 20}
    move_paddle(&testSnapshot.paddle);
    printf("successful paddle move. %i = 600", testSnapshot.paddle.x)

	return 0;
}
