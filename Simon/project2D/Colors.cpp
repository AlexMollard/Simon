#include "Colors.h"
#include <iostream>

Colors::Colors(float x1, float y1, float size, float R, float G, float B)
{
	// Set the Color's position.
	_posX1 = x1;
	_posY1 = y1;

	// Set Colors's Size
	_size = size;

	// Set Colors's RGB values
	_R = R;
	_G = G;
	_B = B;

	// Set colors's opacity
	opacity = 0.5f;
}

//-------------------------------
// OPACITY
//-------------------------------
float Colors::GetOpacity()
{
	return opacity;
}

void Colors::SetOpacity(float newOpacity)
{
	opacity = newOpacity;
}

//-------------------------------
// POSTION
//-------------------------------
float Colors::GetX()
{
	return screenWidth / 2 - _posX1;
}

float Colors::GetY()
{
	return  screenHeight / 2 - _posY1;
}

//-------------------------------
// SIZE
//-------------------------------
float Colors::GetSize()
{
	return _size;
}

void Colors::SetSize(float size)
{
	_size = size;
}

//-------------------------------
// DRAW SQUARES
//-------------------------------
void Colors::Draw(aie::Renderer2D* renderer, float width, float height)
{
	screenWidth = width;
	screenHeight = height;

	// Draw the Boxs
	renderer->SetRenderColour(_R, _G, _B, opacity);
	renderer->DrawBox(width/2 - _posX1,  height/2 - _posY1, _size, _size);

}