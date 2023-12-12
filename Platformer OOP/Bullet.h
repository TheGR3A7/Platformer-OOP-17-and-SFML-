#pragma once
#include "Object.h"

class Bullet : public Object
{
private:
	float speed;
	sf::Vector2f direction;

public:
	Bullet(sf::Vector2f position, float speed);
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;
};


