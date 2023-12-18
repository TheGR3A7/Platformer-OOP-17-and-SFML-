#define _USE_MATH_DEFINES
#include "Spike.h"
#include <cmath>
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include "Game.h"

void Spike::Begin()
{
	tag = "spike";

	fixtureData.object = this;
	fixtureData.type = FixtureDataType::Object;

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);


	b2PolygonShape shape;
	shape.SetAsBox(0.4f, 0.4f); // поменять

	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f; // трение
	body->CreateFixture(&fixtureDef);

	body->SetTransform(b2Vec2(position.x, position.y + 0.2f), angle); // сместил хитбок на 0.2 вниз
}

void Spike::Update(float deltaTime)
{
}

void Spike::Render(Renderer& ren)
{
	ren.Draw(Resources::textures["spike.png"], sf::Vector2f(position.x, position.y + 0.2f), sf::Vector2f(0.8f, 0.8f), angle);
}

void Spike::OnContact(b2Fixture* self, b2Fixture* other)
{
	if (player.GetGroundFixture() == self)
		player.isDead = true;
}
