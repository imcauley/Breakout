#include "psg.h"

#define A 1
#define B 2
#define C 3

const unsigned int SONG [] = {
0xD5D, 0xBE7, 0xA9B};

void start_music()
{
    long old_ssp = Super(0);
    unsigned int song* = SONG[0];
    
    set_tone(A,song);
    enable_channel(A,1,1);
    set_volume(A,11);
    
}

void update_music(UINT32 time_elapsed)
{
    if (time_elapsed >= 5)
    {
            *song += 1;
    }
    return;
}

