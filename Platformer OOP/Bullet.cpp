#include "Bullet.h"
#include "Resources.h"


Bullet::Bullet(sf::Vector2f position, float speed) : direction(position.x, position.y), speed(speed)
{
	this->position = position;
}

void Bullet::Begin() 
{
	tag = "bullet";
}

void Bullet::Update(float deltaTime)
{
	position += direction * speed * deltaTime;
}

void Bullet::Render(Renderer& ren)
{
	ren.Draw(Resources::textures["bullet.png"], position, sf::Vector2f(0.3f, 0.3f), angle);
}
