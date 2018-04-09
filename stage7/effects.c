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
#include "effects.h"

void play_bounce()
{
    set_noise(15);
    enable_channel(1,0,1);
    set_volume(1,16);
    set_envelope(0,0x1000);
    write_psg(13,0);
    
    return;
}

void play_brick_destroyed()
{
    set_noise(0x1F);
    set_envelope(0,0x3800);
    enable_channel(2,0,1);
    set_volume(2,16);
    write_psg(13,0);
	
    return;
}
