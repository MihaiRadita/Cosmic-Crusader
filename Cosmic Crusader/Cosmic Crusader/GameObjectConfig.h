#pragma once

#include "ColliderBase.h"
#include "serialisation/ISerialisableItem.h"

namespace ratchet
{
	enum class Faction{FACTION_UNKNOWN = 0 ,TEAM_0, TEAM_1, };

	enum class MovementType{MOVEMENTTYPE_UNKNOWN = 0 ,GROUND, AIR};

	enum class ObjectType{None = 0, World, UI, HUD};

	enum class ColliderShapeType{None =0, Rectangle, Circle, Capsule};

	enum class ColliderGroupType{None = 0, Single, Group};

	struct GameObjectConfig : public ISerialisableItem
	{
#ifdef IS_RATCHET_DEBUG
		bool m_debugDraw = false;
#endif

		//States
		Faction m_Faction;
		MovementType m_movementType;
		ColliderType m_colliderType;
		ObjectType m_objectType;
		ColliderGroupType m_colliderGroupType = ColliderGroupType::Single;

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
		bool m_activeObject;
		bool m_canJumpOver;
		ColliderShapeType m_colliderShapeType;

		std::string m_objectLayerName;

		//Physics
		ColliderBaseConfig* m_colliderConfig = nullptr;

		//Layers/Ids
		int m_objectID;

		//Constructor
		GameObjectConfig();
	
		//Destructor
		~GameObjectConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;
	};

}

