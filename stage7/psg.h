/*=========================================

Source File:
psg.h

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/

#ifndef PSG_H
#define PSG_H

#include "types.h"

void write_psg(int reg, UINT8 val);
UINT8 read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void stop_sound();
void enable_channel(int channel, int tone_on, int noise_on);
void set_envelope(int shape, unsigned int sustain);
void set_noise(int tuning);

#endif