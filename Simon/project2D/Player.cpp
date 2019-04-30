#include "Player.h"
#include "Input.h"
#include <iostream>
#include <random>
#include "Font.h"

using namespace std;

Player::Player(int width, int height)
{
	// Get custom royalty free font
	m_font = new aie::Font("./font/goodTimes.ttf", 24);

	// Simons first turn
	simonOrder.PushBack(rand()%4);

	// Create a player object.
	_Red = new Colors(85, -85, 150.0f, 1.0f, 0.26f, 0.28f);
	_Green = new Colors(-85, -85, 150.0f, 0.14f, 0.90f, 0.38f);
	_Blue = new Colors(85, 85, 150.0f, 0.3f, 0.49f, 0.55f);
	_Purple = new Colors(-85, 85, 150.0f, 0.64f, 0.16f, 0.93f);

}

Player::~Player()
{
	// Destruct all objects
	delete _Red;
	delete _Green;
	delete _Blue;
	delete _Purple;
	delete m_font;
}

void Player::Update(float deltaTime)
{
#pragma region Input-Prepare
	// Prepare application for user input
	aie::Input* input = aie::Input::GetInstance();
#pragma endregion

#pragma region Game-Loop
	// Update highscore if players current score is larger then the highscore
	if (highScore < playerOrder.GetUsedData())
	{
		highScore = playerOrder.GetUsedData();
	}

	// Check if player has lost
	if (!lose)
	{
		// Check whos turn it is
		if (current != simonOrder.GetUsedData())
		{
			SimonsTurn(deltaTime, current);		 // Simon's turn
		}
		else if (current >= simonOrder.GetUsedData())
		{
			UsersTurn(deltaTime);				// Player's turn
		}
	}
	else
	{
		// If player has lost go to restart scene
		Restart();
	}
#pragma endregion
}

void Player::SimonsTurn(float Time,int index)
{
#pragma region Display-Simons-Turn
	// Timer
	counter += 4.0f * Time;

	// Delay
	if (counter > 1.0f)
	{
		//-----------------------------------------------------------------------
		// Get Simons array element in order and makes the square he choose flash.
		//-----------------------------------------------------------------------
			switch (simonOrder[index])
			{
			case 0:
				_Red->SetOpacity(1.0f);
				break;
			case 1:
				_Green->SetOpacity(1.0f);
				break;
			case 2:
				_Blue->SetOpacity(1.0f);
				break;
			case 3:
				_Purple->SetOpacity(1.0f);
				break;
			default:
				break;
			}
	}
#pragma endregion

#pragma region Reset-Simons-Turn
	// Delay so that the color squares dont flash for 1 frame and stay for around a second
	if (counter > 2.0f)
	{
		// Increase simons array index by 1
		current++;

		// Resets simon's timer
		counter = 0.0f;

		// Reset all color squares opacity
		_Red->SetOpacity(0.5f);
		_Green->SetOpacity(0.5f);
		_Blue->SetOpacity(0.5f);
		_Purple->SetOpacity(0.5f);
	}
#pragma endregion
}

