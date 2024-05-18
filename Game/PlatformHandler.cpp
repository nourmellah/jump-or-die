#include "PlatformHandler.h"
#include "definitions.h"
#include <iostream>

PlatformHandler::PlatformHandler()
{
	Platform firstPlatform(Vector2f(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f + 100.f), 8);
	this->table.push_back(firstPlatform);
	this->size = 0;
}

PlatformHandler::~PlatformHandler()
{
	this->table.clear();
}

void PlatformHandler::update(RenderWindow* window, float yCameraCenter)
{
	while (this->table.back().getPosition().y > yCameraCenter - WIN_HEIGHT / 2.f) {
		add(this->table.back().getPosition().y);
	}

	for (Platform i : this->table) {
		i.update(window);
	}
	if (this->table.front().getPosition().y > yCameraCenter + WIN_HEIGHT / 2.f) del(this->table.begin());
}

void PlatformHandler::add(float lastY)
{
	Platform newPlatform(lastY);
	this->table.push_back(newPlatform);
	this->size++;
}

void PlatformHandler::del(vector<Platform>::iterator position)
{
	this->table.erase(position);
	this->size--;
}

void PlatformHandler::reset()
{
	this->table.clear();
	Platform firstPlatform(Vector2f(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f + 100.f), 8);
	this->table.push_back(firstPlatform);
	this->size = 0;
}

unsigned int PlatformHandler::getSize()
{
	return this->size;
}
