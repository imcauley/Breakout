#include "psg.h"
#include "music.h"
#include <osbind.h>

#define A 0
#define B 1
#define C 2

const unsigned int SONG [] = {
0,0,451, 100, 402, 100, 338, 100};

const unsigned int* song = SONG;

void start_music()
{
    /*long old_ssp = Super(0);   */
    
    set_tone(A,*song);
    enable_channel(A,1,0);
    set_volume(A,11);
	
	/*Super(old_ssp);*/
}

void update_music(UINT32 time_elapsed)
{
	static UINT32 time_total = 0;
	static int note = 0;
	time_total += time_elapsed;

    if (time_total >= *(song + 1))
	{
		note += 1;
        song += 2;
		set_tone(A,*song);
		time_total = 0;
		if(note == 4)
		{
			note = 0;
			song = SONG;
		}
	}
    return;
}