#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
	float zoomLevel;
	sf::Vector2f position;

	Camera(float zoomLevel = 5.0f);
	sf::View GetView(sf::Vector2u winSize);
};