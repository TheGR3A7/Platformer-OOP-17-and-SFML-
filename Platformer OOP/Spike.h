#pragma once
#include "Object.h"
#include "Physics.h"
#include <box2d/b2_body.h>
#include "Character.h"

class Spike : public Object
{
private:
	sf::Texture textureToDraw;
	FixtureData fixtureData;
	b2Body* body;

public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;
	virtual void OnContact(b2Fixture* self, b2Fixture* other) override;
};

