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
    UINT8 *base0 = (UINT8 *) Physbase();
    UINT16 *base = (UINT16 *) Physbase();
    UINT32 *base2 = (UINT32 *) Physbase();
    
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
            plot_bitmap_32(base2, (c*BRICK_WIDTH), ((r*BRICK_HEIGHT) + 40), brick_bitmap, 16);
        }
    }
    
    for(r = 0; r < 576; r += 7)
    {   
        draw_64rect(base2, r, 300, 16, False);
        Vsync();
        draw_64rect(base2, r, 300, 16, True);
    }
    
    for(r = 0; r < 632; r += 10)
    {
        draw_8rect(base0, r, 250, 8, False);
        Vsync();
        draw_8rect(base0, r, 250, 8, True);
    }
    
    
	return 0;
}
