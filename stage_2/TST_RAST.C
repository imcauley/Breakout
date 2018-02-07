#include <osbind.h>
#include "raster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BRICK_HEIGHT 16

int main()
{
    UINT16 *base = (UINT16 *) Physbase();
    UINT32 *base2 = (UINT32 *) Physbase();

	UINT16 pacman[16] = {
		0x0ff0,
		0x1ff8,
		0x3f9c,
		0x7f9e,
		0xffff,
		0xfffe,
		0xfff8,
		0xffe0,
		0xffe0,
		0xfff8,
		0xfffe,
		0xffff,
		0x7ffe,
		0x3ffc,
		0x1ff8,
		0x0ff0
	};
	
    plot_pixel(base, 0, 0);
    plot_pixel(base, 1, 1);
    
	plot_bitmap_16(base,32,32,pacman,16);

	plot_bitmap_16(base,35,64,pacman,16);

	/*
    int x;
    int y;
    
    long brick_bitmap[BRICK_HEIGHT] =
    {
        0xFFFFFFFF,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0x80000001,
        0xFFFFFFFF
    };

    clear_screen(base);
    
	for(x = 0; x < 640; x += 32)
    {
        for(y = 0; y < 80; y += 16)
        {
            plot_bitmap_32(base2, x, y, brick_bitmap, BRICK_HEIGHT);
        }
    }
    */
	return 0;
}
