#pragma once

enum Faction{FACTION_UNKNOWN = 0,ALIEN, ROBOT };
enum MovementType{MOVEMENTTYPE_UNKNOWN = 0 ,GROUND, UNGROUND};
enum ColliderType{COLLIDERTYPE_UNKNOWN = 0,STATIC, DYNAMIC};
enum ColliderShapeType{COLLIDERSHAPETYPE_UNKNOWN =0,RECTANGLE, CIRCLE};

namespace ratchet
{
	struct GameObjectConfig
	{
		//Transforms
		sf::Vector2f spawnPosition;
		sf::Vector2f spawnRotation;
		sf::Vector2f spawnScale;

		//Graphics
		std::string spritePath;

		//Physics
		sf::Vector2f colliderScaleMultiplier;

		//Constructor
		GameObjectConfig();
	
		//Destructor
		~GameObjectConfig();

	};

}

