#include "Sand.h"
#include <iostream>
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include "Game.h"
#include "Character.h"

Sand::~Sand()
{
	Physics::world->DestroyBody(body);
}

void Sand::Begin()
{
	tag = "sand";

	fixtureData.object = this;
	fixtureData.type = FixtureDataType::Object;

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	pos_x = position.x;
	pos_y = position.y;
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
}

void Sand::Update(float deltaTime)
{
	if (isVisible == false)
	{
		timer += deltaTime;
		if (timer >= 3.0f)
		{
			Physics::world->DestroyBody(body);
			DeleteObject(this);
		}
	}
}

void Sand::Render(Renderer& ren)
{
	ren.Draw(Resources::textures["sand.png"], isVisible ? position : sf::Vector2f(position.x, position.y), sf::Vector2f(1.0f, 1.0f), angle);
}

void Sand::OnContact(b2Fixture* self, b2Fixture* other)
{
	if (player.GetGroundFixture() == self)
	{
		player.IncreaseGrounded();
		isVisible = false;
	}
}

void Sand::OnEndContact(b2Fixture* self, b2Fixture* other)
{
	if (player.GetGroundFixture() == self)
		player.DecreaseGrounded();
}
