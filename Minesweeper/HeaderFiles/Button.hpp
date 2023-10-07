#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>

using namespace sf;

class Button
{
private:
	std::string buttonName;
	Font font;
	Text buttonText;
	Color defaultColor;
	Color highlightedColor;

public:
	Button(std::string name, Color, float size);
	virtual ~Button();

	void SetPosition(float x, float y);

	// Mouse Input
	void  CheckForMouseHover(Vector2i mousePos);
	bool IsPressed(Vector2i mousePos);

	Vector2f GetBounds();
	Vector2f GetPosition();

	void Render(RenderWindow* window);
};