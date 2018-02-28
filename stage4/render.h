#ifndef RENDER_H
#define RENDER_H

#include "../stage2/raster.h"
#include "../stage3/model.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

void render(Model *game);
void render_paddle(Paddle *paddle);
void render_ball(Ball *ball);
void render_bricks(Brick bricks[]);
void render_hud(Header *header, Lives *lives, Score *score);


#endif