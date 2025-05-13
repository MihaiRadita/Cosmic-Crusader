#pragma once

#include "ColliderBase.h"
#include "Weapon.h"

namespace ratchet
{
	enum class Faction{FACTION_UNKNOWN = 0 ,PLAYER, ALIEN, ROBOT };
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
		ColliderShapeType m_colliderShapeType;

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

		//Physics
		BaseColliderConfig* m_colliderConfig = nullptr;

		//Constructor
		GameObjectConfig();
	
		//Destructor
		~GameObjectConfig();

		

	};

}

