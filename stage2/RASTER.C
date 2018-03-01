#include "raster.h"

/* HEADER BLOCK */


/*=== plot_bitmap_8 ===========================================================

Purpose: Plots bitmaps with widths of 8 bits to the given screen position.

Inputs: 
    *base - beginning of screen buffer
        x - x coordinate for beginning of image
        y - y coordinate for beginning of image
  *bitmap - image to be drawn
   height - height of image
            

Outputs: Draws the image to the screen.

Limitations/Known bugs: N/A
=============================================================================*/

void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
    int i;
    
    for (i = 0; i < height; i++)
    {
        *(base + y * 80 + (x >> 3)) |= bitmap[i];
        base += 80;
    }
}

/*=== plot_bitmap_16 ===========================================================

Purpose: Plots bitmaps with widths of 16 bits to the given screen position.

Inputs: 
    *base - beginning of screen buffer
        x - x coordinate for beginning of image
        y - y coordinate for beginning of image
  *bitmap - image to be drawn
   height - height of image
            

Outputs: Draws the image to the screen.

Limitations/Known bugs: N/A
=============================================================================*/

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, 
			unsigned int height)
{
    int i;
    UINT16 offset = x % 16;

    UINT16 extra_mask = 0xFFFF >> (16 - offset);
    UINT16 extra = 0xFFFF;
   
    for (i = 0; i < height; i++)
    {
        extra = bitmap[i];
	extra &= extra_mask;
	extra = extra << (16 - offset);

        *(base + y * 40 + (x >> 4)) |= (bitmap[i] >> offset);
	*((base + y * 40 + ((x + 16) >> 4))) |= extra;
        y++;
    }

}

/*=== plot_bitmap_32 ===========================================================

Purpose: Plots bitmaps with widths of 32 bits to the given screen position.

Inputs: 
    *base - beginning of screen buffer
        x - x coordinate for beginning of image
        y - y coordinate for beginning of image
  *bitmap - image to be drawn
   height - height of image
            

Outputs: Draws the image to the screen.

Limitations/Known bugs: N/A
=============================================================================*/


void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height)
{
    int i;
    
    for (i = 0; i < height; i++)
    {
        *(base + y * 20 + (x >> 5)) &= bitmap[i];
        base += 20;
    }
}

/*=== clear_screen ============================================================

Purpose: Clears the screen (to black)

Inputs:
    *base - beginning of screen buffer

Outputs:
    Draws a black screen

Limitations/Known bugs: N/A
=============================================================================*/

void clear_screen(UINT16 *base)
{
    UINT16 *temp = base;
    int x = 0;
    
    while (x++ < 16000)
        *(temp++) |= 0xFFFF;
}

void draw_hori_line(UINT16 *base, int x, int y, int length)
{
    UINT16 start = 0xFFFF;
    UINT16 end = 0xFFFF;

    int start_word = x / 16;
    int end_word = ((x + length) / 16) + 1;

    base += (y * 40);

    if((x && 16) != 0)
    {
	start = start >> (x % 16);
	start = ~start;
    }    
 
    if(((x + length) && 16) != 0)
    {
	end = end << (16 - ((x + length) % 16));
        end = ~end;
    }

    *(base + start_word) &= start;
    start_word++;

    while(start_word < end_word)
    {     
	*(base + start_word) &= 0x0000;
        start_word++;
    }
    
    *(base + start_word) &= end;
        
}

void draw_vert_line(UINT16 *base, int x, int y, int length)
{
    int i;
    
    for (i = 0; i < length; i++)
    {
        *(base + y * 40 + (x >> 4)) |= 1 << (15 - (x & 15));
        base += 40;
    }

}

void plot_pixel(UINT16 *base, int x, int y)
{
    *(base + (y * 40) + (x >> 4)) &= ~(0x8000 >> (x && 16));
}

void draw_rect(UINT16 *base, int x, int y, int length, int height)
{
    int i;
    
    for (i = 0; i < height; i++)
    {    
        draw_hori_line(base, x, y, length);
        y++;
    }
}

void draw_64rect(UINT32 *base, int x, int y, int height, bool clear)
{
    int r;
    int offset = (x & 31);
    int c = (x >> 5);
    
    UINT32 start = 0xFFFFFFFF >> offset;
    UINT32 mid = 0xFFFFFFFF;
    UINT32 end = 0xFFFFFFFF << (32 - offset);
    
    if(!clear)
    {
        start = ~start;
        mid = ~mid;
        end = ~end;
        
        r = 0;
        while(r < height)
        {
            *(base + (y * 20) + c) = start;
            *(base + (y * 20) + (c + 1)) = mid;
            *(base + (y * 20) + (c + 2)) = end;
            y++;
            r++;
        }
    }
    else
    {
        r = 0;
        while(r < height)
        {
            *(base + (y * 20) + c) |= start;
            *(base + (y * 20) + (c + 1)) |= mid;
            *(base + (y * 20) + (c + 2)) |= end;
            y++;
            r++;
        }
    }
}

void draw_8rect(UINT8 *base, int x, int y, int height, bool clear)
{
    int r;
    int offset = (x & 7);
    int c = (x >> 3);
    
    UINT8 start = 0xFF >> offset;
    UINT8 end = 0xFF << (8 - offset);
    
    if(!clear)
    {
        start = ~start;
        end = ~end;
        
        r = 0;
        while(r < height)
        {
            *(base + (y * 80) + c) = start;
            *(base + (y * 80) + (c+ 1)) = end;
            y++;
            r++;
        }
        
    }
    else
    {
        r = 0;
        while(r < height)
        {
            *(base + (y * 80) + c) |= start;
            *(base + (y * 80) + (c+ 1)) |= end;
            y++;
            r++;
        }
        
    }
}

