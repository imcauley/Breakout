/*=========================================

Source File:
splash.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
April 8 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/

#include "splash.h"
#include "render.h"
#include "types.h"
#include "input.h"
#include "buffer.h"

/* DFA for mouse input */
#define NO_INPUT 0
#define CLICK_INPUT 1
#define X_INPUT 2
#define Y_INPUT 3

#define CLICK_UP 0xF8
#define CLICK_DOWN 0xFA

UINT8 splash(UINT32 *base32, UINT8 *base8)
{
	UINT8 prev1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	UINT8 prev2[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
	UINT8 input;
	UINT8 click;
	UINT8 mouse_state = 0;
	UINT8 select = 0;
	
	int x, y = 0;
	
	int dx = 0;
	int dy = 0;
	
	
	
	while(select == 0)
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
			}
		}
		
		if(click == CLICK_DOWN)
		{
			if(x > 72 && x < 232)
			{
				if(y > 234 && y < 266)
				{
					select = 1;
				}
			}
			
			if(x > 72 && x < 232)
			{
				if(y > 340 && y < 376)
				{
					select = 3;
				}
			}
			
		}
		
		render_splash_screen(base32);
		render_mouse(base8, x, y);
		
	}

	return select;
}