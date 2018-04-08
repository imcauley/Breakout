/*=========================================

Source File:
buffer.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
April 8 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/

#include "types.h"
#include "buffer.h"
#include <stdio.h>
#define BUFFER_SZ 255

UINT8 IKDB_BUFFER[BUFFER_SZ];
UINT8 front;
UINT8 back;

/*=== title ===========================================================

Purpose:

Inputs:

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

void start_queue()
{
	front = 0;
	back = 0;
	return;
}

/*=== title ===========================================================

Purpose:

Inputs:

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

void enque(UINT8 code)
{
	if(front != back + 1)
	{
		IKDB_BUFFER[back] = code;
		back += 1;
		if(back % BUFFER_SZ == 0)
		{
			back = 0;
		}
	}
	
	return;
}

/*=== title ===========================================================

Purpose:

Inputs:

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

UINT8 deque()
{
	UINT8 item;
	
	if(queue_is_empty() == False)
	{
		item = IKDB_BUFFER[front];
		front += 1;
		if(front % BUFFER_SZ == 0)
		{
			front = 0;
		}
		return item;
	}
	return 0x00;
}

/*=== title ===========================================================

Purpose:

Inputs:

Outputs:

Limitations/Known bugs: N/A
=============================================================================*/

bool queue_is_empty()
{
	if(front == back)
	{
		return True;
	}
	else
	{
		return False;
	}

}