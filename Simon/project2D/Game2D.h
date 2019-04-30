#pragma once

#include "DynamicArray.h"
#include "Game.h"
#include "Renderer2D.h"

class Player;

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen); //Game constructor
	virtual ~Game2D();			//Game destructor

	virtual void Update(float deltaTime);		//Function that updates every frame
	virtual void Draw();						//Draws menu to scrren and updates draw function in player

	void QuickMenu(aie::Renderer2D* renderer);	//Draw button function

	bool play;					//Game playing bool

	//Button opacity
	float playOpacity = 1.0f;	//Play button opacity
	float quitOpacity = 1.0f;	//Quit button opacity
	float drawOpacity = 1.0f;	//Draw button opacity

	//Window size (Used to draw all objects to the center of screen)
	float windowHeight;			//Windows Height
	float windowWidth;			//Windows Width

protected:
	//Objects
	aie::Renderer2D* m_2dRenderer; //Renderer
	aie::Font*	m_font;			//Font
	Player* m_Player;			//Game player
};