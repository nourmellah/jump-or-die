#pragma once
#include <SFML/Graphics.hpp>
#include <vector> 
#include "Platform.h"

using namespace std;
using namespace sf;

class PlatformHandler
{
private:
	unsigned int size;
public:
	vector<Platform> table;

	PlatformHandler();
	~PlatformHandler();
	void update(RenderWindow*, float);
	void add(float);
	void del(vector<Platform>::iterator);
	void reset();
	unsigned int getSize();
};

