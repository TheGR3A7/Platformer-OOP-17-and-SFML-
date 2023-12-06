#pragma once
#include "Renderer.h"

class Object
{
public:
	sf::Vector2f position;
	float angle;

	virtual void Begin() {}
	virtual void Update(float deltaTime) {}
	virtual void Render(Renderer& ren) {}
};

