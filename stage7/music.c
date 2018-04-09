/*=========================================

Source File:
psg.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/

#include "psg.h"
#include "music.h"

#define A_CHANNEL 0
#define B_CHANNEL 1
#define C_CHANNEL 2

#define A 284
#define A_S 268
#define B 253
#define C 478
#define C_S 451
#define D 426
#define D_S 402
#define E 379
#define F 358
#define F_S 338
#define G 319
#define G_S 301

#define QU 35
#define EI 17
#define HA 70
#define WH 140

const unsigned int SONG [] = {
0,0, F_S, QU, A, EI, C_S/2, EI, 0, EI, A, EI, 0, EI, F_S, EI, D, EI, 0, 1, D, EI, 0, 1, D, EI, 0, HA, 0, QU,
F_S, EI, A, EI, C_S/2, QU, A, QU, F_S, EI, E/2, QU+EI, D_S/2, EI, D/2, QU, 0, QU, G_S, QU, C_S/2, EI, F_S, QU,
C_S/2, QU, G_S, QU, C_S/2, QU, G, EI, F_S, QU, E, QU, 0, 1, E, EI, 0, 1, E, EI, 0, 1, E, EI, 0, QU+EI, E, EI, 0, 1,
E, EI, 0, 1, E, EI, 0, HA, D_S, QU, D, QU, 0, 1


};

const unsigned int* song = SONG;

void start_music()
{
    set_tone(A_CHANNEL,*song);
    enable_channel(A_CHANNEL,1,0);
    set_volume(A_CHANNEL,7);
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
	set_tone(A_CHANNEL,*song);
	time_total = 0;
	if(note == 49)
	{
            note = 0;
	    song = SONG;
	}
    }
    return;
}
