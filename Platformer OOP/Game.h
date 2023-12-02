#pragma once
#include <SFML/Graphics.hpp>
#include "Standard Values.h"
#include "Renderer.h"

void Begin(const sf::Window& win);
void Update(float deltaTime);
void Render(Renderer& ren);
