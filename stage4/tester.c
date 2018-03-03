#include "render.h"
#include <osbind.h>

int main()
{
	UINT8 *base8 = (UINT8 *) Physbase();
	UINT32 *base32 = (UINT32 *) Physbase();
	Model tester;
	
	create_bricks(tester.bricks);
	render(&tester);
	remove_brick(base32, 0, 0);
	remove_brick(base32, 1, 0);
	remove_brick(base32, 2, 0);
	remove_brick(base32, 4, 19);
	
	plot_char(base8, 2, 16, 35);
	plot_char(base8, 3, 16, 19);
	plot_char(base8, 4, 16, 31);
	plot_char(base8, 5, 16, 34);
	plot_char(base8, 6, 16, 21);
	
	plot_char(base8, 8, 16, 0);
	plot_char(base8, 9, 16, 0);
	plot_char(base8, 10, 16, 0);
	plot_char(base8, 11, 16, 0);
	return 0;
}