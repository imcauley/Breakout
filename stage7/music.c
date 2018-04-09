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

#define A 284		/* A */
#define A_S 268		/* A sharp */
#define B 253		/* ... */
#define C 478
#define C_S 451
#define D 426
#define D_S 402
#define E 379
#define F 358
#define F_S 338
#define G 319
#define G_S 301
#define REPEAT 1    /* repeat a note */
#define REST 0		/* rest note */

#define QU 35		/* quarter note length */
#define EI 17		/* eighth note length */
#define HA 70		/* half note length */
#define WH 140		/* whole note length */

#define NEXT_NOTE 2

#define SONG_LENGTH 49

const unsigned int SONG [] = {
REST,REST, F_S, QU, A, EI, C_S/2, EI, REST, EI, A, EI, REST, EI, F_S, EI, D,
EI, REST, REPEAT, D, EI, REST, REPEAT, D, EI, REST, HA, REST, QU, F_S, EI, A,
EI, C_S/2, QU, A, QU, F_S, EI, E/2, QU+EI, D_S/2, EI, D/2, QU, REST, QU, G_S,
QU, C_S/2, EI, F_S, QU, C_S/2, QU, G_S, QU, C_S/2, QU, G, EI, F_S, QU, E, QU,
REST, REPEAT, E, EI, REST, REPEAT, E, EI, REST, REPEAT, E, EI, REST, QU+EI,
E, EI, REST, REPEAT, E, EI, REST, REPEAT, E, EI, REST, HA, D_S, QU, D, QU,
REST, REPEAT
};

const unsigned int* song = SONG;

/*=== start_music ===========================================================

Purpose: Begins playing the background music. Loads the first note of the song
		 into the A channel, and enables it.

Inputs: N/A

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void start_music()
{
    set_tone(A_CHANNEL,*song);
    enable_channel(A_CHANNEL,1,0);
    set_volume(A_CHANNEL,20);
}

/*=== update_music ===========================================================

Purpose: Updates the song, loading the next note into the A channel.

Inputs:
	time_elapsed: the amount of time that has elapsed in 1/70ths of seconds.

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void update_music(UINT32 time_elapsed)
{
    static UINT32 time_total = 0;
    static int note = 0;
    time_total += time_elapsed;

    if (time_total >= *(song + 1))		/* *(song+1) points to the duration of
    									   the current note that is playing */
	{
		note += 1;
		song += NEXT_NOTE;
		set_tone(A_CHANNEL,*song);
		time_total = 0;
		if(note == SONG_LENGTH)			/* if on last note of the song, */
		{
			note = 0;
			song = SONG;				/* go back to the start of the song. */
		}
    }
    return;
}
