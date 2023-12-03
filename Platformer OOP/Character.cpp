#include "Character.h"
#include "Resources.h"


const float movementSpeed = 200.0f;

void Character::Update(float deltaTime)
{
	float move = movementSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		move *= 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		position.x += move * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		position.x -= move * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		position.y -= move * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		position.y += move * deltaTime;
}

void Character::Draw(Renderer& ren)
{
	ren.Draw(Resources::textures["sand.png"], position, sf::Vector2f(16.0f, 32.0f));
}
