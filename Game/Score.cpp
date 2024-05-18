#include "Score.h"
#include "definitions.h"
#include <iostream>

Score::Score()
{
	// Score set-up
	this->font.loadFromFile("Assets/Montserrat-Bold.ttf");
	this->scoreText.setFont(font);
	this->scorePosition = Vector2f(10, WIN_HEIGHT / 20.f);
	this->scoreText.setPosition(this->scorePosition);
	this->scoreText.setCharacterSize(48);
	this->scoreText.setFillColor(sf::Color::Red);

	// High score set-up
	this->highText.setFont(font);
	this->highPosition = Vector2f(WIN_WIDTH / 2.752f, WIN_HEIGHT / 5.f);
	this->highText.setPosition(this->highPosition);
	this->highText.setCharacterSize(48);
	this->highText.setFillColor(sf::Color::Red);

	// Start text set-up
	this->startText.setFont(font);
	this->startPosition = Vector2f(WIN_WIDTH / 3.25f, WIN_HEIGHT / 3.f);
	this->startText.setPosition(this->startPosition);
	this->startText.setString("Click The Player to start!");
	this->startText.setCharacterSize(48);
	this->startText.setFillColor(sf::Color::Red);

	this->score = 0;
	this->highScore = 0;
	this->highText.setString("Highest Score: 0");
}

void Score::update(RenderWindow* window, Vector2f cameraCenter, bool gameOn)
{
	// Show only score if game has started
	if (gameOn)
	{
		Vector2i relativePos = window->mapCoordsToPixel(Vector2f(WIN_WIDTH / 2.f, WIN_HEIGHT / 20.f));

		this->scorePosition = Vector2f(10, cameraCenter.y - WIN_HEIGHT / 2.f);
		this->scoreText.setPosition(scorePosition);

		this->score = (WIN_HEIGHT / 2 - cameraCenter.y) / 10;
		this->scoreText.setString("Score: " + std::to_string(this->score));

		window->draw(this->scoreText);
	}
	// Show high score and start text otherwise
	else
	{
		window->draw(this->highText);
		window->draw(this->startText);
	}
}

void Score::reset()
{
	// Reset score and update high score
	this->highScore = std::max(this->highScore,this->score);
	this->score = 0;
	this->highText.setString("Highest Score: "+std::to_string(this->highScore));
}