void Player::UsersTurn(float Time)
{
#pragma region Input-Prepare
	// Prepare application for user input
	aie::Input* input = aie::Input::GetInstance();
#pragma endregion

#pragma region Players-Turn
	// Increase timer
	clickCounter += 1.0f * Time;

	//RED
	if (input->WasMouseButtonPressed(0) && (input->GetMouseX() >= _Red->GetX() - (_Red->GetSize() / 2) && input->GetMouseX() <= _Red->GetX() + (_Red->GetSize() / 2) && input->GetMouseY() >= _Red->GetY() - (_Red->GetSize() / 2) && input->GetMouseY() <= _Red->GetY() + (_Red->GetSize() / 2)))
	{
		//Changing _Red squares varibles
		_Red->SetOpacity(1.0f);
		_Red->SetSize(145);

		//Resetting timer
		clickCounter = 0.0f;

		//Adding players input
		playerOrder.PushBack(0);

		//Detect if player has lost
		if (simonOrder[currentPlayer] != playerOrder[currentPlayer])
			Lost();

		//Add to players turn number
		currentPlayer++;

	}
	//Set squares back to normal after user input
	else if (clickCounter > 0.2 && clickCounter < 0.3)
	{
		//Changing _Red squares varibles
		_Red->SetSize(150);
		_Red->SetOpacity(0.5f);
	}

	//GREEN
	if (input->WasMouseButtonPressed(0) && (input->GetMouseX() >= _Green->GetX() - (_Green->GetSize() / 2) && input->GetMouseX() <= _Green->GetX() + (_Green->GetSize() / 2) && input->GetMouseY() >= _Green->GetY() - (_Green->GetSize() / 2) && input->GetMouseY() <= _Green->GetY() + (_Green->GetSize() / 2)))
	{
		//Changing _Green squares varibles
		_Green->SetOpacity(1.0f);
		_Green->SetSize(145);

		//Reset timer
		clickCounter = 0.0f;

		//Adding players input
		playerOrder.PushBack(1);

		//Detect if player has lost
		if (simonOrder[currentPlayer] != playerOrder[currentPlayer])
			Lost();

		//Add to players turn number
		currentPlayer++;

	}
	//Set squares back to normal after user input
	else if (clickCounter > 0.2 && clickCounter < 0.3)
	{
		//Changing _Green squares varibles
		_Green->SetSize(150);
		_Green->SetOpacity(0.5f);
	}

	//BLUE
	if (input->WasMouseButtonPressed(0) && (input->GetMouseX() >= _Blue->GetX() - (_Blue->GetSize() / 2) && input->GetMouseX() <= _Blue->GetX() + (_Red->GetSize() / 2) && input->GetMouseY() >= _Blue->GetY() - (_Blue->GetSize() / 2) && input->GetMouseY() <= _Blue->GetY() + (_Blue->GetSize() / 2)))
	{
		//Changing _Blue squares varibles
		_Blue->SetOpacity(1.0f);
		_Blue->SetSize(145);

		//Reset timer
		clickCounter = 0.0f;

		//Adding players input
		playerOrder.PushBack(2);

		//Detect if player has lost
		if (simonOrder[currentPlayer] != playerOrder[currentPlayer])
			Lost();

		//Add to players turn number
		currentPlayer++;
	}
	//Set squares back to normal after user input
	else if (clickCounter > 0.2 && clickCounter < 0.3)
	{
		//Changing _Blue squares varibles
		_Blue->SetSize(150);
		_Blue->SetOpacity(0.5f);
	}

	//PURPLE
	if (input->WasMouseButtonPressed(0) && (input->GetMouseX() >= _Purple->GetX() - (_Purple->GetSize() / 2) && input->GetMouseX() <= _Purple->GetX() + (_Purple->GetSize() / 2) && input->GetMouseY() >= _Purple->GetY() - (_Purple->GetSize() / 2) && input->GetMouseY() <= _Purple->GetY() + (_Purple->GetSize() / 2)))
	{
		//Changing _Purple squares varibles
		_Purple->SetOpacity(1.0f);
		_Purple->SetSize(145);

		//Resetting timer
		clickCounter = 0.0f;

		//Adding players input
		playerOrder.PushBack(3);

		//Detect if player has lost
		if (simonOrder[currentPlayer] != playerOrder[currentPlayer])
			Lost();

		//Add to players turn number
		currentPlayer++;
	}
	//Set squares back to normal after user input
	else if (clickCounter > 0.2 && clickCounter < 0.3)
	{
		//Changing _Red squares varibles
		_Purple->SetSize(150);
		_Purple->SetOpacity(0.5f);
	}
#pragma endregion

#pragma region Lose-Detection
	// If players turn is finished
	if (currentPlayer >= current && clickCounter > 0.2 && clickCounter < 0.3)
	{
		for (int i = 0; i < playerOrder.GetUsedData(); i++)
		{
			// Check if player and simon have same array elements
			if (playerOrder[i] == simonOrder[i])
			{
				round++;
			}
		}

		// If simon and player have same amount of element add another to simons
		if (round == simonOrder.GetUsedData())
		{
			//Create simons next color
			simonOrder.PushBack(rand()%4);
		}
		else
		{
			//Goto Lost function
			Lost();
		}

		//Reset players turn for the next round
		round = 0;
		current = 0;
		currentPlayer = 0;
		playerOrder.clear();
	}
#pragma endregion
}

