# 1 "raster.c" 1
# 1 "./raster.h" 1
# 1 "./types.h" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef int bool;
# 4 "./raster.h" 2


void draw_hori_line(UINT16 *base, int x, int y, int length);
void draw_vert_line(UINT16 *base, int x, int y, int length);
void plot_pixel(UINT16 *base, int x, int y);
void clear_screen(UINT16 *base);
void draw_rect(UINT16 *base, int x, int y, int length, int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void draw_64rect(UINT32 *base, int x, int y, int height, bool clear);
void draw_8rect(UINT8 *base, int x, int y, int height, bool clear);
# 1 "raster.c" 2
# 23 "raster.c"
void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
    int i;

    for (i = 0; i < height; i++)
    {
        *(base + y * 80 + (x >> 3)) |= bitmap[i];
        base += 80;
    }
}
# 51 "raster.c"
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
# 91 "raster.c"
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height)
{
    int i;

    for (i = 0; i < height; i++)
    {
        *(base + y * 20 + (x >> 5)) &= bitmap[i];
        base += 20;
    }
}
# 115 "raster.c"
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
