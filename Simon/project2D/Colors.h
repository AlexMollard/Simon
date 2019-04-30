#pragma once
#include "Renderer2D.h"
#include "Input.h"


class Colors
{
public:
	Colors(float x1, float y1, float size, float R, float G, float B);	//Color square Constructor

	void Draw(aie::Renderer2D* renderer, float width, float height);	//Draw color square  

	//Functions to change and get varibles

	//Opacity
	float GetOpacity();
	void SetOpacity(float newOpacity);

	//Postion
	float GetX();
	float GetY();

	//Size
	float GetSize();
	void SetSize(float size);

protected:
	//Window Size
	float screenWidth;		//Window Width
	float screenHeight;		//Window Height

	//Square Draw Varibles
	float opacity;			//Square opacity
	float _posX1;			//X postion of square
	float _posY1;			//Y postion of square
	float _size;			//Size of square
	float _R;				//Red value of square
	float _G;				//Green value of square
	float _B;				//Blue value of square
};