#define _USE_MATH_DEFINES
#include "Saw.h"
#include <cmath>
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_circle_shape.h>

void Saw::Begin()
{
	tag = "saw";

	animation = Animation(0.8f,
		{
			AnimFrame(0.7f, Resources::textures["saw1.png"]),
			AnimFrame(0.6f, Resources::textures["saw2.png"]),
			AnimFrame(0.5f, Resources::textures["saw3.png"]),
			AnimFrame(0.4f, Resources::textures["saw4.png"]),
			AnimFrame(0.3f, Resources::textures["saw5.png"]),
			AnimFrame(0.2f, Resources::textures["saw6.png"]),
			AnimFrame(0.1f, Resources::textures["saw7.png"]),
			AnimFrame(0.0f, Resources::textures["saw8.png"]),
		});

	fixtureData.object = this;
	fixtureData.type = FixtureDataType::Object;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = 1.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f; // трение
	body->CreateFixture(&fixtureDef);
}

void Saw::Update(float deltaTime)
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

void Saw::Render(Renderer& ren)
{
	ren.Draw(animation.GetTexture(), position, sf::Vector2f(2.0f, 2.0f), angle);
}

