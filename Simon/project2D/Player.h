#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Colors.h"
#include "DynamicArray.h"


class Player
{
public:
	Player(int width, int height);			//Constructor
	~Player();								//Destructor

	void Update(float deltaTime);			//Function that runs every frame
	void Draw(aie::Renderer2D* renderer, float width, float height);	//Draw Game screen


	void SimonsTurn(float Time,int index);	//Simons turn
	void NewGame();							//Helps to reset game
	void UsersTurn(float Time);				//Players turn
	void Lost();							//Reset function to reset scene
	void Restart();							//Restart function to display loss screen

	int current = 0;						//Current Simon
	int currentPlayer = 0;					//Current Player
	int round = 0;							//Current Round
	float rOpacity = 1.0f;					//Opacity of square
	bool lose = false;						//Lose varible
	int highScore = 0;						//Current HighScore
	

private:
	float counter = 0.0f;					//Simons Counter
	float clickCounter = 1.0f;				//Players Counter

	aie::Font*		m_font;					//Font
	DynamicArray<int> playerOrder;			//Players Colors
	DynamicArray<int> simonOrder;			//Simons Colors
protected:
	// Colors.
	Colors* _Red;							//Red square
	Colors* _Green;							//Green square
	Colors* _Blue;							//Blue square
	Colors* _Purple;						//Purple square

};