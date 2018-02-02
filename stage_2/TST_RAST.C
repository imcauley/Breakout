#include <osbind.h>
#include "raster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BRICK_HEIGHT 16

int main()
{
    UINT16 *base = (UINT16 *) Physbase();
    UINT32 *base2 = (UINT32 *) Physbase();
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

	return 0;
}
