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


#include <osbind.h>
#include "psg.h"

#define A 1
#define B 2
#define C 3

volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

void write_psg(int reg, UINT8 val)
{
    if (reg >= 0 && reg <= 15 && val >= 0 && val <= 255)
    {
        *PSG_reg_select = reg;
        *PSG_reg_write = val;
    }
    return;
}

UINT8 read_psg(int reg)
{
    if (reg >= 0 && reg <= 15)
    {    
        *PSG_reg_select = reg;
        return *PSG_reg_select;
    }
    return -1;
}

void set_tone(int channel, int tuning)
{
    if (tuning >= 0 && tuning <= 4095)  /* 12 bit value */
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

void set_volume(int channel, int volume)
{
    if (volume >= 0 && volume <= 31)
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

void enable_channel(int channel, int tone_on, int noise_on)
{
    UINT8 mask = 0x00;
    
    UINT8 enable_a_noise = 0x30;
    UINT8 disable_a_noise = 0x08;
    UINT8 enable_b_noise = 0x28;
    UINT8 disable_b_noise = 0x10;
    UINT8 enable_c_noise = 0x18;
    UINT8 disable_c_noise = 0x20;
    
    UINT8 enable_a_tone = 0x06;
    UINT8 disable_a_tone = 0x01;
    UINT8 enable_b_tone = 0x05;
    UINT8 disable_b_tone = 0x02;
    UINT8 enable_c_tone = 0x03;
    UINT8 disable_c_tone = 0x04;
    
    mask &= 0x00111111;
    
    if (channel == A)
    {
        if (tone_on == 1)
            mask |= enable_a_tone;
        else
            mask |= disable_a_tone;
        
        if (noise_on == 1)
            mask |= enable_a_noise;
        else
            mask |= disable_a_noise;
    }
    
    if (channel == B)
    {
        if (tone_on == 1)
            mask |= enable_b_tone;
        else
            mask |= disable_b_tone;
        
        if (noise_on == 1)
            mask |= enable_b_noise;
        else
            mask |= disable_b_noise;
    }
    
    if (channel == C)
    {
        if (tone_on == 1)
            mask |= enable_c_tone;
        else
            mask |= disable_c_tone;
        
        if (noise_on == 1)
            mask |= enable_c_noise;
        else
            mask |= disable_c_noise;
    }
    
    write_psg(7, mask);
}

void stop_sound()
{
    set_volume(A,0);
    set_volume(B,0);
    set_volume(C,0);
    return;
}

/*int main()
{
	long old_ssp = Super(0);
	Super(old_ssp);
    set_tone(A, 248);
    enable_channel(A,1,1);
    set_volume(A,11);


	while (!Cconis())	     
		;

	set_volume(A,0);

	Cnecin();

	return 0;
}*/
