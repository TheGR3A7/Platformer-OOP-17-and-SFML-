#pragma once
#include "Object.h"
#include "Physics.h"
#include <box2d/b2_body.h>

class Spike : public Object
{
private:
	sf::Texture textureToDraw;
	FixtureData fixtureData;
	b2Body* body;
	b2Vec2 velocity;

public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;
};

