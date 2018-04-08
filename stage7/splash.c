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

void splash(UINT32 *base32, UINT8 *base8)
{
	UINT8 input;
	UINT8 click;
	UINT8 mouse_state = 0;
	int select = 0;
	
	int x, y = 0;
	
	int dx = 0;
	int dy = 0;
	
	clear_screen(base32);
	
	while(select != 3)
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
				if(dx > 15 && dx < -15)
					dx = 0;
				mouse_state += 1;
			}
			else if(mouse_state == 2)
			{
				dy = convertToSigned(input);
				if(dy > 15 && dy < -15)
					dy = 0;
				
				mouse_state = 0;
				
				x += dx;
				y += dy;
				dx = 0;
				dy = 0;
			}
		}
		
		if(click == CLICK_DOWN)
		{
			select = 3;
		}
		
		render_mouse(base8, x, y);
		
	}

	return;
}