void Player::Lost()
{
#pragma region Reset-squares-color-and-opacity
	// Lose equals true so that game loop is stopped
	lose = true;

	// Set all color square opacity to 100%
	_Red->SetOpacity(1.0f);
	_Green->SetOpacity(1.0f);
	_Blue->SetOpacity(1.0f);
	_Purple->SetOpacity(1.0f);

	// Set all color square size to original size
	_Red->SetSize(150);
	_Green->SetSize(150);
	_Blue->SetSize(150);
	_Purple->SetSize(150);
#pragma endregion
}

void Player::Restart()
{
#pragma region Input-Prepare
	// Prepare application for user input
	aie::Input* input = aie::Input::GetInstance();
#pragma endregion

#pragma region Restart-Button
	// If Restart button is hovered over
	if (input->GetMouseX() <= _Red->GetX() + 85 + 125 && input->GetMouseX() >= _Red->GetX() + 85 - 125 && input->GetMouseY() <= _Red->GetY() - 280 + 25 && input->GetMouseY() >= _Red->GetY() - 280 - 25)
	{
		//Change opacity of restart button
		rOpacity = 0.65f;

		//If button is clicked
		if (input->IsMouseButtonDown(0))
		{
			NewGame();
		}
	}
	else
	{
		//When restart button isnt clicked reset opacity
		rOpacity = 1.0f;
	}
#pragma endregion
}

void Player::NewGame()
{
#pragma region Reset-Game
	// Clear simons and players arrays
	simonOrder.clear();
	playerOrder.clear();

	// Add simons first turn
	simonOrder.PushFront(rand() % 4);

	// Reset varibles
	current = 0;
	currentPlayer = 0;
	round = 0;
	lose = 0;
	lose = false;

	// Set all color square opacity to full
	_Red->SetOpacity(0.5f);
	_Green->SetOpacity(0.5f);
	_Blue->SetOpacity(0.5f);
	_Purple->SetOpacity(0.5f);

	// Set all color square size to previous size
	_Red->SetSize(150);
	_Green->SetSize(150);
	_Blue->SetSize(150);
	_Purple->SetSize(150);
#pragma endregion
}

void Player::Draw(aie::Renderer2D* renderer, float width, float height)
{
#pragma region Draw-Game
	// Convert simonOrder array size to char* from int
	char roundNum[32];
	char highScoreNum[32];
	sprintf(roundNum, "%d", simonOrder.GetUsedData());
	sprintf(highScoreNum, "%d", highScore);

	// Draw title
	renderer->DrawText(m_font, "SIMON", _Red->GetX() - 75, _Red->GetY()+120);
	renderer->DrawBox(_Red->GetX() - 75, _Red->GetY()+120, 1, 75);
	
	// Draw Highscore
	renderer->DrawText(m_font, highScoreNum, _Red->GetX() + 82, _Red->GetY() + 200);
	renderer->DrawText(m_font, "HighScore:", _Red->GetX() + 20, _Red->GetY() + 220);

	// Draw Round
	renderer->DrawText(m_font, "Round:", width / 2 + 20, _Red->GetY() + 120);
	renderer->DrawText(m_font, roundNum, width / 2 + 130, _Red->GetY() + 120);

	// Draw the Color squares
	_Red->Draw(renderer, width, height);
	_Green->Draw(renderer, width, height);
	_Blue->Draw(renderer, width, height);
	_Purple->Draw(renderer, width, height);
#pragma endregion

#pragma region Lose-Scene
	// If player has lost draw You Lost
	if (lose)
	{
		//Black box
		renderer->SetRenderColour(0.07, 0.06, 0.07);
		renderer->DrawBox(width / 2 , height / 2 + 5, 150, 50);

		//You Lost Text
		renderer->SetRenderColour(1, 1, 1);
		renderer->DrawText(m_font, "YOU LOST", width/2 - 65, height/2);

		//Restart botton
		//Button
		renderer->SetRenderColour(1, 1, 1, rOpacity);
		renderer->DrawBox(_Red->GetX() + 85, _Red->GetY() - 280, 250, 50);

		//Text
		renderer->SetRenderColour(0.07, 0.06, 0.07);
		renderer->DrawText(m_font, "Restart", _Red->GetX() + 28, _Red->GetY() - 285);
	}
#pragma endregion
}