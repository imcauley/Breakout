#include "input.h"
#include "buffer.h"
#include "in_asm.h"
#include <osbind.h>
#include <stdio.h>
typedef void (*Vector) ();
#define KEY_ISR_NUM	70

#define CLICK_UP 0xF8
#define CLICK_DOWN 0xFA

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

int convertToSigned(UINT8 num)
{
	int sign = (int) num;
	if(num > 0x7F)
	{
		sign |= 0xFF00;
	}
	return sign;
}

int main()
{
	long old_ssp;
	unsigned long i = 0;
	Vector orig_key;
	UINT8 input = 0x00;
	
	
	UINT8 mouse_mask;
	UINT8 input;
	UINT8 click = 0xf8;
	UINT8 mouse_state = 0;
	int select = 0;
	
	int x, y = 0;
	int dx = 0;
	int dy = 0;
	
	orig_key = install_vector(KEY_ISR_NUM, key_isr);
	start_queue();
	
	while(click != 0xfa)
	{
		while(queue_is_empty() == False)
		{
			input = deque();
			if(mouse_state == 0)
			{
				if(input == CLICK_DOWN || input == CLICK_UP)
				{
					click = input;
					mouse_state += 1;
				}
				else
				{

					deque();
					deque();
				}
				
			}
			else if(mouse_state == 1)
			{
				dx = convertToSigned(input);
				mouse_state += 1;
			}
			else if(mouse_state == 2)
			{
				dy = convertToSigned(input);
				
				mouse_state = 0;
				
				x += dx;
				y += dy;
				dx = 0;
				dy = 0;
				
				if(x < 0)
					x = 0;
				if(x > 632)
					x = 632;
				if(y < 0)
					y = 0;
				if(y > 392)
					y = 392;
				
				printf("%x, x: %i, y: %i\n", click, x, y);
			}
		}
	}
	
	install_vector(KEY_ISR_NUM, orig_key);
	
	return 0;
}