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
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
    int i;

    for (i = 0; i < height; i++)
    {
        *(base + y * 40 + (x >> 4)) |= bitmap[i];
        base += 40;
    }
}
# 80 "raster.c"
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height)
{
    int i;

    for (i = 0; i < height; i++)
    {
        *(base + y * 20 + (x >> 5)) |= bitmap[i];
        base += 20;
    }
}
# 104 "raster.c"
void clear_screen(UINT16 *base)
{
    UINT16 *temp = base;
    int x = 0;

    while (x++ < 16000)
        *(temp++) |= 0xFFFF;
}

void draw_hori_line(UINT16 *base, int x, int y, int length)
{
    int i;

    int full_lines = length / 16;
    int partial = length % 16;

    *(base + y * 40 + (x >> 4)) |= partial;
    base++;

    for (i = 0; i < full_lines; i++)
    {
        *(base + y * 40 + (x >> 4)) |= 0xFFFF;
        base++;
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
    *(base + y * 40 + (x >> 4)) |= 1 << (15 - (x & 15));
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
