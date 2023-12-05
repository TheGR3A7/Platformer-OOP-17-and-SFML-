#include "Camera.h"

Camera::Camera(float zoomLevel)
	: zoomLevel(zoomLevel) 
{
}

sf::Vector2f Camera::GetViewSize()
{
	return viewSize;
}

sf::View Camera::GetView(sf::Vector2u winSize)
{
	float dt = (float)winSize.x / (float)winSize.y;
	if (dt < 1.0f)
		viewSize = sf::Vector2f(zoomLevel, zoomLevel / dt);
	else
		viewSize = sf::Vector2f(zoomLevel * dt, zoomLevel);
	return sf::View(position, viewSize);
}
