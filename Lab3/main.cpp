#include "RasterSurface.h"
#include "draw.h"
#include "XTime.h"


int main()
{
	XTime timer;
	timer.Restart();

	RS_Initialize(REZ_X, REZ_Y);
	//Top left point (A)
	//x
	triangleVerts[0].coord[0] = -0.7f;
	//y
	triangleVerts[0].coord[1] = 0.7f;
	//z
	triangleVerts[0].coord[2] = 0.0f;
	//w
	triangleVerts[0].coord[3] = 0.0f;
	//Blue
	triangleVerts[0].color = 0x000000FF;

	//Top right (B)
	triangleVerts[1].coord[0] = 0.7f;
	triangleVerts[1].coord[1] = 0.7f;
	triangleVerts[1].coord[2] = 0.0f;
	triangleVerts[1].coord[3] = 0.0f;
	//Green
	triangleVerts[1].color = 0x0000FF00;

	//Bottom (C)
	triangleVerts[2].coord[0] = 0.0f;
	triangleVerts[2].coord[1] = -0.7f;
	triangleVerts[2].coord[2] = 0.0f;
	triangleVerts[2].coord[3] = 0.0f;
	//Red
	triangleVerts[2].color = 0x00FF0000;

	triRender[0].coord[0] = triangleVerts[0].coord[0];
	triRender[0].coord[1] = triangleVerts[0].coord[1];
	triRender[1].coord[0] = triangleVerts[1].coord[0];
	triRender[1].coord[1] = triangleVerts[1].coord[1];
	triRender[2].coord[0] = triangleVerts[2].coord[0];
	triRender[2].coord[1] = triangleVerts[2].coord[1];

	float theta = 0;

	while (RS_Update(myArray, REZ_X * REZ_Y))
	{
		matrix zRotationMatrix;
		zRotationMatrix.xx = cos(theta);
		zRotationMatrix.xy = -1 * sin(theta);
		zRotationMatrix.xz = 0;
		zRotationMatrix.yx = sin(theta);
		zRotationMatrix.yy = cos(theta);
		zRotationMatrix.yz = 0;
		zRotationMatrix.zx = 0;
		zRotationMatrix.zy = 0;
		zRotationMatrix.zz = 1;

		timer.Signal();
		double temp = timer.Delta();
		theta += timer.Delta();


		vec2f temp1 = zRotation(triangleVerts[0], zRotationMatrix);
		vec2f temp2 = zRotation(triangleVerts[1], zRotationMatrix);
		vec2f temp3 = zRotation(triangleVerts[2], zRotationMatrix);
		
		triRender[0].coord[0] = temp1.members[0];
		triRender[0].coord[1] = temp1.members[1];
		triRender[1].coord[0] = temp2.members[0];
		triRender[1].coord[1] = temp2.members[1];
		triRender[2].coord[0] = temp3.members[0];
		triRender[2].coord[1] = temp3.members[1];


		render();
	}	

	RS_Shutdown();

	return 0;
}