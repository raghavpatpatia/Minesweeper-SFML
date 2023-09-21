#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Game
{
private:
	RenderWindow window;
	CircleShape player;

	void ProcessEvents();
	void Update();
	void Render();

public:
	Game();
	void Run();
};