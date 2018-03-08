#include <osbind.h>
#include <stdio.h>
#include "types.h"

long get_input();
bool key_pressed();



long get_input()
{
	return Cnecin();
}

bool key_pressed()
{
	return Cconos();
}

int main()
{
	get_input();
}