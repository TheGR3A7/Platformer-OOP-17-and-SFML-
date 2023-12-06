#pragma once
#include "Renderer.h"

using namespace std;

class Object
{
public:
	sf::Vector2f position;
	float angle;
	string tag;

	virtual void Begin() {}
	virtual void Update(float deltaTime) {}
	virtual void Render(Renderer& ren) {}
};

