#pragma once
#include "Enemy.h"
#include "Character.h"

class Hedgehog : public Enemy
{
private:
	Animation walkAnimation;
	Animation sleepAnimation;
	sf::Texture textureToDraw;
	float movement = 5.0f;
	bool dirLeft = false;

	float destroyTimer = 0.0f;
	bool isDead = false;

	FixtureData fixtureData;
	b2Body* body;

	float sleepTimer = 0.0f;
	float walkTimer = 0.0f;
	bool isSleeping = false;
	float sleepDuration = 2.0f;
	float walkDuration = 4.0f;

public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;

	virtual void Die() override;
	virtual bool IsDead() override;
	virtual void OnContact(b2Fixture* self, b2Fixture* other) override;

	bool IsSleeping();
	void Sleep();
	void WakeUp();
};

