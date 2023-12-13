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

using namespace std;

const float movementSpeed = 7.0f;
const float jumpVelocity = 10.0f;

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
	bodyDef.fixedRotation = true; // убирает вращение персонажа
	body = Physics::world->CreateBody(&bodyDef);


	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData; //приведение указателя к беззнаковому целочисленному типу для сохранения указателя на объект 
	fixtureDef.density = 1.0f; 
	fixtureDef.friction = 0.0f; // трение

	b2CircleShape circleShape;
	circleShape.m_radius = 0.5f;
	circleShape.m_p.Set(0.0f, -0.5f);
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef); 

	circleShape.m_p.Set(0.0f, 0.5f);
	body->CreateFixture(&fixtureDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.5f, 0.5f);
	fixtureDef.shape = &polygonShape;// фигура
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

	textureToDraw = runAnimation.GetTexture();

	if (velocity.x < -0.02f)
		dirLeft = true;
	else if (velocity.x > 0.02f) // else if потому что если == 0, то он не должен менять сторону, при просто else это не учтется
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
	ren.Draw(textureToDraw, position, sf::Vector2f(dirLeft ? -1.0f : 1.0f, 2.0f), angle); // типо Перс 1 метр ростом и 1 метр в ширину(мы теперь делем исходные данные на 16)
}

void Character::OnBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (!data)
		return;

	if(groundFixture == self && data->type == FixtureDataType::MapTile)
		isGrounded++;
	if (data->type == FixtureDataType::Object && data->object->tag == "platform")
	{
		MovingPlatform* platform = dynamic_cast<MovingPlatform*>(data->object);
		if (!platform)
			return;
		else
		{
			isGrounded++;
		}
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "coin")
	{
		Coin* coin = dynamic_cast<Coin*>(data->object);
		if (!coin)
			return;
		if (coin->IsCollected())
			return;

		coinSound.play();
		coin->Collected();
		//DeleteObject(data->object);
		cout << "coins = " << ++coins << endl;
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "spike")
	{
		Spike* spike = dynamic_cast<Spike*>(data->object);
		if (!spike)
			return;
		if (groundFixture == self)
			isDead = true;
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "saw")
	{
		Saw* saw = dynamic_cast<Saw*>(data->object);
		if (!saw)
			return;
		else
			isDead = true;
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "enemy")
	{
		Enemy* enemy = dynamic_cast<Enemy*>(data->object);
		if (!enemy)
			return;
		if (groundFixture == self)
			enemy->Die();
		else if(!enemy->IsDead())
			isDead = true;
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "hedgehog")
	{
		Hedgehog* hedgehog = dynamic_cast<Hedgehog*>(data->object);
		if (!hedgehog)
			return;
		if (hedgehog->IsSleeping() == true)
			hedgehog->Die();
		else if (!hedgehog->IsDead())
			isDead = true;
	}
	else if (data->type == FixtureDataType::Object && data->object->tag == "trampoline")
	{
		Trampoline* trampoline = dynamic_cast<Trampoline*>(data->object);
		if (!trampoline)
			return;
		if (groundFixture == self)
		{
			trampoline->Activated();

			b2Vec2 jumpVelocity = body->GetLinearVelocity();
			jumpVelocity.y = -15.0f;
			body->SetLinearVelocity(jumpVelocity);
		}
	}
}

void Character::OnEndContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (!data)
		return;

	if (groundFixture == self && data->type == FixtureDataType::MapTile && isGrounded > 0)
		isGrounded--;
	else if (data->type == FixtureDataType::Object && data->object->tag == "platform")
		isGrounded--;
}

size_t Character::GetCoins()
{
	return coins;
}