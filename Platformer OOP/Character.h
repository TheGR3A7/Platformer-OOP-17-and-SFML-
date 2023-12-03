#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>
#include "Renderer.h"


class Character
{
private:
	b2Body* body;
public:
	sf::Vector2f position;
	float angle;

	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& ren);
};