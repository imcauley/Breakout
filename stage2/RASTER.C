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

void move_bitmap(UINT16 *base, int x1, int y1, int x2, UINT16 *bitmap,
			int height)
{
     UINT32 saved[16];
     int position;
     int i;

     while(i < 16)
     {
	saved[i] = *(base + ((y1 + 16) * 40) + (x1 << 4));
	i = i + 1;
     }

     plot_bitmap_16(base, x1, y1, bitmap, height);
     plot_bitmap_16(base, x1, y1, saved, height);			 
    /*
     while(x1 < x2)
     {

	
	position = ((y1*40) + (x1 >> 4));

	for(i = 0; i < 16; i++)
     	{
     		saved[i] = *(base + position + (i*40));
     	}

        x1 = x1 + 1;
     }
    */
}
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

void clear_hori_line(UINT16 *base, int x, int y, int length)
{
    UINT16 start = 0xFFFF;
    UINT16 end = 0xFFFF;

    int start_word = x / 16;
    int end_word = ((x + length) / 16) + 1;

    base += (y * 40);

    if((x && 16) != 0)
    {
        start = start >> (x % 16);
    }    
 
    if(((x + length) && 16) != 0)
    {
        end = end << (16 - ((x + length) % 16));
    }

    *(base + start_word) |= start;
    start_word++;

    while(start_word < end_word)
    {     
	*(base + start_word) |= 0xFFFF;
        start_word++;
    }
    
    if(length > 8)
    {
        *(base + start_word) |= end;
    }
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

void clear_rect(UINT16 *base, int x, int y, int length, int height)
{
    int i;
    
    for (i = 0; i < height; i++)
    {    
        clear_hori_line(base, x, y, length);
        y++;
    }
}

