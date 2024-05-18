#include "Platform.h"
#include "definitions.h"
#include <iostream>
#include <random>

std::default_random_engine generator;

// A Default platform with fixed position and size
Platform::Platform(Vector2f position, float size)
{
	this->type = NORMAL;

	this->texture.loadFromFile("Assets/platform.png");
	this->platformBox.setTexture(&this->texture);

	this->size = Vector2f(this->texture.getSize().x * size, this->texture.getSize().y);

	this->platformBox.setSize(this->size);
	this->platformBox.setOrigin(this->size.x / 2.f, this->size.y / 2.f);

	this->position = position;
	this->platformBox.setPosition(position);


}

// A platform with random position, size and type
Platform::Platform(float lastY)
{
	// Further randomize the random generator
	generator.discard(time(NULL)%50);

	// Picking the type of the platform
	std::uniform_real_distribution<float> pType(0, 100);
	int x = pType(generator);
	if (x < 60)
	{
		this->type = NORMAL;
		this->texture.loadFromFile("Assets/platform.png");
	} 
	else if (x < 97)
	{
		this->type = FRAIL;
		this->texture.loadFromFile("Assets/platform-frail.png");
	} 
	else 
	{
		this->type = BOOST;
		this->texture.loadFromFile("Assets/platform-boost.png");
	}

	this->platformBox.setTexture(&this->texture);

	// Size and position
	std::uniform_int_distribution<int> sizeDistribution(1, 8);
	sizeDistribution.reset();
	this->size = Vector2f(this->texture.getSize().x * (sizeDistribution(generator) / 8.f + 1), this->texture.getSize().y);

	this->platformBox.setSize(this->size);
	this->platformBox.setOrigin(this->size.x / 2.f, this->size.y / 2.f);

	std::uniform_real_distribution<float> xPosDistribution(30, WIN_HEIGHT * 1.5f - 30);
	std::uniform_real_distribution<float> YPosDistribution(5, 150);

	this->position = Vector2f(xPosDistribution(generator), lastY - YPosDistribution(generator));
	this->platformBox.setPosition(position);

}

void Platform::update(RenderWindow* window) const
{
	window->draw(platformBox);
}

Vector2f Platform::getPosition()
{
	return Vector2f(this->position);
}

RectangleShape* Platform::getPlatformBox()
{
	return &this->platformBox;
}

FloatRect Platform::getRect()
{
	return this->platformBox.getGlobalBounds();
}

// Collision shape of the platform
FloatRect Platform::getCollisionBox()
{
	return FloatRect(this->position.x - (this->size.x / 2.f), this->position.y - (this->size.y / 2.f), this->size.x, this->size.y);
}


