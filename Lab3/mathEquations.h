#pragma once
#include "Includes.h"

//functions
int implicitLineEquation(int x1, int x2, int y1, int y2, int midx, int midy);

//need a function to convert from NDC to the rastor
unsigned int convertNDCX(float x, unsigned int width = 500);
unsigned int convertNDCY(float y, unsigned int height = 500);


unsigned int convertCoor(unsigned int x, unsigned int y, unsigned int width = 500)
{
	return((y*width) + x);
}

int implicitLineEquation(int x1, int x2, int y1, int y2, int midx, int midy)
{
	return ((y1 - y2)*midx + (x2 - x1)*midy + x1*y2 - y1*x2);
}

unsigned int convertNDCX(float x, unsigned int width)
{
	return ((unsigned int)((x + 1)*(width / 2)));
}

unsigned int convertNDCY(float y, unsigned int height)
{
	return ((unsigned int)((1 - y) * (height / 2)));
}

vec2f zRotation(vertex original, matrix multiplier)
{
	vec2f returnThis;
	returnThis.members[0] = (original.coord[0] * multiplier.xx) + (original.coord[1] * multiplier.yx);
	returnThis.members[1] = (original.coord[0] * multiplier.xy) + (original.coord[1] * multiplier.yy);
	return returnThis;
}