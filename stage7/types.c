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
#define NEGATIVE 0xFF00
#define LAST_LSB 0x7F

int convertToSigned(UINT8 num)
{
	int sign = (int) num;
	if(num > LAST_LSB)
	{
		sign |= NEGATIVE;
	}
	return sign;
}