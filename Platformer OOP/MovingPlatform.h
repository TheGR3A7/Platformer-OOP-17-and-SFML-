#pragma once
#include"Object.h"
#include "Animation.h"
#include "Physics.h"
#include <box2d/b2_body.h>
#include "Character.h"

class MovingPlatform : public Object
{
private:
	Animation animation;
	FixtureData fixtureData;
	b2Body* body;

	float movement = 5.0f;
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;
	virtual void OnContact(b2Fixture* self, b2Fixture* other) override;
};


