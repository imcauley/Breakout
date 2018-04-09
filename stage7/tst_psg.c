#include "psg.h"
#include <stdio.h>
#include <osbind.h>

int main()
{
	long old_ssp = Super(0);
	write_psg(7,10);
	printf("write_psg test - expected: 10 actual: %d\n", read_psg(7));
	set_tone(1, 400);
	printf("set_tone test - expected fine:  144, actual: %d\n", read_psg(2));
	printf("set_tone test - expected rough: 1,   actual: %d\n", read_psg(3));
	set_volume(2,12);
	printf("set_volume test - expected: 12, actual: %d\n", read_psg(10));
	enable_channel(0,1,1);
	enable_channel(1,1,1);
	enable_channel(2,1,1);
	printf("enable_channel test - expected: 0, actual: %d\n", read_psg(7));
	stop_sound();
	printf("stop_sound test - A expected: 0, actual: %d\n", read_psg(8));
	printf("stop_sound test - B expected: 0, actual: %d\n", read_psg(9));
	printf("stop_sound test - C expected: 0, actual: %d\n", read_psg(10));
	set_noise(10);
	printf("set_noise test - expected: 10, actual: %d\n", read_psg(6));
	set_envelope(4,0xAAAA);
	printf("set_envelope test - shape expected: 4, actual: %d\n", read_psg(0xD));
	printf("set_envelope test - lsustain expected: 170, actual: %d\n", read_psg(0xB));
	printf("set_envelope test - usustain expected: 170, actual: %d\n", read_psg(0xC));

	
	Super(old_ssp);
	return 1;
}
