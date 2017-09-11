#pragma once
#include "Shaders.h"

#define REZ_X 500
#define REZ_Y 500

void render();
void parametricAlgorithm(unsigned int startX, unsigned int startY, unsigned int finalX, unsigned int finalY, unsigned int startColor, unsigned int finalColor);
unsigned int interpColors(unsigned int sourceColor, unsigned int desColor, float ratio);
void colorToScreen(unsigned int x, unsigned int y, unsigned int color);
void clearBuffer(unsigned int color);
bool barycentricCheck(int x1, int y1, int x2, int y2, int x3, int y3, int pointX, int pointY);
unsigned int interp3Colors(int x1, int y1, int x2, int y2, int x3, int y3, int pointX, int pointY);
unsigned int myArray[REZ_X * REZ_Y];

void render()
{
	clearBuffer(0x00000000);

	
	for (unsigned int y = 0; y < 500; ++y)
	{
		for (unsigned int x = 0; x < 500; ++x)
		{
			if (barycentricCheck(convertNDCX(triRender[0].coord[0]), convertNDCY(triRender[0].coord[1]), convertNDCX(triRender[1].coord[0]), convertNDCY(triRender[1].coord[1]), convertNDCX(triRender[2].coord[0]), convertNDCY(triRender[2].coord[1]), x, y))
				myArray[convertCoor(x, y)] = interp3Colors(convertNDCX(triRender[0].coord[0]), convertNDCY(triRender[0].coord[1]), convertNDCX(triRender[1].coord[0]), convertNDCY(triRender[1].coord[1]), convertNDCX(triRender[2].coord[0]), convertNDCY(triRender[2].coord[1]), x, y);
		}
	}
	//line from A to B
	parametricAlgorithm(convertNDCX(triRender[0].coord[0]), convertNDCY(triRender[0].coord[1]), convertNDCX(triRender[1].coord[0]),
		convertNDCY(triRender[1].coord[1]), 0xFFFFFFFF, 0xFFFFFFFF);
	//line from B to C
	parametricAlgorithm(convertNDCX(triRender[1].coord[0]), convertNDCY(triRender[1].coord[1]), convertNDCX(triRender[2].coord[0]),
		convertNDCY(triRender[2].coord[1]), 0xFFFFFFFF, 0xFFFFFFFF);
	//line from C to A
	parametricAlgorithm(convertNDCX(triRender[2].coord[0]), convertNDCY(triRender[2].coord[1]), convertNDCX(triRender[0].coord[0]),
		convertNDCY(triRender[0].coord[1]), 0xFFFFFFFF, 0xFFFFFFFF);
}

void parametricAlgorithm(unsigned int startX, unsigned int startY, unsigned int finalX, unsigned int finalY, unsigned int startColor, unsigned int finalColor)
{
	unsigned int deltaX = abs((int)startX - (int)finalX);
	unsigned int deltaY = abs((int)startY - (int)finalY);

	unsigned int x1, x2, y1, y2;
	if (startX < finalX)
	{
		x1 = startX;
		x2 = finalX;
	}
	else
	{
		x1 = finalX;
		x2 = startX;
	}
	if (startY < finalY)
	{
		y1 = startY;
		y2 = finalY;
	}
	else
	{
		y1 = finalY;
		y2 = startY;
	}
	//if slope is not steep
	if (deltaX > deltaY)
	{
		for (unsigned int i = x1; i < x2; ++i)
		{
			float ratio = ((float)i - (float)startX) / ((float)finalX - (float)startX);
			int currY = ((int)finalY - (int)startY)*ratio + (int)startY;
			unsigned int colorToDraw = interpColors(startColor, finalColor, ratio);
			colorToScreen(i, (unsigned int)floor((double)currY + 0.5), colorToDraw);
		}
	}
	else
	{
		for (unsigned int i = y1; i < y2; ++i)
		{
			float ratio = ((float)i - (float)startY) / ((float)finalY - (float)startY);
			int currX = ((int)finalX - (int)startX)*ratio + (int)startX;
			unsigned int colorToDraw = interpColors(startColor, finalColor, ratio);
			colorToScreen((unsigned int)floor((double)currX + 0.5), i, colorToDraw);
		}
	}
}

unsigned int interpColors(unsigned int sourceColor, unsigned int desColor, float ratio)
{
	//(b - a)*r + a

	//ARGB
	int r = (sourceColor & 0x00FF0000) >> 16;
	int g = (sourceColor & 0x0000FF00) >> 8;
	int b = (sourceColor & 0x000000FF);

	int newR = (desColor & 0x00FF0000) >> 16;
	int newG = (desColor & 0x0000FF00) >> 8;
	int newB = (desColor & 0x000000FF);

	int finalR = (int)((newR - r) * (ratio)+r);
	int finalG = (int)((newG - g) * (ratio)+g);
	int finalB = (int)((newB - b) * (ratio)+b);

	return((finalR << 16) | (finalG << 8) | finalB);
}

void colorToScreen(unsigned int x, unsigned int y, unsigned int color)
{
	if (x > REZ_X || y > REZ_Y) {}
	else
		myArray[convertCoor(x, y)] = color;
}

void clearBuffer(unsigned int color)
{
	for (unsigned int i = 0; i < (REZ_X * REZ_Y); ++i)
		myArray[i] = color;
}

bool barycentricCheck(int x1, int y1, int x2, int y2, int x3, int y3, int pointX, int pointY)
{
	int gamma = implicitLineEquation(x1, x2, y1, y2, x3, y3);
	int alpha = implicitLineEquation(x2, x3, y2, y3, x1, y1);
	int beta = implicitLineEquation(x3, x1, y3, y1, x2, y2);
	int temp1 = implicitLineEquation(x1, x2, y1, y2, pointX, pointY);
	int temp2 = implicitLineEquation(x2, x3, y2, y3, pointX, pointY);
	int temp3 = implicitLineEquation(x3, x1, y3, y1, pointX, pointY);

	float check1 = (float)temp1 / gamma;
	float check2 = (float)temp2 / alpha;
	float check3 = (float)temp3 / beta;


	return (check1 > 0 && check1 < 1 && check2 > 0 && check2 < 1 && check3 > 0 && check3 < 1);
}

unsigned int interp3Colors(int x1, int y1, int x2, int y2, int x3, int y3, int pointX, int pointY)
{
	//1 is blue
	//2 is green
	//3 is red	
	int gamma = implicitLineEquation(x1, x2, y1, y2, x3, y3);
	int alpha = implicitLineEquation(x2, x3, y2, y3, x1, y1);
	int beta = implicitLineEquation(x3, x1, y3, y1, x2, y2);
	int temp1 = implicitLineEquation(x1, x2, y1, y2, pointX, pointY);
	int temp2 = implicitLineEquation(x2, x3, y2, y3, pointX, pointY);
	int temp3 = implicitLineEquation(x3, x1, y3, y1, pointX, pointY);
	float check1 = (float)temp1 / gamma;
	float check2 = (float)temp2 / alpha;
	float check3 = (float)temp3 / beta;

	int finalR = (int)((check1) * 0x000000FF);
	int finalG = (int)((check3) * 0x000000FF);
	int finalB = (int)((check2) * 0x000000FF);
	
	return ((finalR << 16) | (finalG << 8) | finalB);
}