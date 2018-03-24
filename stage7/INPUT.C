/*=========================================

Source File:
input.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/


#include <osbind.h>
#include <stdio.h>
#include "types.h"

long get_input();
bool key_pressed();


long get_input()
{
	return Cnecin();
}

bool key_pressed()
{
	long input = Cconis();
	if(input == 0)
	{
		return False;
	}
	else
		return True;
}
