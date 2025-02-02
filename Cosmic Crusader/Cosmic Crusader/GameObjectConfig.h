#pragma once

#include "ColliderBase.h"
#include "WeaponConfig.h"
#include "Weapon.h"

namespace ratchet
{
	enum Faction{FACTION_UNKNOWN = 0 ,PLAYER, ALIEN, ROBOT };
	enum MovementType{MOVEMENTTYPE_UNKNOWN = 0 ,GROUND, UNGROUND};
	struct GameObjectConfig
	{
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

		//Physics
		BaseColliderConfig* m_colliderConfig = nullptr;

		//Constructor
		GameObjectConfig();
	
		//Destructor
		~GameObjectConfig();

		

	};

}

