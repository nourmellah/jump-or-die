#include "Background.h"
#include "definitions.h"

Background::Background()
{
	this->bgTexture.loadFromFile("Assets/bg_texture.png");
	this->bgTexture.setRepeated(true);
	this->bgSprite.setTexture(bgTexture);
	this->bgSprite.setTextureRect( { 0, 0, WIN_WIDTH * 100, WIN_HEIGHT } );
	this->yCenter = WIN_HEIGHT / 2.f;
}

void Background::update(RenderWindow* window, float yCameraCenter)
{
	this->bgSprite.move(Vector2f(-0.5f, yCameraCenter - yCenter));
	window->draw(bgSprite);
	this->yCenter = yCameraCenter;
}
