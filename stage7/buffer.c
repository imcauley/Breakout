#include "types.h"
#include "buffer.h"
#include <stdio.h>
#define BUFFER_SZ 256

UINT8 IKDB_BUFFER[BUFFER_SZ];
UINT8 front;
UINT8 back;

void start_queue()
{
	front = 0;
	back = 0;
	return;
}
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

void print_buffer()
{
	int i;
	
	for(i = 0; i < BUFFER_SZ; i++)
	{
		printf("%x, ",IKDB_BUFFER[i]);
	}
	printf("\n");
	return;
}