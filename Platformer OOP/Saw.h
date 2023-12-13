#pragma once
#include "Object.h"
#include "Animation.h"
#include "Physics.h"
#include <box2d/b2_body.h>

class Saw : public Object
{
private:
	Animation animation;
	FixtureData fixtureData;
	b2Body* body;

	float movement = 3.0f;
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;
};

