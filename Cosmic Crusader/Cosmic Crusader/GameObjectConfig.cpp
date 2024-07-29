#include "stdafx.h"
#include "GameObjectConfig.h"

namespace ratchet
{
	GameObjectConfig::GameObjectConfig()
	{
		spawnPosition = sf::Vector2f(0.f, 0.f);
		spawnRotation = sf::Vector2f(0.f, 0.f);
		spawnScale = sf::Vector2f(0.f, 0.f);
		
		spritePath = "";

		colliderScaleMultiplier = sf::Vector2f(0.f, 0.f);
	}

	GameObjectConfig::~GameObjectConfig()
	{

	}
}