#include "Player.h"
#include "Platform.h"
#include "definitions.h"
#include <iostream>

Player::Player()
{
	// Preparing the texture
	this->texture.loadFromFile("Assets/player.png");
	this->playerBox.setTexture(&this->texture);
	this->size = Vector2f(this->texture.getSize());
	this->playerBox.setSize(this->size);
	this->playerBox.setOrigin(this->size.x / 2.f, this->size.y / 2.f);

	// Preparing physics
	this->position = Vector2f(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f);
	this->playerBox.setPosition(this->position);
	this->velocity = Vector2f(0,-10);
}

void Player::move()
{
	// Get Mouse position (originally, mouse.x is off by 150 for some reason)
	Vector2i newMousePos = Vector2i(Mouse::getPosition().x-150, Mouse::getPosition().y);
	velocity.x = newMousePos.x - position.x;
	velocity.y += gravity;

	// Update position
	position = Vector2f(newMousePos.x, position.y + velocity.y);
	this->playerBox.setPosition(position);
	
	// Change orientation
	if (velocity.x < 0) playerBox.setScale(-1.f, 1.f);
	else if (velocity.x > 0) playerBox.setScale(1.f, 1.f);
}

void Player::update(RenderWindow* window) const
{
	window->draw(this->playerBox);
}

// Reset the player to original state
void Player::reset()
{
	this->position = Vector2f(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f);
	this->playerBox.setPosition(this->position);
	this->velocity = Vector2f(0, -10);
}

void Player::setVelocity(Vector2f velocity)
{
	this->velocity = velocity;
}

Vector2f Player::getVelocity()
{
	return this->velocity;
}

Vector2f Player::getPosition()
{
	return Vector2f(this->position);
}

FloatRect Player::getRect()
{
	return this->playerBox.getGlobalBounds();
}

// Collision shape of the player
FloatRect Player::getCollisionBox()
{
	return FloatRect(this->position.x - (this->size.x / 2.f), this->position.y + (this->size.y / 2.f) - 5, this->size.x, 10);
}


