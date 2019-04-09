#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Colors.h"
#include "DynamicArray.h"


class Player
{
public:
	Player(int width, int height);
	~Player();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer, float width, float height);

	bool resetBuffer = false;

	void SimonsTurn(float Time,int index);
	void NewGame();
	bool UsersTurn(float Time);
	void Lost();
	void Restart();
	bool click;

	int current;	//Current Simon
	int currentPlayer;	//Current Player
	int round;
	float rOpacity;
	bool lose;
	int highScore;
	

private:
	float counter;
	float clickCounter;

	aie::Texture* m_texture;
	aie::Font*		m_font;
	DynamicArray<int> playerOrder;
	DynamicArray<int> simonOrder;
protected:
	// Colors.
	Colors* _Red;
	Colors* _Green;
	Colors* _Blue;
	Colors* _Purple;

};

