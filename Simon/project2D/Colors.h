#pragma once
#include "Renderer2D.h"
#include "Input.h"


class Colors
{
public:
	Colors() {};
	Colors(float x1, float y1, float size, float R, float G, float B);
	~Colors();

	void Update(float deltaTime, float timer);
	void Draw(aie::Renderer2D* renderer, float width, float height);

	float GetOpacity();
	void SetOpacity(float newOpacity);

	float GetX();
	float GetY();

	float GetSize();
	void SetSize(float size);

	float counter;
	float opacity;

	aie::Texture* m_texture;

	float screenWidth;
	float screenHeight;

	float _posX1;
	float _posY1;
	float _size;
	float _R;
	float _G;
	float _B;
};