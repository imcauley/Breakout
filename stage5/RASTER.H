#ifndef RASTER_H
#define RASTER_H

#include "types.h"

void draw_hori_line(UINT16 *base, int x, int y, int length);
void draw_vert_line(UINT16 *base, int x, int y, int length);
void plot_pixel(UINT16 *base, int x, int y);
void clear_screen(UINT16 *base);
void draw_rect(UINT16 *base, int x, int y, int length, int height);
void plot_char(UINT8 *base, int x, int y, int character);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void draw_64rect(UINT32 *base, int x, int y, int height, bool clear);
void draw_8rect(UINT8 *base, int x, int y, int height, bool clear);
#endif
