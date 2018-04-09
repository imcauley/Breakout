/*=========================================

Source File:
breakout.c

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
March 23 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

KNOWN BUGS:
-When the ball is on the paddle and the paddle
	is against a wall the ball will go into the
	paddle
-Occasionally when the ball touches the bottom
	corner it will be drawn on the top of the
	screen
-If the ball hits the side of the paddle the 
	direction of the ball will be changed in 
	the y direction, not the x direction

==========================================*/

#include "render.h"
#include "input.c"
#include "events.h"
#include "rast_asm.h"
#include "in_asm.h"
#include "splash.h"
#include <osbind.h>
#include <stdio.h>
#include <string.h>
#include "psg.h"
#include "music.h"

typedef void (*Vector) ();

#define Q    0x90
#define KEY_ISR_NUM	70
#define VBL_ISR_NUM 28

#define BUFFER_SZ 32000

#define EMPTY_KEY 0x00
#define RELEASE	0x80
#define MOUSE_INPUT 0xF8
#define SEVEN_LSB 0x7F

void vert_sync();

UINT8 buffer2[32256];
UINT8 background[32256];

bool render_request = True;
Model game;

/*=== get_base ===========================================================

Purpose: offset the screen base to be 256 bit aligned

Inputs: start of buffer

Outputs:  new start of buffer

Limitations/Known bugs: N/A
=============================================================================*/

UINT8 *get_base(UINT8 buffer[])
{
	UINT8 *base;
	unsigned int difference;
	base = buffer;
	difference = (int) base;
	difference %= 0x100;
	difference = 0x100 - difference;
	return base + difference;
}

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

int main()
{
	long old_ssp;
	/* buffer1: space in memory dedicated to the first screen buffer*/
	UINT8 *buffer1_8 = (UINT8 *) get_video_base();
	UINT32 *buffer1_32 = (UINT32 *) get_video_base();


	/* buffer2: space in memory dedicated to the second screen buffer*/
	UINT8 *buffer2_8 = get_base(buffer2);
	UINT32 *buffer2_32 = (UINT32 *) buffer2_8;

	/* background:  buffer specially dedicated to storing the background */
	UINT8 *background_8 = get_base(background);
	UINT32 *background_32 = (UINT32 *) background_8;

	/* pointer to where the renderer is writing to */
	UINT8 *render_base_8 = buffer1_8;
	UINT32 *render_base_32 = buffer1_32;

	/* current:  what the bricks were last screenshot */
	Brick current[5][20];
	int x,y = -1;
	
	bool hold = False;
	UINT8 hold_mask;
	UINT8 mouse_mask;
	UINT8 held_key;

	UINT8 input = 0;
		
	bool swap = False;
	
	UINT8 select = 0;

	Vector orig_key = install_vector(KEY_ISR_NUM, key_isr);
	Vector orig_vbl = install_vector(VBL_ISR_NUM, VBL_isr);
	
	start_queue();
	start_game(&game);
	old_ssp = Super(0);
	start_music();
	Super(old_ssp);

	memcpy(current, game.bricks, sizeof(current));
	
	start_queue();
	select = splash(buffer1_32, buffer1_8);
	
	if(select == 1)
	{
		start_render(background_32, &game);
	}
	
	while(input != Q && select == 1)
	{
		if(queue_is_empty() == False)
		{
			input = get_input();
			
			if(input != MOUSE_INPUT)
			{
				if((input & RELEASE) == EMPTY_KEY)
				{
					hold = True;
					held_key = input;
				}
				else
				{
					if((input & SEVEN_LSB) == held_key)
					{
						hold = False;
						held_key = EMPTY_KEY;
					}
				}
			}
				
		}
		else
		{
			clear_input();
		}
		
		if(hold == True)
		{
			asynch_events(&game.paddle, &game.ball, held_key);
		}

		if(render_request == True)
		{
			for(x = 0; x < BRICK_ROWS; x++)
			{
				for(y = 0; y < BRICK_COLS; y++)
				{
					if(current[x][y].broken != ((game.bricks)[x][y]).broken)
					{
						remove_brick(background_32, x, y);
					}
				}
			}
			memcpy(current, game.bricks, sizeof(current));

			memcpy(render_base_8, background_8, BUFFER_SZ);
			render(render_base_8, render_base_32, &game);

			if(swap == True)
			{
				render_base_8 = buffer2_8;
				render_base_32 = buffer2_32;
				old_ssp = Super(0);
				set_screen_base(buffer1_8);
				Super(old_ssp);
				swap = False;
			}
			else
			{
				render_base_8 = buffer1_8;
				render_base_32 = buffer1_32;
				old_ssp = Super(0);
				set_screen_base(buffer2_8);
				Super(old_ssp);
				swap = True;
			}
			
			render_request = False;
		}

	}
	

	old_ssp = Super(0);
	stop_sound();
	set_screen_base(buffer1_8);
	Super(old_ssp);

	install_vector(KEY_ISR_NUM, orig_key);
	install_vector(VBL_ISR_NUM, orig_vbl);
	
	
	return 0;
}

void vert_sync()
{
	update_music(1);
	if(render_request == False)
	{
		synch_events(&(game.paddle), &(game.ball), game.bricks);
		condition_events(&(game.paddle), &(game.ball), 
					game.bricks, &(game.score), &(game.lives));
	}
				
	render_request = True;
}
