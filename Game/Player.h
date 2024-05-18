#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Player
{
private:

	const float gravity = 0.5f;
	Vector2f position;
	Vector2f velocity;

	Texture texture;
	Vector2f size;
	RectangleShape playerBox;

public:
	Player();
	void move();
	void update(RenderWindow*) const;
	void reset();
	void setVelocity(Vector2f);
	Vector2f getVelocity();
	Vector2f getPosition();
	FloatRect getRect();
	FloatRect getCollisionBox();
};

