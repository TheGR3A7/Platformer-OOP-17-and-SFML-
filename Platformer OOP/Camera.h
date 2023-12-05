#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
private:
	sf::Vector2f viewSize;
public:
	float zoomLevel;
	sf::Vector2f position;

	Camera(float zoomLevel = 5.0f);
	sf::Vector2f GetViewSize();
	sf::View GetView(sf::Vector2u winSize);
};