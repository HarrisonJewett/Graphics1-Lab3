#pragma once
#include <math.h>
struct vertex
{
	//coords(x1,y1,x2,y2)
	float coord[4];

	unsigned int color;
};

struct matrix
{
	union
	{
		float members[9];
		struct 
		{
			float xx, xy, xz;
			float yx, yy, yz;
			float zx, zy, zz;
		};
	};
};

struct vec2f
{
	float members[2];
};

vertex triangleVerts[3];
vertex triRender[3];
