#pragma once

#include "ColliderBase.h"

namespace ratchet
{
	enum class Faction{FACTION_UNKNOWN = 0 ,TEAM_0, TEAM_1, };
	enum class MovementType{MOVEMENTTYPE_UNKNOWN = 0 ,GROUND, AIR};

	struct GameObjectConfig
	{
#ifdef IS_RATCHET_DEBUG
		bool m_debugDraw = false;
#endif

		//States
		Faction m_Faction;
		MovementType m_movementType;
		ColliderType m_colliderType;

		//Transforms
		sf::Vector2f position;
		float rotation;
		sf::Vector2f scale;
		float positionXOffset;
		float positionYOffset;
	

		//Graphics
		std::string startSpriteTexturePath;
		std::string spriteTexturePath;
		std::string startSpriteTexturePathAddition;
		std::string fallingSpriteTexturePath;
		bool m_activeRenderer;

		//Physics
		ColliderBaseConfig* m_colliderConfig = nullptr;

		//Layers/Ids
		std::string m_configLayer;

		//Constructor
		GameObjectConfig();
	
		//Destructor
		~GameObjectConfig();

	};

}

