#include "input.h"
#include "buffer.h"
#include "in_asm.h"
#include <osbind.h>
#include <stdio.h>
typedef void (*Vector) ();
#define KEY_ISR_NUM	70

Vector install_vector(int num, Vector vector)
{
  Vector orig;
  Vector *vectp = (Vector *) ((long) num << 2);
  long old_ssp = Super(0);
  

  orig = *vectp;
  *vectp = vector;
  
  Super(old_ssp);
  return orig;
}

void mask_key(bool mask)
{
	volatile UINT8 *IKBD_control = 0xFFFFFC00;
	long old_ssp = Super(0);
	if(mask == True)
	{
		(*IKBD_control) &= 0xBF;
	}
	else
	{
		(*IKBD_control) |= 0x40;
	}
	Super(old_ssp);
}

int main()
{
	long old_ssp;
	unsigned long i = 0;
	Vector orig_key;
	UINT8 input = 0x00;
	
	orig_key = install_vector(KEY_ISR_NUM, key_isr);
	
	start_queue();
	while(input != 0x90)
	{
		if(queue_is_empty() == False)
		{
			input = get_input();
			printf("%x\n", input);
		}
	}

	install_vector(KEY_ISR_NUM, orig_key);
	
	return 0;
}