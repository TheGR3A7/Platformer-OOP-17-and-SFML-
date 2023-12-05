#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

using namespace std;

class Resources
{
public:
	static unordered_map<string, sf::Texture> textures;
	static unordered_map<string, sf::SoundBuffer> sounds;
};