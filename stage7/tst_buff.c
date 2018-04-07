#include "buffer.h"
#include <stdio.h>

int main()
{
	UINT8 item;
	start_queue();
	if(queue_is_empty())
	{
		printf("is empty\n");
	}
	print_buffer();
	enque(0x23);
	if(queue_is_empty())
	{
		printf("is empty\n");
	}
	print_buffer();
	printf("deque: %x\n", deque());
	if(queue_is_empty())
	{
		printf("is empty\n");
	}
	return 0;
}