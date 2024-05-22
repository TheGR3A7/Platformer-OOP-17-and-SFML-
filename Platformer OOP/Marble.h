#pragma once
#include <SFML/Audio.hpp>
#include "Object.h"
#include "Physics.h"
#include <box2d/b2_body.h>
#include "Character.h"


class Marble : public Object
{
private:
	sf::Texture textureToDraw;
	FixtureData fixtureData;
	b2Body* body;
	float pos_x, pos_y;
	bool isVisible = true;
	float timer = 0.0f;
public:
	~Marble();

	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;
	virtual void OnContact(b2Fixture* self, b2Fixture* other) override;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) override;
};

