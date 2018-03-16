#include "render.h"
#include <osbind.h>

int main()
{
	UINT8 *base8 = (UINT8 *) Physbase();
	UINT32 *base32 = (UINT32 *) Physbase();
	Model tester;
	int r;
	
	create_bricks(tester.bricks);
	
	tester.ball.x = 200;
	tester.ball.y = 200;
	tester.ball.height = 8;
	
	tester.paddle.x = 20;
	tester.paddle.y = 300;
	tester.paddle.height = 16;
	
	for(r = 0; r < 400; r += 7)
	{
		Vsync();
		tester.paddle.x = r;
		render(&tester);
	}
	
	return 0;
}