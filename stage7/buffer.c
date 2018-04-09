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

/*=== start_queue ===========================================================

Purpose: set all the initial values of the input buffer

Inputs:
	N/A

Outputs:
	N/A

Limitations/Known bugs: N/A
=============================================================================*/

void start_queue()
{
	front = 0;
	back = 0;
	return;
}

/*=== enque ===========================================================

Purpose: put a object at the end of the buffer

Inputs:
	-code: object to be placed in the buffer

Outputs:
	N/A

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

/*=== deque ===========================================================

Purpose: returns the object at the front of the queue. If there is nothing
			at the end of the buffer it returns 0x00.

Inputs:
	N/A

Outputs:
	-object at the end of the queue

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

/*=== queue_is_empty ===========================================================

Purpose: boolean on if the queue is empty

Inputs:
	N/A

Outputs:
	-True if the buffer is empty
	=False if the buffer is not

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