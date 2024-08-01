#pragma once

enum Faction{FACTION_UNKNOWN = 0,ALIEN, ROBOT };
enum MovementType{MOVEMENTTYPE_UNKNOWN = 0 ,GROUND, UNGROUND};
enum ColliderType{COLLIDERTYPE_UNKNOWN = 0,STATIC, DYNAMIC};
enum ColliderShapeType{COLLIDERSHAPETYPE_UNKNOWN =0,RECTANGLE, CIRCLE};

namespace ratchet
{
	struct GameObjectConfig
	{
		//States
		Faction m_Faction;
		MovementType m_movementType;
		ColliderType m_colliderType;
		ColliderShapeType m_colliderShapeType;

		//Transforms
		sf::Vector2f spawnPosition;
		sf::Vector2f spawnRotation;
		sf::Vector2f spawnScale;
		sf::Vector2f currentPosition;
		sf::Vector2f currentRoatation;
		sf::Vector2f currentScale;
	

		//Graphics
		std::string spritePath;
		sf::Sprite objSprite;
		sf::Texture spriteTexture;

		//Physics
		sf::Vector2f colliderScaleMultiplier;

		//Constructor
		GameObjectConfig();
	
		//Destructor
		~GameObjectConfig();

	};

}

