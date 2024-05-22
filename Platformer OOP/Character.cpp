#define _USE_MATH_DEFINES
#include "Character.h"
#include "Resources.h"
#include "Object.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <cmath>
#include <iostream>
#include "Game.h"
#include "Duck.h"
#include "Coin.h"
#include "Trampoline.h"
#include "Hedgehog.h"
#include "MovingPlatform.h"
#include "Spike.h"
#include "Saw.h"
#include "Flag.h"
#include "Jumping.h"
#include "Shield.h"
#include "Marble.h"
#include "Sand.h"

using namespace std;

const float movementSpeed = 7.0f;
float jumpVelocity = 15.0f;

void Character::Begin()
{
	runAnimation = Animation(0.72f,
		{
			AnimFrame(0.60f, Resources::textures["run6.png"]),
			AnimFrame(0.48f, Resources::textures["run5.png"]),
			AnimFrame(0.36f, Resources::textures["run4.png"]),
			AnimFrame(0.24f, Resources::textures["run3.png"]),
			AnimFrame(0.12f, Resources::textures["run2.png"]),
			AnimFrame(0.00f, Resources::textures["run1.png"]),
		});

	jumpSound.setBuffer(Resources::sounds["jump.wav"]);
	jumpSound.setVolume(50);

	coinSound.setBuffer(Resources::sounds["coin.wav"]);
	coinSound.setVolume(50);

	fixtureData.listener = this;
	fixtureData.character = this;
	fixtureData.type = FixtureDataType::Character;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true; // ������� �������� ���������
	body = Physics::world->CreateBody(&bodyDef);


	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData; //���������� ��������� � ������������ �������������� ���� ��� ���������� ��������� �� ������ 
	fixtureDef.density = 1.0f; 
	fixtureDef.friction = 0.0f; // ������

	b2CircleShape circleShape;
	circleShape.m_radius = 0.5f;
	circleShape.m_p.Set(0.0f, -0.5f);
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef); 

	circleShape.m_p.Set(0.0f, 0.5f);
	body->CreateFixture(&fixtureDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.5f, 0.5f);
	fixtureDef.shape = &polygonShape;// ������
	body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(0.4f, 0.2f, b2Vec2(0.0f, 1.0f), 0.0f);
	fixtureDef.isSensor = true;
	groundFixture = body->CreateFixture(&fixtureDef);
}

void Character::Update(float deltaTime)
{
	float move = movementSpeed;

	runAnimation.Update(deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && isGrounded)
		move *= 1.5f;

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += move;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= move;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded)
	{
		velocity.y = -jumpVelocity;
		jumpSound.play();
	}

	if (immortalityTimer > 0.0f)
	{
		immortalityTimer -= deltaTime; 
	}

	textureToDraw = runAnimation.GetTexture();

	if (velocity.x < -0.02f)
		dirLeft = true;
	else if (velocity.x > 0.02f) // else if ������ ��� ���� == 0, �� �� �� ������ ������ �������, ��� ������ else ��� �� �������
		dirLeft = false;
	else
		textureToDraw = Resources::textures["idle1.png"];


	if (!isGrounded)
		textureToDraw = Resources::textures["jump1.png"];
			

	body->SetLinearVelocity(velocity);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);

}

void Character::Draw(Renderer& ren)
{
	ren.Draw(textureToDraw, position, sf::Vector2f(dirLeft ? -1.0f : 1.0f, 2.0f), angle); // ���� ���� 1 ���� ������ � 1 ���� � ������(�� ������ ����� �������� ������ �� 16)
}

void Character::IncreaseCoins()
{
	++coins;
}

void Character::IncreaseGrounded()
{
	isGrounded++;
}

void Character::DecreaseGrounded()
{
	isGrounded--;
}

void Character::PlayCoinSound()
{
	coinSound.play();
}

b2Body* Character::GetBody()
{
	return body;
}

b2Fixture* Character::GetGroundFixture()
{
	return 	groundFixture;
}

float Character::GetJumpVelocity()
{
	return jumpVelocity;
}

void Character::SetJumpVelocity(float jump)
{
	jumpVelocity = jump;
}


void Character::OnBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (!data)
		return;

	if (groundFixture == self && data->type == FixtureDataType::MapTile) // +
		isGrounded++;
	if (groundFixture == self && data->type == FixtureDataType::Object && data->object->tag == "platform") // +
	{
		MovingPlatform* platform = dynamic_cast<MovingPlatform*>(data->object);
		if (!platform)
			return;
		else
			platform->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "coin") // +
	{
		Coin* coin = dynamic_cast<Coin*>(data->object);
		if (!coin)
			return;
		else
			coin->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "jumping") // +
	{
		Jumping* jumping = dynamic_cast<Jumping*>(data->object);
		if (!jumping)
			return;
		else
			jumping->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "shield") // +
	{
		Shield* shield = dynamic_cast<Shield*>(data->object);
		if (!shield)
			return;
		else
			shield->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "spike") // +
	{
		Spike* spike = dynamic_cast<Spike*>(data->object);
		if (!spike)
			return;
		else
			spike->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "saw") // +
	{
		Saw* saw = dynamic_cast<Saw*>(data->object);
		if (!saw)
			return;
		else
			saw->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "enemy") // +  
	{
		Enemy* enemy = dynamic_cast<Enemy*>(data->object);
		if (!enemy)
			return;
		else
			enemy->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "hedgehog") // +
	{
		Hedgehog* hedgehog = dynamic_cast<Hedgehog*>(data->object);
		if (!hedgehog)
			return;
		else
			hedgehog->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "trampoline") // +
	{
		Trampoline* trampoline = dynamic_cast<Trampoline*>(data->object);
		if (!trampoline)
			return;
		else
			trampoline->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "flag") // +
	{
		Flag* flag = dynamic_cast<Flag*>(data->object);
		if (!flag)
			return;
		else
			flag->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "marble") // +
	{
		Marble* marble = dynamic_cast<Marble*>(data->object);
		if (!marble)
			return;
		else
			marble->OnContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "sand") // +
	{
		Sand* sand = dynamic_cast<Sand*>(data->object);
		if (!sand)
			return;
		else
			sand->OnContact(self, other);
	}
}

void Character::OnEndContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (!data)
		return;

	if (groundFixture == self && data->type == FixtureDataType::MapTile && isGrounded > 0)
		DecreaseGrounded();
	else if (groundFixture == self && data->type == FixtureDataType::Object && data->object->tag == "platform")
	{
		MovingPlatform* platform = dynamic_cast<MovingPlatform*>(data->object);
		if (!platform)
			return;
		else
			platform->OnEndContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "flag")
	{
		Flag* flag = dynamic_cast<Flag*>(data->object);
		if (!flag)
			return;
		else
			flag->OnEndContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "marble")
	{
		Marble* marble = dynamic_cast<Marble*>(data->object);
		if (!marble)
			return;
		else
			marble->OnEndContact(self, other);
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "sand")
	{
		Sand* sand = dynamic_cast<Sand*>(data->object);
		if (!sand)
			return;
		else
			sand->OnEndContact(self, other);
	}
}

size_t Character::GetCoins()
{
	return coins;
}