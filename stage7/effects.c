#include "psg.h"
#include "effects.h"

void play_bounce()
{
	set_noise(0x0F);
	enable_channel(1,0,1);
	enable_channel(2,0,1);
	set_volume(1,0x10);
	set_volume(2,0x10);
	set_envelope(0x0,0x01);
	return;
}

void play_brick_destroyed()
{
	set_noise(0x1F);
	enable_channel(1,0,1);
	enable_channel(2,0,1);
	set_volume(1,0x10);
	set_volume(2,0x10);
	set_envelope(0x0,0x01);
	return;
}