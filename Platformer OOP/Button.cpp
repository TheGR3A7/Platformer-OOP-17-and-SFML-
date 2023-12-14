#include "Button.h"
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

void Button::Begin()
{
	tag = "button";

	activeAnimation = Animation(0.5f,
		{
			AnimFrame(0.32f, Resources::textures["button4.png"]),
			AnimFrame(0.16f, Resources::textures["button3.png"]),
			AnimFrame(0.0f, Resources::textures["button2.png"]),
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

void Button::Update(float deltaTime)
{
	if (!isActivated)
	{
		textureToDraw = Resources::textures["button1.png"];
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


void Button::Render(Renderer& ren)
{
	ren.Draw(textureToDraw, position, sf::Vector2f(1.0f, 1.0f), angle);
}

void Button::Activated()
{
	isActivated = true;
	activationTimer.restart();
}

void Button::Deactivate()
{
	isActivated = false;
	textureToDraw = Resources::textures["button1.png"];
}