#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum pType {
	NORMAL, FRAIL, BOOST
};

class Platform
{
private:
	Vector2f position;

	Texture texture;
	Vector2f size;
	RectangleShape platformBox;

public:
	pType type;

	Platform(Vector2f, float);
	Platform(float lastY);
	void update(RenderWindow*) const;
	Vector2f getPosition();
	RectangleShape* getPlatformBox();
	FloatRect getRect();
	FloatRect getCollisionBox();
};
