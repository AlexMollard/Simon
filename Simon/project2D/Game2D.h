#pragma once

#include "DynamicArray.h"
#include "Game.h"
#include "Renderer2D.h"

class Player;

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void QuickMenu(aie::Renderer2D* renderer);

	int _height;
	int _width;
	bool play;

	float playOpacity;
	float quitOpacity;
	float drawOpacity;

	float windowHeight;
	float windowWidth;

protected:
	aie::Renderer2D*	m_2dRenderer;

	// Example textures.
	aie::Texture*		m_texture;
	aie::Texture*		m_texture2;
	aie::Font*			m_font;

	// Player.
	Player* m_Player;
};