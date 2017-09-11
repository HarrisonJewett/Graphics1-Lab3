#pragma once
#include "mathEquations.h"



void(*VertexShader) (vertex &) = 0;
void(*PixelShader) (unsigned int &) = 0;

//need a matrix

void VS_Multiply(vertex &multiplyMe)
{
	//multiply vertex by matrix(multiplyme, SV_WorldMatrix);
}

void PS_Black(unsigned int &makeBlack)
{
	makeBlack = 0x00000000;
}

/*
include.h
math.h
shaders.h
draw.h
main.cpp
*/