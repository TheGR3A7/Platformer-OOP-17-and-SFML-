#pragma once
#include "Object.h"
#include "Animation.h"
#include "Physics.h"
#include <box2d/b2_body.h>
#include "Character.h"

class Trampoline : public Object
{
private:
	Animation activeAnimation;
	sf::Texture textureToDraw;
	FixtureData fixtureData;
	b2Body* body;

	//sf::Clock activationTimer; 
	float activationTimer = 0.0f;
	float activationDuration = 0.5f; 

	bool isActivated = false;
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;
	virtual void OnContact(b2Fixture* self, b2Fixture* other) override;

	void Activated();
	void Deactivate();
};

