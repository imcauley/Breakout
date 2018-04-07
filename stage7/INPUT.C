/*=========================================

Source File:
input.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
April 7 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/


#include <osbind.h>
#include <stdio.h>
#include "types.h"
#include "buffer.h"

volatile const UINT8 * const IKBD_RDR = 0xFFFFFC02;

UINT8 get_input()
{
	return deque();
}

bool key_pressed()
{
	if(queue_is_empty() == True)
	{
		return False;
	}
	return True;
}

void key_press()
{	
	UINT8 data = (*IKBD_RDR);
	enque(data);
	return;
}

