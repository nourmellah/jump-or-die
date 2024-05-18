#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Background
{
private:
	float yCenter;
public:
	Sprite bgSprite;
	Texture bgTexture;


	Background();
	void update(RenderWindow*, float);
};

