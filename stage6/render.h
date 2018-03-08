#ifndef RENDER_H
#define RENDER_H

#include "raster.h"
#include "model.h"

void render(Model *game);
void render_paddle(UINT32 *base, Paddle *paddle);
void render_ball(UINT8 *base, Ball *ball);
void render_bricks(UINT32 *base, Brick bricks[][]);
void render_hud(UINT8 *base, Header *header, Lives *lives, Score *score);
void remove_brick(UINT32 *base, int row, int col);
void start_render(Model *game);
void render_clear(Model *game);

#endif