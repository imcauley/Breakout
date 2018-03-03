#ifndef RENDER_H
#define RENDER_H

#include "raster.h"
#include "model.h"

void render(Model *game);
void render_paddle(Paddle *paddle);
void render_ball(Ball *ball);
void render_bricks(UINT32 *base, Brick bricks[][]);
void render_hud(Header *header, Lives *lives, Score *score);
void remove_brick(UINT32 *base, int row, int col);

#endif