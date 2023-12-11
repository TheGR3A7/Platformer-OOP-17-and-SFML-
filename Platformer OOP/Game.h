#pragma once
#include <SFML/Graphics.hpp>
#include "Standard Values.h"
#include "Renderer.h"
#include "Camera.h"
#include "Object.h"

extern Camera camera;
extern bool paused;

void Begin();
void Update(float deltaTime);
void Render(Renderer& ren);
void RenderUI(Renderer& ren);

void DeleteObject(Object* object);
bool IsPlayerDead();