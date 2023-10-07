#include "Game.hpp"

void Game::CreateWindow()
{
	window = new RenderWindow(screenSize, "MINESWEEPER");
	window->setFramerateLimit(30);
}

void Game::UpdateAll()
{
	Event e;
	while(window->pollEvent(e))
	{
		if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window->close();
		}
	}
	controller->Update();
}

void Game::RenderAll()
{
	window->clear(screenBgColor);
	controller->Render();
	window->display();
}

Game::Game()
{
	screenBgColor = Color(20, 20, 20, 225);
	screenSize.width = 800;
	screenSize.height = 900;
	CreateWindow();
	controller = new StateController(window);
}

Game::~Game()
{
	delete window;
	delete controller;
}

void Game::Run()
{
	while(window->isOpen())
	{
		UpdateAll();
		RenderAll();
	}
}