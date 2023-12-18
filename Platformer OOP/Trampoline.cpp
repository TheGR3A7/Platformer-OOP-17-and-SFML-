#include "Trampoline.h"
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include "Game.h"

void Trampoline::Begin() 
{
	tag = "trampoline";

	activeAnimation = Animation(0.5f,
		{
			AnimFrame(0.4f, Resources::textures["tramp2.png"]),
			AnimFrame(0.3f, Resources::textures["tramp3.png"]),
			AnimFrame(0.2f, Resources::textures["tramp4.png"]),
			AnimFrame(0.1f, Resources::textures["tramp3.png"]),
			AnimFrame(0.0f, Resources::textures["tramp2.png"]),
		});


	fixtureData.object = this;
	fixtureData.type = FixtureDataType::Object;

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.4f); // поменять

	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f; // трение
	body->CreateFixture(&fixtureDef);
}

void Trampoline::Update(float deltaTime)
{
	if (!isActivated)
	{
		textureToDraw = Resources::textures["tramp1.png"];
	}
	else
	{
		textureToDraw = activeAnimation.GetTexture();

		if (activationTimer.getElapsedTime().asSeconds() > activationDuration)
		{
			Deactivate();
		}
	}

	activeAnimation.Update(deltaTime);
}


void Trampoline::Render(Renderer& ren)
{
	ren.Draw(textureToDraw, position, sf::Vector2f(1.0f, 1.0f), angle);
}

void Trampoline::OnContact(b2Fixture* self, b2Fixture* other)
{
	if (player.groundFixture == self)
	{
		Activated();
		b2Vec2 jumpVelocity = player.body->GetLinearVelocity();
		jumpVelocity.y = -17.0f;
		player.body->SetLinearVelocity(jumpVelocity);
	}
}

void Trampoline::Activated()
{
	isActivated = true;
	activationTimer.restart(); 
}

void Trampoline::Deactivate()
{
	isActivated = false;
	textureToDraw = Resources::textures["tramp1.png"];
}