#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/b2_body.h>
#include "Animation.h"
#include "Renderer.h"
#include "Physics.h"


class Character : public ContactListener
{
private:
	Animation runAnimation;
	sf::Texture textureToDraw;
	sf::Sound jumpSound;

	FixtureData fixtureData;
	bool dirLeft = false;

public:
	//
	sf::Sound coinSound;
	b2Body* body;

	size_t isGrounded; // bool плохо работал
	b2Fixture* groundFixture;
	size_t coins;

	//
	sf::Vector2f position;
	float angle;
	bool isDead;

	size_t GetCoins();
	
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& ren);

	// Унаследовано через ContactListener
	virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) override;
};