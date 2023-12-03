#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"


class Character
{
public:
	sf::Vector2f position;
	float angle;

	void Update(float deltaTime);
	void Draw(Renderer& ren);
};