#include "Game.hpp"

Game::Game() : window(VideoMode(680, 380), "SFML Application"), player()
{
	player.setRadius(100.f);
	player.setFillColor(Color::Cyan);
	player.setPosition(50.f, 50.f);
}

void Game::Run()
{
	while (window.isOpen())
	{
		ProcessEvents();
		Update();
		Render();
	}
}

void Game::ProcessEvents()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
	}
}

void Game::Update() {}

void Game::Render()
{
	window.clear();
	window.draw(player);
	window.display();
}