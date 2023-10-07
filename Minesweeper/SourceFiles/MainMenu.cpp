#include "MainMenu.hpp"

MainMenu::MainMenu(RenderWindow* window) : States(window)
{
	std::cout << "Starting MainMenu \n";
	gameTitle = "MINESWEEPER";
	textColor = Color(255, 255, 255, 255);
	font.loadFromFile("Assets/Fonts/static/Orbitron-ExtraBold.ttf");
	SetUpText();
}

MainMenu::~MainMenu()
{
	std::cout << "Exiting MainMenu\n";
}

void MainMenu::SetUpText()
{
	titleText.setFont(font);
	titleText.setCharacterSize(80);
	titleText.setFillColor(textColor);
	titleText.setString(gameTitle);
	titleText.setPosition(
		window->getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f,
		window->getSize().x / 3.f
	);
	playButton = new Button("PLAY", Color(80, 80, 80, 255), 40);
	playButton->SetPosition(
		window->getSize().x / 2.f - playButton->GetBounds().x / 2.f,
		titleText.getPosition().y + window->getSize().x / 3.f
	);
	quitButton = new Button("QUIT", Color(80, 80, 80, 255), 40);
	quitButton->SetPosition(
		window->getSize().x / 2.f - quitButton->GetBounds().x / 2.f,
		playButton->GetPosition().y + playButton->GetBounds().y + 20.f
	);
}

void MainMenu::CheckForMouseHover(Vector2i mousePos)
{
	playButton->CheckForMouseHover(mousePos);
	quitButton->CheckForMouseHover(mousePos);
}

void MainMenu::CheckForMouseClick(Vector2i mousePos)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (playButton->IsPressed(mousePos))
		{
			playState = true;
		}
		if (quitButton->IsPressed(mousePos))
		{
			quitState = true;
			window->close();
		}
	}
}

void MainMenu::MouseInput()
{
	Vector2i mousePos = Mouse::getPosition(*window);
	CheckForMouseHover(mousePos);
	CheckForMouseClick(mousePos);
}

void MainMenu::MoveToNextState(std::stack<States*>* states)
{
	states->push(new PlayState(window));
}

void MainMenu::Update()
{
	MouseInput();
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		quitState = true;
	}
}

void MainMenu::Render()
{
	window->draw(titleText);
	playButton->Render(window);
	quitButton->Render(window);
}