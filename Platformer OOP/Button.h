#pragma once
#include "Object.h"
#include "Animation.h"
#include "Physics.h"
#include <box2d/b2_body.h>

class Button : public Object
{
private:
	Animation activeAnimation;
	sf::Texture textureToDraw;
	FixtureData fixtureData;
	b2Body* body;

	sf::Clock activationTimer;
	float activationDuration = 0.3f;

	bool isActivated = false;
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;

	void Activated();
	void Deactivate();
};

