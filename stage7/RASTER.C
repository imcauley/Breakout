/*=========================================

Source File:
raster.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/

#include "raster.h"
#include "sprite.c"
#include <osbind.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define CLEAR 0xFFFFFFFF


/*=== plot_bitmap_8 ===========================================================

Purpose: Plots bitmaps with widths of 8 bits to the given screen position.

Inputs:
    *base - beginning of screen buffer
        x - x coordinate for beginning of image
        y - y coordinate for beginning of image
  *bitmap - image to be drawn
   height - height of image


Outputs: Draws the image to the screen.

Limitations/Known bugs: 
    -When the x is above 632 the back
		renders on the other side of the screen
=============================================================================*/

void plot_bitmap_8(UINT8 *base, int x, int y,
  const UINT8 *bitmap, unsigned int height)
{
    int i;
	UINT8 front;
	UINT8 back;
	UINT8 offset = x % 8;

	y *= 80;
	x /= 8;
	
    for(i = 0; i < height; i++)
	{
		front = bitmap[i] >> offset;
		back = bitmap[i] << (8 - offset);
		*(base + y + x) &= ~front;
		*(base + y + x + 1) &= ~back;
		y += 80;
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


void plot_bitmap_32(UINT32 *base, int x, int y,
  const UINT32 *bitmap, unsigned int height)
{
    int i;

    for (i = 0; i < height; i++)
    {
        *(base + y * (SCREEN_WIDTH / 32) + (x >> 5)) = bitmap[i];
        base += (SCREEN_WIDTH / 32);
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

void clear_screen(UINT32 *base)
{
	int x = 0;
	while(x++ < 8000)
	{
		*(base++) = CLEAR;
	}
}

/*=== draw_64rect ===========================================================

Purpose: Draws a recangle with a width of 64 bits

Inputs:
  *base    -  pointer to screen base
  x        -  x position on screen
  y        -  y position on screen
  height   -  desired height of recangle
  clear    -  flag to write black or white
                  True for black
                  False for white

Outputs:  Draws to screen

Limitations/Known bugs: N/A
=============================================================================*/

void draw_64rect(UINT32 *base, int x, int y, int height, bool clear)
{
    int r;
    int offset = (x & 31);
    int c = (x >> 5);

    UINT32 start = CLEAR >> offset;
    UINT32 mid = CLEAR;
    UINT32 end = CLEAR << (32 - offset);

    if(!clear)
    {
        start = ~start;
        mid = ~mid;
        end = ~end;

        r = 0;
        while(r < height)
        {
            *(base + (y * (SCREEN_WIDTH / 32)) + c) = start;
            *(base + (y * (SCREEN_WIDTH / 32)) + (c + 1)) = mid;
            *(base + (y * (SCREEN_WIDTH / 32)) + (c + 2)) = end;
            y++;
            r++;
        }
    }
    else
    {
        r = 0;
        while(r < height)
        {
            *(base + (y * (SCREEN_WIDTH / 32)) + c) |= start;
            *(base + (y * (SCREEN_WIDTH / 32)) + (c + 1)) |= mid;
            *(base + (y * (SCREEN_WIDTH / 32)) + (c + 2)) |= end;
            y++;
            r++;
        }
    }
}

/*=== draw_8rect ===========================================================

Purpose: Draws a recangle with a width of 8 bits

Inputs:
  *base    -  pointer to screen base
  x        -  x position on screen
  y        -  y position on screen
  height   -  desired height of recangle
  clear    -  flag to write black or white
                  True for black
                  False for white

Outputs:  Draws to screen

Limitations/Known bugs: N/A
=============================================================================*/

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
            *(base + (y * (SCREEN_WIDTH / 8)) + c) = start;
            *(base + (y * (SCREEN_WIDTH / 8)) + (c+ 1)) = end;
            y++;
            r++;
        }

    }
    else
    {
        r = 0;
        while(r < height)
        {
            *(base + (y * (SCREEN_WIDTH / 8)) + c) |= start;
            *(base + (y * (SCREEN_WIDTH / 8)) + (c+ 1)) |= end;
            y++;
            r++;
        }

    }
}


/*=== plot_char ===========================================================

Purpose: Writes a character from the constant font to the screen

Inputs:
  *base  -  pointer to screen base
  x      -  x position on screen
  y      -  y position on screen
  character - character code coorosponding to the above font

Outputs:  Draws to screen

Limitations/Known bugs: N/A
=============================================================================*/

void plot_char(UINT8 *base, int x, int y, int character)
{
	int r;
	int letter;
	character *= 8;
	for(r = 0; r < 8; r++)
	{
		letter = character + r;
		*(base + ((SCREEN_WIDTH / 8)*y) + x) = ~(font[letter]);
		y++;
	}
}

/*=== title ===========================================================

Purpose:

Inputs:

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

UINT16 *get_video_base()
{
	long old_ssp;
	UINT8 *get_base;
	UINT16 low;
	UINT16 high;
	UINT32 combined;
	UINT16 *base;

	old_ssp = Super(0);
	get_base = (UINT8 *) 0xFFFF8201;
	high = *get_base;
	low = *(get_base + 2);
	Super(old_ssp);

	combined = low;
	high *= 0x100;
	combined += high;
	combined *= 0x100;

	base = (UINT16 *) combined;

	return base;
}


