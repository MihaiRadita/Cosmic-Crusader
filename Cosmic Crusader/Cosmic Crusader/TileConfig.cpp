#include "stdafx.h"
#include "TileConfig.h"

#include "SceneManager.h"


namespace ratchet
{
	bool TileConfig::serialise(nlohmann::json& jsonFile)
	{
		return GameObjectConfig::serialise(jsonFile);
	}

	bool TileConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		float scalscale = SceneManager::sc_tiledToGameScale;

		scale = sf::Vector2f(1.0f, 1.0f) * SceneManager::sc_tiledToGameScale;
		positionXOffset = 0.f;
		positionYOffset = -tileHeight * scale.y;

		float posX = jsonFile["x"].get<float>()* scale.x;
		float posY = jsonFile["y"].get<float>()* scale.y;

		posY += positionYOffset;

		std::string name = jsonFile["name"].get<std::string>();

		

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

			if (propertyName == "objectType")
			{
				m_objectType = static_cast<ObjectType>(propertyValue.get<int>());
			}

			if (propertyName == "startSpriteTexturePath") startSpriteTexturePath = propertyValue.get<std::string>();

			if (propertyName == "Faction") m_Faction = static_cast<Faction>(propertyValue.get<int>());
			if (propertyName == "activeObject")
			{
				m_activeObject = propertyValue.get<bool>();
			}
			if (propertyName == "activeRenderer") m_activeRenderer = propertyValue.get<bool>();

			if (propertyName == "colliderLayer")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_layer = static_cast<PhysicsLayer>(propertyValue.get<float>());
				}
			}
			if (propertyName == "colliderType")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_bodyDef.type = static_cast<b2BodyType>(propertyValue.get<int>());
				}
			}
			if (propertyName == "colliderFixedRotation")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
				}
			}
			if (propertyName == "colliderDensity")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
				}
			}
			if (propertyName == "colliderFriction")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.friction = propertyValue.get<float>();
				}
			}
			if (propertyName == "colliderRestitution")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.restitution = propertyValue.get<float>();
				}
			}
			if (propertyName == "colliderIsSensor")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
				}
			}

			if (propertyName == "colliderGroupType")
			{
				m_colliderGroupType = static_cast<ColliderGroupType>(propertyValue.get<int>());
			}

			if (propertyName == "colliderWidth")
			{
				if (auto* rectAngleConfig = dynamic_cast<RectAngleColliderConfig*>(m_colliderConfig))
				{
					rectAngleConfig->m_width = propertyValue.get<float>();
				}
			}

			if (propertyName == "colliderHeight")
			{
				if (auto* rectAngleConfig = dynamic_cast<RectAngleColliderConfig*>(m_colliderConfig))
				{
					rectAngleConfig->m_height = propertyValue.get<float>();
				}
			}

		}

		return true;
	}
}