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

		//Transforms
		position = sf::Vector2f(0.f, 0.f);
		rotation = 0.f;
		scale = sf::Vector2f(0.f, 0.f);

		m_canJumpOver = false;
		
		//Graphics
		spriteTexturePath = "";
		startSpriteTexturePath = "";
		startSpriteTexturePathAddition = "";
		fallingSpriteTexturePath = "";
		positionXOffset = 0.f;
		positionYOffset = 0.f;

	}

	GameObjectConfig::~GameObjectConfig()
	{

	}

	bool GameObjectConfig::serialise(nlohmann::json& jsonFile)
	{
		return false;
	}

	bool GameObjectConfig::deserialise(const nlohmann::json& jsonFile)
	{
		return false;
	}
}