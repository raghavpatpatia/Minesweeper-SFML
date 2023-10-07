#include "PlayState.hpp"

PlayState::PlayState(RenderWindow* window) : States(window) 
{
	std::cout << "Starting Play State" << std::endl;
	borderOffset = Vector2f(20.f, 20.f);
	isGameStart = false;
	showPopup = false;
	font.loadFromFile("Assets/Fonts/static/Orbitron-Regular.ttf");
	CreateGameArea();
	CreateButtons();
	ResetGame();
}

void PlayState::CreateGameArea()
{
	float screenWidth = window->getSize().x;
	float screenMid = window->getSize().x / 2;
	gameArea.setFillColor(Color(0, 0, 0, 0));
	gameArea.setPosition(borderOffset.x, borderOffset.y);
	gameArea.setSize(Vector2f(
		screenWidth - borderOffset.x * 2,
		screenWidth - borderOffset.x * 2
	));
	gameArea.setOutlineThickness(3.f);
	gameArea.setOutlineColor(Color(120, 120, 120, 255));
}

void PlayState::CreateButtons()
{
	resetButton = new Button("RESET", Color(80, 80, 80, 255), 40.f);
	float screenMid = window->getSize().x / 2;
	resetButton->SetPosition
	(
		screenMid - resetButton->GetBounds().x / 2,
		window->getSize().y - resetButton->GetBounds().y - 30.f
	);
}

void PlayState::ResetGame()
{
	isGameStart = false;
	ResetTime();
	ResetBombs();
	board.CreateNewBoard(gameArea, bombCount);
	HidePopup();
}

void PlayState::ResetTime()
{
	float textSize = 40.0f;
	timeText.setFont(font);
	timeText.setCharacterSize(textSize);
	timeText.setPosition(
		gameArea.getPosition().x,
		gameArea.getPosition().y + gameArea.getGlobalBounds().height + 20);
	timeText.setString("TIME : 0");
	timer.restart();
	playTime = 0;
}

void PlayState::ResetBombs()
{
	bombCount = BOMB_COUNT;
	float textSize = 40.0f;
	bombText.setFont(font);
	bombText.setCharacterSize(textSize);
	bombText.setPosition
	(
		5 * gameArea.getGlobalBounds().width / 7,
		gameArea.getPosition().y + gameArea.getGlobalBounds().height + 20
	);
	UpdateBomb();
}

void PlayState::UpdateBomb()
{
	std::stringstream ss;
	ss << "Bombs: ";
	ss << bombCount;
	bombText.setString(ss.str());
}

void PlayState::UpdateTime()
{
	if (!isGameStart) { return; }

	if (timer.getElapsedTime().asSeconds() > 1)
	{
		playTime += timer.getElapsedTime().asSeconds();
		timer.restart();

		std::stringstream ss;
		ss << "TIME: ";
		ss << playTime;
		timeText.setString(ss.str());
	}
}

void PlayState::ShowPopup(const std::string& message)
{
	showPopup = true;
	popupBackground.setSize(Vector2f(400.f, 200.f));
	popupBackground.setFillColor(Color(0, 0, 0, 200));
	popupBackground.setPosition(
		window->getSize().x / 2 - popupBackground.getSize().x / 2,
		window->getSize().y / 2 - popupBackground.getSize().y / 2
	);
	PopupText.setFont(font);
	PopupText.setString(message);
	PopupText.setCharacterSize(40);
	PopupText.setFillColor(Color::White);
	PopupText.setPosition(
		window->getSize().x / 2 - PopupText.getGlobalBounds().width / 2,
		popupBackground.getPosition().y + 20
	);
	restartButton = new Button("RESTART", Color(80, 80, 80, 255), 30.f);
	restartButton->SetPosition(
		window->getSize().x / 2 - restartButton->GetBounds().x - 20.f,
		popupBackground.getPosition().y + popupBackground.getSize().y - restartButton->GetBounds().y - 20.f
	);
	quitButton = new Button("QUIT", Color(80, 80, 80, 255), 30.f);
	quitButton->SetPosition(
		window->getSize().x / 2 - quitButton->GetBounds().x + 170.f,
		popupBackground.getPosition().y + popupBackground.getSize().y - quitButton->GetBounds().y - 20.f
	);
}

void PlayState::HidePopup()
{
	showPopup = false;
}

PlayState::~PlayState()
{
	delete resetButton;
	delete restartButton;
	delete quitButton;
	std::cout << "Exiting PlayState\n";
}

void PlayState::MoveToNextState(std::stack<States*>* states)
{
	return;
}

void PlayState::PlayGame(bool isLeftClick, bool isRightClick, Vector2i mousePos)
{
	if (!isGameStart && timer.getElapsedTime().asSeconds() > 0.5f)
	{
		isGameStart = true;
		timer.restart();
	}

	if (isLeftClick)
	{
		board.LeftButton(mousePos);
	}
	if (isRightClick)
	{
		board.RightButton(mousePos);
	}

	if (board.IsWin())
	{
		ShowPopup("You Win!");
	}
	else if (board.IsLoss())
	{
		ShowPopup("You Lose!");
	}
	bombCount = board.GetRemainingBombs();
	UpdateBomb();
}

void PlayState::CheckForMouseClick(Vector2i mousePos)
{
	bool isLeftClick = Mouse::isButtonPressed(Mouse::Left);
	bool isRightClick = Mouse::isButtonPressed(Mouse::Right);
	if (showPopup)
	{
		if (restartButton->IsPressed(mousePos) && isLeftClick)
		{
			ResetGame();
		}
		else if (quitButton->IsPressed(mousePos) && isLeftClick)
		{
			window->close();
		}
	}
	else
	{
		if (resetButton->IsPressed(mousePos) && isLeftClick)
		{
			ResetGame();
		}
		else
		{
			PlayGame(isLeftClick, isRightClick, mousePos);
		}
	}
}

void PlayState::CheckForMouseHover(Vector2i mousePos)
{
	if (showPopup)
	{
		restartButton->CheckForMouseHover(mousePos);
		quitButton->CheckForMouseHover(mousePos);
	}
	else
	{
		resetButton->CheckForMouseHover(mousePos);
	}
}

void PlayState::CheckExitState()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window->close();
	}
}

void PlayState::Update()
{
	Vector2i mousePos = Mouse::getPosition(*window);
	CheckForMouseHover(mousePos);
	CheckForMouseClick(mousePos);
	CheckExitState();
	UpdateTime();
}

void PlayState::Render()
{
	window->draw(gameArea);
	board.RenderBoard(window);

	if (showPopup)
	{
		window->draw(popupBackground);
		window->draw(PopupText);
		restartButton->Render(window);
		quitButton->Render(window);
	}
	else
	{
		resetButton->Render(window);
	}
	window->draw(timeText);
	window->draw(bombText);
}
