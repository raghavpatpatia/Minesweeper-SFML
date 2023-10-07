#include "Button.hpp"

Button::Button(std::string name, Color color, float size)
{
	defaultColor = color;
	highlightedColor = Color(255, 255, 255, 255);
	buttonName = name;

	font.loadFromFile("Assets/Fonts/static/Orbitron-Regular.ttf");
	buttonText.setFont(font);
	buttonText.setString(buttonName);
	buttonText.setCharacterSize(size);
	buttonText.setFillColor(defaultColor);
}

Button::~Button(){}

void Button::SetPosition(float x, float y)
{
	buttonText.setPosition(x, y);
}

// Mouse Input
void  Button::CheckForMouseHover(Vector2i mousePos) 
{
	if (buttonText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
	{
		buttonText.setFillColor(highlightedColor);
	}
	else
	{
		buttonText.setFillColor(defaultColor);
	}
}

bool Button::IsPressed(Vector2i mousePos)
{
	return buttonText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

Vector2f Button::GetBounds()
{
	return Vector2f(buttonText.getGlobalBounds().width, buttonText.getGlobalBounds().height);
}

Vector2f Button::GetPosition()
{
	return buttonText.getPosition();
}

void Button::Render(RenderWindow* window)
{
	window->draw(buttonText);
}