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

	// Initalise the Font.
	m_font = new aie::Font("./font/goodTimes.ttf", 24);

	// Create a player object.
	m_Player = new Player(width, height);

	// Set game to not playing
	play = false;
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

	// Prepare bootstrap for input
	aie::Input* input = aie::Input::GetInstance();

	// Exit to the menu if escape key is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		m_Player->NewGame();
		play = false;
	}

	if (!play)
	{
		// If Play button is hovered over by mouse
		if (input->GetMouseX() <= windowWidth / 2 + 100 && input->GetMouseX() >= windowWidth / 2 - 100 && input->GetMouseY() <= windowHeight / 2 + 35 && input->GetMouseY() >= windowHeight / 2 - 35)
		{
			// Change Play buttons opacity
			playOpacity = 0.75f;

			// If Play button is pressed
			if (input->WasMouseButtonPressed(0))
			{
				play = true;
			}
		}
		else
		{
			// Set Play buttons opacity back to 100%
			playOpacity = 1.0f;
		}

		// If Quit button is hovered over by mouse
		if (input->GetMouseX() <= windowWidth / 2 + 100 && input->GetMouseX() >= windowWidth / 2 - 100 && input->GetMouseY() <= windowHeight / 2 + 35 - 100 && input->GetMouseY() >= windowHeight / 2 - 35 - 100)
		{
			// Change Quit buttons opacity
			quitOpacity = 0.75f;

			// If Quit button is pressed
			if (input->WasMouseButtonPressed(0))
			{
				// Close game
				aie::Application* application = aie::Application::GetInstance();
				application->Quit();
			}
		}
		else
		{
			// Set Play buttons opacity back to 100%
			quitOpacity = 1.0f;
		}
	}
}

void Game2D::QuickMenu(aie::Renderer2D* renderer)
{
	// Prepare application for input from user
	aie::Input* input = aie::Input::GetInstance();

	// If mouse is hovered over quick menu draw
	if (input->GetMouseX() <= windowWidth / 2 - 150 + 20 &&
		input->GetMouseX() >= windowWidth / 2 - 150 - 20 &&
		input->GetMouseY() >= windowHeight / 2 + 300 - 2 &&
		input->GetMouseY() <= windowHeight / 2 + 320 + 2 )
	{
		// Change quick menu draw opacity 
		drawOpacity = 0.75f;

		// If quick menu draw is clicked
		if (input->WasMouseButtonPressed(0))
		{
			// Restart game
			m_Player->NewGame();

			// Return to menu
			play = false;
		}
	}
	else
	{
		// Make quick draw menu opacity 100%
		drawOpacity = 1.0f;
	}

	// Draw quick draw menu
	renderer->SetRenderColour(1, 1, 1, drawOpacity);							// Color
	renderer->DrawBox(windowWidth / 2 - 150, windowHeight / 2 + 300, 40, 4);	// Draw Box as a line
	renderer->DrawBox(windowWidth / 2 - 150, windowHeight / 2 + 310, 40, 4);	// Draw Box as a line
	renderer->DrawBox(windowWidth / 2 - 150, windowHeight / 2 + 320, 40, 4);	// Draw Box as a line
}

void Game2D::Draw()
{
	// Needed to get instance of application
	aie::Application* application = aie::Application::GetInstance();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Set background color to be a off shade of black
	application->SetBackgroundColour(0.07, 0.06, 0.07);

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();
	
	// Get size of window
	windowHeight = (float)application->GetWindowHeight();
	windowWidth = (float)application->GetWindowWidth();

	// Draw Main Menu
	if (!play)
	{
		// Draw Buttons
		m_2dRenderer->SetRenderColour(1, 1, 1, playOpacity);
		m_2dRenderer->DrawBox(windowWidth / 2, windowHeight / 2, 200, 70);
		m_2dRenderer->SetRenderColour(1, 1, 1, quitOpacity);
		m_2dRenderer->DrawBox(windowWidth / 2, windowHeight / 2 - 100, 200, 70);
		
		// Draw Logo
		m_2dRenderer->SetRenderColour(1,1,1);
		m_2dRenderer->DrawText(m_font, "SIMON", windowWidth/2 - 100, windowHeight/2 + 120);
		m_2dRenderer->DrawBox(windowWidth/2 - 100, windowHeight/2 + 120, 1, 75);

		// Draw Text
		m_2dRenderer->SetRenderColour(0.07, 0.06, 0.07);
		m_2dRenderer->DrawText(m_font, "Play", windowWidth / 2 - 100, windowHeight / 2 - 5);
		m_2dRenderer->DrawText(m_font, "Quit", windowWidth / 2 - 100, windowHeight / 2 - 5 - 100);
	}


	if (play)
	{
	// Update the Draw in player.
	m_Player->Draw(m_2dRenderer, windowWidth, windowHeight);

	// Draw in top right
	QuickMenu(m_2dRenderer);
	}

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}