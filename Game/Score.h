#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Score
{
private:
	Font font;
	Text scoreText;
	Text highText;
	Text startText;
	Vector2f scorePosition;
	Vector2f highPosition;
	Vector2f startPosition;
public:
	unsigned int score;
	unsigned int highScore;

	Score();
	void update(RenderWindow*, Vector2f, bool);
	void reset();
};