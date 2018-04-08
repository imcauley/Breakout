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

#include "types.h"

int convertToSigned(UINT8 num)
{
	int sign = (int) num;
	
	if(num > 0x7F)
	{
		num |= 0xFF00;
	}
	return sign;
}