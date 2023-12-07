#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/b2_body.h>
#include "Renderer.h"
#include "Physics.h"
#include "Animation.h"


class Character : public ContactListener
{
private:
	FixtureData fixtureData;

	Animation runAnimation;
	sf::Texture textureToDraw;
	sf::Sound jumpSound;

	b2Body* body;
	b2Fixture* groundFixture;
	size_t isGrounded = 0; // bool плохо работал
	bool dirLeft = false;

	size_t coins;
public:
	sf::Vector2f position;
	float angle;
	size_t GetCoins();


	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& ren);

	// Унаследовано через ContactListener
	virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) override;
};