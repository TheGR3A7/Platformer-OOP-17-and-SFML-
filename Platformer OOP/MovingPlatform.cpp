#define _USE_MATH_DEFINES
#include "MovingPlatform.h"
#include <cmath>
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_collision.h>

void MovingPlatform::Begin()
{
	tag = "platform";

	animation = Animation(0.8f,
		{
			AnimFrame(0.6f, Resources::textures["platform4.png"]),
			AnimFrame(0.4f, Resources::textures["platform3.png"]),
			AnimFrame(0.2f, Resources::textures["platform2.png"]),
			AnimFrame(0.0f, Resources::textures["platform1.png"]),
		});

	fixtureData.object = this;
	fixtureData.type = FixtureDataType::Object;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);


	b2PolygonShape shape;
	shape.SetAsBox(1.0f, 0.5f); // поменять

	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f; // трение
	body->CreateFixture(&fixtureDef);
}

void MovingPlatform::Update(float deltaTime)
{
	animation.Update(deltaTime);

	b2Vec2 velocity = body->GetLinearVelocity();

	if (abs(velocity.y) <= 0.1f)
		movement *= -1.0f;

	velocity.y = movement;

	body->SetLinearVelocity(velocity);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);
}

void MovingPlatform::Render(Renderer& ren)
{
	ren.Draw(animation.GetTexture(), position, sf::Vector2f(2.0f, 1.0f), angle);
}


