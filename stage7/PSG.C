/*=========================================

Source File:
psg.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
April 9 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/


#include <osbind.h>
#include "psg.h"

#define A 0
#define B 1
#define C 2

#define ENABLE_A_NOISE 0x30
#define DISABLE_A_NOISE 0x08
#define ENABLE_B_NOISE 0x28
#define DISABLE_B_NOISE 0x10
#define ENABLE_C_NOISE 0x18
#define DISABLE_C_NOISE 0x20
    
#define ENABLE_A_TONE 0x06
#define DISABLE_A_TONE 0x01
#define ENABLE_B_TONE 0x05
#define DISABLE_B_TONE 0x02
#define ENABLE_C_TONE 0x03
#define DISABLE_C_TONE 0x04

volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

/*=== write_psg ===========================================================

Purpose: Writes the given value to the given PSG register.

Inputs:
	reg: the register to be written to
	val: the value to be written

Outputs: N/A

Limitations/Known bugs: Value must be an 8 bit value
=============================================================================*/

void write_psg(int reg, UINT8 val)
{
    if (reg >= 0 && reg <= 0xF && val >= 0 && val <= 0xFF)
    {
        *PSG_reg_select = reg;
        *PSG_reg_write = val;
    }
    return;
}

/*=== read_psg ===========================================================

Purpose: Reads the value currently stored at the given psg register.

Inputs:
	reg: register to be read

Outputs:
	value: the value that was stored at the register. if an invalid register
		   was given returns -1.
		   
Limitations/Known bugs: N/A
=============================================================================*/

UINT8 read_psg(int reg)
{
	UINT8 value;
    if (reg >= 0 && reg <= 0xF)
    {    
        *PSG_reg_select = reg;
		value = *PSG_reg_select;
        return value;
    }
    return -1;
}

/*=== set_tone ===========================================================

Purpose: Sets the 12 bit fine and rough tuning of the given channel.

Inputs:
	channel: channel to be tuned (A, B, or C)
	tuning: 12 bit value that fine and rough are to be set from.

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void set_tone(int channel, int tuning)
{
    if (tuning >= 0 && tuning <= 0xFFF)  /* 12 bit value */
    {
        int fine_mask = 0x0FF;
        int rough_mask = ~fine_mask;
        
        int fine = tuning & fine_mask;
        int rough = (tuning & rough_mask) >> 8;
        
        if (channel == A)
        {
            write_psg(0, fine);
            write_psg(1,rough);
        }
        
        if (channel == B)
        {
            write_psg(2,fine);
            write_psg(3,rough);
        }
        
        if (channel == C)
        {
            write_psg(4,fine);
            write_psg(5,rough);
        }
    }
    return;
}

/*=== set_volume ===========================================================

Purpose: Sets the volume level of the given channel.

Inputs:
	channel: channel to be tuned (A, B, or C)
	volume: volume level to be set to

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void set_volume(int channel, int volume)
{
    if (volume >= 0 && volume <= 0x1F)
    {
        if (channel == A)
            write_psg(8,volume);
        
        if (channel == B)
            write_psg(9,volume);
        
        if (channel == C)
            write_psg(10,volume);
    }
    return;
}

/*=== enable_channel ===========================================================

Purpose: Enables or disables the tone and noise of the given channel,
		 while preserving the status of the other channels.

Inputs:
	channel:  channel to be changed
	tone_on:  flag if tone is being turned on or off
	noise_on: flag if noise is being turned on or off 

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void enable_channel(int channel, int tone_on, int noise_on)
{
	UINT8 old_channels = read_psg(7);
	
    if (channel == A)
    {
        if (tone_on == 1)
            write_psg(7,old_channels & ENABLE_A_TONE);
        else
            write_psg(7,old_channels | DISABLE_A_TONE);
        
        if (noise_on == 1)
            write_psg(7,old_channels & ENABLE_A_NOISE);
        else
            write_psg(7,old_channels | DISABLE_A_NOISE);
    }
    
    if (channel == B)
    {
        if (tone_on == 1)
            write_psg(7,old_channels & ENABLE_B_TONE);
        else
            write_psg(7,old_channels | DISABLE_B_TONE);
        
        if (noise_on == 1)
            write_psg(7,old_channels & ENABLE_B_NOISE);
        else
            write_psg(7,old_channels | DISABLE_B_NOISE);
    }
    
    if (channel == C)
    {
        if (tone_on == 1)
            write_psg(7,old_channels & ENABLE_C_TONE);
        else
            write_psg(7,old_channels | DISABLE_C_TONE);
        
        if (noise_on == 1)
            write_psg(7,old_channels & ENABLE_C_NOISE);
        else
            write_psg(7,old_channels | DISABLE_C_NOISE);
    }
}

/*=== stop_sound ===========================================================

Purpose: Stops all sound output from the psg by setting all 3 channels volumes
		 to 0.

Inputs: N/A

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void stop_sound()
{
    set_volume(A,0);
    set_volume(B,0);
    set_volume(C,0);
    return;
}

/*=== set_noise ===========================================================

Purpose: Sets the noise value of the psg

Inputs:
	tuning: value to be set to

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void set_noise(int tuning)
{
	if (tuning >= 0 && tuning <= 0x1F)
		write_psg(6,tuning);
}

/*=== set_envelope ===========================================================

Purpose: sets the envelope frequency and shape.

Inputs:
	sustain: value to set envelope frequency to
	shape: shape to be set to

Outputs: N/A

Limitations/Known bugs: N/A
=============================================================================*/

void set_envelope(int shape, unsigned int sustain)
{
	if (shape >= 0 && shape <= 0xF)
		write_psg(0xD,shape);
	
	if (sustain <= 0xFFFF)
	{
		unsigned int lower = sustain & 0xFF;
		unsigned int upper = sustain & 0xFF00;
        upper >>= 8;
		write_psg(0xC,upper);
		write_psg(0xB,lower);
	}
}
