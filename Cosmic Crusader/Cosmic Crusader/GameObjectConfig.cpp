#include "stdafx.h"
#include "GameObjectConfig.h"

namespace ratchet
{
	GameObjectConfig::GameObjectConfig()
	{
		//States
		m_Faction = Faction::FACTION_UNKNOWN;
		m_movementType = MovementType::MOVEMENTTYPE_UNKNOWN;
		m_colliderType = ColliderType::COLLIDERTYPE_UNKNOWN;
		m_colliderShapeType = ColliderShapeType::COLLIDERSHAPETYPE_UNKNOWN;

		//Transforms
		spawnPosition = sf::Vector2f(0.f, 0.f);
		spawnRotation = sf::Vector2f(0.f, 0.f);
		spawnScale = sf::Vector2f(0.f, 0.f);
		
		//Graphics
		spritePath = "";
		objSprite = sf::Sprite();
		spriteTexture = sf::Texture();

		//Physics
		colliderScaleMultiplier = sf::Vector2f(0.f, 0.f);
	}

	GameObjectConfig::~GameObjectConfig()
	{

	}
}