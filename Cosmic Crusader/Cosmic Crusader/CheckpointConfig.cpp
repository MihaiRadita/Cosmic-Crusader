#include "stdafx.h"
#include "CheckpointConfig.h"

#include "SceneManager.h"

namespace ratchet
{
	CheckpointConfig::CheckpointConfig()
	{
		
	}

	CheckpointConfig::~CheckpointConfig()
	{

	}
	bool CheckpointConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		m_objectID = jsonFile["id"].get<int>();

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		scale = sf::Vector2f(1.0f, 1.0f) * SceneManager::sc_tiledToGameScale;
		positionXOffset = 0.f;
		positionYOffset = -tileHeight * scale.y;

		float posX = jsonFile["x"].get<float>() * scale.x;
		float posY = jsonFile["y"].get<float>() * scale.y;

		posY += positionYOffset;

		position = sf::Vector2f(posX, posY);
		rotation = jsonFile["rotation"];
		startSpriteTexturePath = "";
		startSpriteTexturePathAddition = "";

		// Custom Properties
		m_colliderConfig = new RectAngleColliderConfig();

		for (const auto& jsonProperty : jsonFile["properties"])
		{
			const auto& propertyName = jsonProperty["name"];
			const auto& propertyValue = jsonProperty["value"];

			const auto& propertyType = jsonProperty["type"];

			if (propertyName == "Faction")
			{
				m_Faction = static_cast<Faction>(propertyValue.get<int>());
			}

			if (propertyName == "activeObject")
			{
				m_activeObject = propertyValue.get<bool>();
			}

			if (propertyName == "activeRenderer")
			{
				m_activeRenderer = propertyValue.get<bool>();
			}

			if (propertyName == "colliderDensity")
			{
				m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
			}

			if (propertyName == "colliderFixedRotation")
			{
				m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
			}

			if (propertyName == "colliderIsSensor")
			{
				m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
			}

			if (propertyName == "colliderLayer")
			{
				m_colliderConfig->m_layer = static_cast<PhysicsLayer>(propertyValue.get<int>());
			}

			if (propertyName == "colliderType")
			{
				m_colliderConfig->m_bodyDef.type = static_cast<b2BodyType>(propertyValue.get<int>());
			}

			if (propertyName == "flagGreenTexture")
			{
				m_GreenFlagPath = propertyValue.get<std::string>();
			}

			if (propertyName == "flagRedTexture")
			{
				m_RedFlagPath = propertyValue.get<std::string>();
			}

			if (propertyName == "objectType")
			{
				m_objectType = static_cast<ObjectType>(propertyValue.get<int>());
			}

			if (propertyName == "startSpriteTexturePath")
			{
				startSpriteTexturePath = propertyValue.get<std::string>();
			}
		}

		return true;
	}
}