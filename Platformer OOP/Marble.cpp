#include "Marble.h"
#include <iostream>
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include "Game.h"
#include "Character.h"

Marble::~Marble()
{
    Physics::world->DestroyBody(body);
}

void Marble::Begin()
{
    tag = "marble";

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

void Marble::Update(float deltaTime)
{
	timer += deltaTime;
	if (timer >= 2.f)
	{
		timer = 0;
		if (isVisible)
		{
			Physics::world->DestroyBody(body);
			position.x = 200;
			position.y = 200;
			//DeleteObject(this);
			isVisible = false;	
		}
		else
		{
			position.x = pos_x;
			position.y = pos_y;
			isVisible = true;
			Begin();
		}
	}
}

void Marble::Render(Renderer& ren)
{
    ren.Draw(Resources::textures["marble.png"], isVisible ? position : sf::Vector2f(position.x, position.y), sf::Vector2f(1.0f, 1.0f), angle);
}

void Marble::OnContact(b2Fixture* self, b2Fixture* other)
{
	if (player.GetGroundFixture() == self)
		player.IncreaseGrounded();
}

void Marble::OnEndContact(b2Fixture* self, b2Fixture* other)
{
	if (player.GetGroundFixture() == self)
		player.DecreaseGrounded();
}
