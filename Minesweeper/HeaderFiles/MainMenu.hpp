#pragma once

#include "PlayState.hpp"
#include "Button.hpp"

class MainMenu : public States
{
private:
	std::string gameTitle;

	Font font;

	Text titleText;
	Color textColor;

	Button* playButton;
	Button* quitButton;

	void SetUpText();

	void CheckForMouseHover(Vector2i mousePos);
	void CheckForMouseClick(Vector2i mousePos);
	void MouseInput();

public:
	MainMenu(RenderWindow* window);
	virtual ~MainMenu();

	void MoveToNextState(std::stack<States*>* states);
	void Update();
	void Render();
};