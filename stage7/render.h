/*=========================================

Source File:
render.h

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/


#ifndef RENDER_H
#define RENDER_H

#include "raster.h"
#include "model.h"

void render(UINT8 *base8, UINT32 *base32, Model *game);
void render_paddle(UINT32 *base, Paddle *paddle);
void render_ball(UINT8 *base, Ball *ball);
void render_bricks(UINT32 *base, Brick bricks[][]);
void render_hud(UINT8 *base, Header *header, Lives *lives, Score *score);
void remove_brick(UINT32 *base, int row, int col);
void start_render(UINT32 *base32, Model *game);
void render_clear(UINT8 *base8, UINT32 *base32, Model *game);
void simple_render(UINT8 *base8, UINT32 *base32, Model *game);
void render_splash_screen(UINT32 *base32); 
void render_game_over(UINT8 *base8, Score *score);
#endif
