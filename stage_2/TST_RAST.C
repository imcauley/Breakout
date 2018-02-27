#include <osbind.h>
#include "raster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BRICK_HEIGHT 16
#define BRICK_WIDTH 32

int main()
{
    int r;
    int c;
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


    
    UINT32 brick_bitmap[BRICK_HEIGHT] =
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
    
    r = 0;
    for(r = 0; r < 5; r++)
    {
        c = 0;
        for(c = 0; c < 20; c++)
        {
            plot_bitmap_32(base2, (c*BRICK_WIDTH), (r*BRICK_HEIGHT), brick_bitmap, 16);
        }
    }

    draw_rect(base, 20, 334, 64,16);
    draw_rect(base, 12, 350, 64,16);
    clear_rect(base, 12, 350, 64, 16);
    draw_rect(base,40,200, 8,8);
    r = 0;
    c = 350;
    while(r < (SCREEN_WIDTH - 8))
    {   
        draw_rect(base,r,c, 8,8);
        Vsync();
        clear_rect(base,r,c, 8,8);

        r+=5;
        c--;
    }
    
	return 0;
}
