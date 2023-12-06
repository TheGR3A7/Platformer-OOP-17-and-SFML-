#include "Coin.h"
#include "Resources.h"

void Coin::Begin()
{
	animation = Animation(0.6f,
		{
			AnimFrame(0.5f, Resources::textures["coin1.png"]),
			AnimFrame(0.4f, Resources::textures["coin2.png"]),
			AnimFrame(0.3f, Resources::textures["coin3.png"]),
			AnimFrame(0.2f, Resources::textures["coin4.png"]),
			AnimFrame(0.1f, Resources::textures["coin5.png"]),
			AnimFrame(0.0f, Resources::textures["coin6.png"]),
		});
}

void Coin::Update(float deltaTime)
{
	animation.Update(deltaTime);
}

void Coin::Render(Renderer& ren)
{
	ren.Draw(animation.GetTexture(), position, sf::Vector2f(0.8f, 0.8f));
}
