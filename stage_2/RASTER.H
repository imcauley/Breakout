#ifndef RASTER_H
#define RASTER_H

#include "types.h"

void draw_hori_line(UINT16 *base, int x, int y, int length);
void draw_vert_line(UINT16 *base, int x, int y, int length);
void plot_pixel(UINT16 *base, int x, int y);
void clear_screen(UINT16 *base);
void draw_rect(UINT16 *base, int x, int y, int length, int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void move_bitmap(UINT16 *base, int x1, int y1, int x2, UINT16 *bitmap,
			int height);
#endif
