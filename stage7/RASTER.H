/*=========================================

Source File:
raster.h

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/


#ifndef RASTER_H
#define RASTER_H

#include "types.h"

void clear_screen(UINT32 *base);
void plot_char(UINT8 *base, int x, int y, int character);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void draw_64rect(UINT32 *base, int x, int y, int height, bool clear);
void draw_8rect(UINT8 *base, int x, int y, int height, bool clear);

#endif
