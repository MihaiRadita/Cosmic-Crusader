#include "stdafx.h"
#include "ActionTriggerConfig.h"

#include "SceneManager.h"


namespace ratchet
{
	ActionTriggerConfig::ActionTriggerConfig() : GameObjectConfig()
	{
		m_triggerShapeSizeX = 0.0f;
		m_triggerShapeSizeY = 0.0f;
	}
	ActionTriggerConfig::~ActionTriggerConfig()
	{

	}
	bool ActionTriggerConfig::serialise(nlohmann::json& jsonFile)
	{
		return false;
	}
	bool ActionTriggerConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		m_triggerShapeSizeX = tileWidth;
		m_triggerShapeSizeY = tileHeight;

		float scalscale = SceneManager::sc_tiledToGameScale;

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

			if (propertyName == "Faction")
			{
				m_Faction = static_cast<Faction>(propertyValue.get<int>());
			}

			if (propertyName == "actionTriggerName")
			{
				m_actionTriggerName = static_cast<ActionTriggerName>(propertyValue.get<int>());
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
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
				}
			}

			if (propertyName == "colliderFixedRotation")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
				}
			}

			if (propertyName == "colliderIsSensor")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
				}
			}

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

			if (propertyName == "isFallTriggerInteracting")
			{
				m_isActionTriggerInteracting = propertyValue.get<bool>();
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