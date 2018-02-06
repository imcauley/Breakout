# 1 "raster.c" 1
# 1 "./raster.h" 1
# 1 "./types.h" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
# 4 "./raster.h" 2


void draw_hori_line(UINT16 *base, int x, int y, int length);
void draw_vert_line(UINT16 *base, int x, int y, int length);
void plot_pixel(UINT16 *base, int x, int y);
void clear_screen(UINT16 *base);
void draw_rect(UINT16 *base, int x, int y, int length, int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void move_bitmap(UINT16 *base, int x1, int y1, int x2, UINT16 *bitmap,
			int height);
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
# 81 "raster.c"
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
# 122 "raster.c"
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height)
{
    int i;

    for (i = 0; i < height; i++)
    {
        *(base + y * 20 + (x >> 5)) |= bitmap[i];
        base += 20;
    }
}
# 146 "raster.c"
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
