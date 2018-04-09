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

#define A 0
#define B 1
#define C 2

#include "psg.h"
#include "effects.h"

/*=== play_bounce ===========================================================

Purpose: Plays a gunshot noise on channel B

Inputs: N/A

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void play_bounce()
{
    set_noise(15);
    enable_channel(B,0,1);
    set_volume(B,16);
    set_envelope(0,0x1000);
    write_psg(13,0);
    
    return;
}

/*=== play_brick_destroyed ===========================================================

Purpose: Plays an explosion noise on channel C

Inputs: N/A

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void play_brick_destroyed()
{
    set_noise(0x1F);
    set_envelope(0,0x3800);
    enable_channel(C,0,1);
    set_volume(C,16);
    write_psg(13,0);
	
    return;
}
