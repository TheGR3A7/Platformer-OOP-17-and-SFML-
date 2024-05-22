#pragma once
#include <SFML/Audio.hpp>
#include "Object.h"
#include "Animation.h"
#include "Physics.h"
#include <box2d/b2_body.h>
#include "Character.h"

class Jumping : public Object
{
private:
	sf::Texture textureToDraw;
	b2Body* body;

	float boostTimer = 0.0f;
	bool isCollected = false;
public:
	~Jumping();

	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;
	virtual void OnContact(b2Fixture* self, b2Fixture* other) override;

	void Collected();
	bool IsCollected();
};