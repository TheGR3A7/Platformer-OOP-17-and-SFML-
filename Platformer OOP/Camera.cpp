#include "Camera.h"

Camera::Camera(float zoomLevel)
	: zoomLevel(zoomLevel) 
{
}

sf::View Camera::GetView(sf::Vector2u winSize)
{
	float dt = (float)winSize.x / (float)winSize.y;
	sf::Vector2f size;
	if (dt < 1.0f)
		size = sf::Vector2f(zoomLevel, zoomLevel / dt);
	else
		size = sf::Vector2f(zoomLevel * dt, zoomLevel);
	return sf::View(position, size);
}
