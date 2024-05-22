#define _USE_MATH_DEFINES
#include <cmath>
#include "Game.h"
#include "Enemy.h"
#include "Resources.h"
#include <box2d/b2_circle_shape.h>

void Enemy::OnContact(b2Fixture* self, b2Fixture* other)
{
	if (player.GetGroundFixture() == self)
		Die();
	else if (!IsDead())
    {
		if (player.hasShield != 1 && player.immortalityTimer <= 0.0f)
			player.isDead = true;
		if (player.GetGroundFixture() != self && player.hasShield == 1)
		{
			player.hasShield += 1;
			player.immortalityTimer = 2.0f;
		}
    }
}
