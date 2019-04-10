#include "Game2D.h"
#include "DynamicArray.h"
#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Player.h"
#include <iostream>


Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/goodTimes.ttf", 24);

	// Create a player object.
	m_Player = new Player(width, height);

	play = false;
	playOpacity = 1.0f;
	quitOpacity = 1.0f;
	drawOpacity = 1.0f;

}

Game2D::~Game2D()
{
	// Delete player.
	delete m_Player;
	m_Player = nullptr;

	// Delete the renderer.
	delete m_2dRenderer;
	delete m_font;
}

void Game2D::Update(float deltaTime)
{
	if (play)
	{
		// Update the player.
		m_Player->Update(deltaTime);
	}

	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();

	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		m_Player->NewGame();
		play = false;
	}

	if (!play)
	{
		//Play
		if (input->GetMouseX() <= windowWidth / 2 + 100 && input->GetMouseX() >= windowWidth / 2 - 100 && input->GetMouseY() <= windowHeight / 2 + 35 && input->GetMouseY() >= windowHeight / 2 - 35)
		{
			playOpacity = 0.75f;
			if (input->WasMouseButtonPressed(0))
			{
				play = true;
			}
		}
		else
		{
			playOpacity = 1.0f;
		}

		//Quit
		if (input->GetMouseX() <= windowWidth / 2 + 100 && input->GetMouseX() >= windowWidth / 2 - 100 && input->GetMouseY() <= windowHeight / 2 + 35 - 100 && input->GetMouseY() >= windowHeight / 2 - 35 - 100)
		{
			quitOpacity = 0.75f;
			if (input->WasMouseButtonPressed(0))
			{
				aie::Application* application = aie::Application::GetInstance();
				application->Quit();
			}
		}
		else
		{
			quitOpacity = 1.0f;
		}
	}
}

void Game2D::QuickMenu(aie::Renderer2D* renderer)
{
	aie::Input* input = aie::Input::GetInstance();

	if (input->GetMouseX() <= windowWidth / 2 - 150 + 20 &&
		input->GetMouseX() >= windowWidth / 2 - 150 - 20 &&
		input->GetMouseY() >= windowHeight / 2 + 300 - 2 &&
		input->GetMouseY() <= windowHeight / 2 + 320 + 2 )
	{
		drawOpacity = 0.75f;
		if (input->WasMouseButtonPressed(0))
		{
			m_Player->NewGame();
			play = false;
		}
	}
	else
	{
		drawOpacity = 1.0f;
	}

	renderer->SetRenderColour(1, 1, 1, drawOpacity);
	renderer->DrawBox(windowWidth / 2 - 150, windowHeight / 2 + 300, 40, 4);
	renderer->DrawBox(windowWidth / 2 - 150, windowHeight / 2 + 310, 40, 4);
	renderer->DrawBox(windowWidth / 2 - 150, windowHeight / 2 + 320, 40, 4);
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	application->SetBackgroundColour(0.07, 0.06, 0.07);

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();
	
	//Get size
	windowHeight = (float)application->GetWindowHeight();
	windowWidth = (float)application->GetWindowWidth();

	//Main Menu
	if (!play)
	{
		//Bottons
		m_2dRenderer->SetRenderColour(1, 1, 1, playOpacity);
		m_2dRenderer->DrawBox(windowWidth / 2, windowHeight / 2, 200, 70);
		m_2dRenderer->SetRenderColour(1, 1, 1, quitOpacity);
		m_2dRenderer->DrawBox(windowWidth / 2, windowHeight / 2 - 100, 200, 70);
		
		//Logo
		m_2dRenderer->SetRenderColour(1,1,1);
		m_2dRenderer->DrawText(m_font, "SIMON", windowWidth/2 - 100, windowHeight/2 + 120);
		m_2dRenderer->DrawBox(windowWidth/2 - 100, windowHeight/2 + 120, 1, 75);

		//Text
		m_2dRenderer->SetRenderColour(0.07, 0.06, 0.07);
		m_2dRenderer->DrawText(m_font, "Play", windowWidth / 2 - 100, windowHeight / 2 - 5);
		m_2dRenderer->DrawText(m_font, "Quit", windowWidth / 2 - 100, windowHeight / 2 - 5 - 100);
	}


	if (play)
	{
	// Draw the player.
	m_Player->Draw(m_2dRenderer, windowWidth, windowHeight);

	//Draw in top right
	QuickMenu(m_2dRenderer);
	}

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}