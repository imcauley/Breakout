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
        int fine_mask = 0x000011111111;
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
/*
void enable_channel(int channel, int tone_on, int noise_on)
{
    int enable_a = 0x110;
    int enable_b = 0x101;
    int enable_c = 0x011;
    
    if (tone_on == 1)
    {
        
    }
    if (channel == A)
    {
        if (tone_on == 1)
        {
            
        }
    }
}*/

void stop_sound()
{
    set_volume(A,0);
    set_volume(B,0);
    set_volume(C,0);
    return;
}
int main()
{
    return 0;
}
/*
int main()
{
	
	long old_ssp = Super(0);
    
   

	*PSG_reg_select = 0;		 set channel A fine tune = 248 
	*PSG_reg_write  = 248;

	*PSG_reg_select = 1;		 set channel A coarse tune = 0 
	*PSG_reg_write  = 100;

    *PSG_reg_select = 6;
    *PSG_reg_write = 31;

	*PSG_reg_select = 7;		 enable channel A on mixer 
	*PSG_reg_write  = 0x3E;

	*PSG_reg_select = 8;		 set channel A volume = 11 
	*PSG_reg_write  = 11;


	while (!Cconis())	     tone now playing, await key 
		;

	*PSG_reg_select = 8;		 set channel A volume = 0 
	*PSG_reg_write  = 0;

	Cnecin();
	Super(old_ssp);
	return 0;
}
*/