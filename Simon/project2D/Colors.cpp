#include "Colors.h"
#include <iostream>

Colors::Colors(float x1, float y1, float size, float R, float G, float B)
{
	// Set the Color's position.
	_posX1 = x1;
	_posY1 = y1;
	_size = size;
	_R = R;
	_G = G;
	_B = B;
	opacity = 0.5f;
	counter = 0.0f;
}

Colors::~Colors()
{

}

void Colors::Update(float deltaTime, float timer)
{

}

float Colors::GetOpacity()
{
	return opacity;
}

void Colors::SetOpacity(float newOpacity)
{
	opacity = newOpacity;
}

float Colors::GetX()
{
	return screenWidth / 2 - _posX1;
}

float Colors::GetY()
{
	return  screenHeight / 2 - _posY1;
}

float Colors::GetSize()
{
	return _size;
}

void Colors::SetSize(float size)
{
	_size = size;
}

void Colors::Draw(aie::Renderer2D* renderer, float width, float height)
{
	screenWidth = width;
	screenHeight = height;

	// Draw the Boxs
	renderer->SetRenderColour(_R, _G, _B, opacity);
	renderer->DrawBox(width/2 - _posX1,  height/2 - _posY1, _size, _size);

}