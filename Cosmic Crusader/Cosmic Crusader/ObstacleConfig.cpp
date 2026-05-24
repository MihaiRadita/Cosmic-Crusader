#include "stdafx.h"
#include "ObstacleConfig.h"

#include "SceneManager.h"

#include "EnumMask.h"

namespace ratchet
{
	ObstacleConfig::ObstacleConfig()
	{
		m_damage = 0.0f;
		m_animationActiveTimePass = 0.0f;
		m_colliderOffsetX = 0.0f;
		m_colliderOffsetY = 0.0f;
		m_isAnimationPlaying = false;
		m_animtionTimeLimit = 0;
	}

	bool ObstacleConfig::serialise(nlohmann::json& jsonFile)
	{
		return false;
	}

	bool ObstacleConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		m_objectID = jsonFile["id"];
		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		std::string m_objectName = jsonFile["name"];

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
		if (m_objectName == "Cutter")
		{
			m_colliderConfig = new CircleColliderConfig();
		}
		
		if (m_objectName == "Flame")
		{
			m_colliderConfig = new RectAngleColliderConfig();
		}

		for (const auto& jsonProperty : jsonFile["properties"])
		{
			const auto& propertyName = jsonProperty["name"];
			const auto& propertyValue = jsonProperty["value"];

			const auto& propertyType = jsonProperty["type"];


			if (propertyName == "Faction")
			{
				m_Faction = static_cast<Faction>(propertyValue.get<int>());
			}

			if (propertyName == "objectType")
			{
				m_objectType = static_cast<ObjectType>(propertyValue.get<int>());
			}

			if (propertyName == "activeObject")
			{
				m_activeObject = propertyValue.get<bool>();
			}

			if (propertyName == "activeRenderer")
			{
				m_activeRenderer = propertyValue.get<bool>();
			}

			if (propertyName == "animationActiveTimePass")
			{
				m_animationActiveTimePass = propertyValue.get<float>();
			}

			if (propertyName == "animationTimeLimit")
			{
				m_animtionTimeLimit = propertyValue.get<float>();
			}

			if (propertyName == "frameIndexContinueAnimtionFrom")
			{
				m_frameIndexContinueAnimationFrom = propertyValue.get<int>();
			}

			if (propertyName == "colliderDensity")
			{
				m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
			}

			if (propertyName == "colliderFixedRotation")
			{
				m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
			}

			if (propertyName == "colliderFriction")
			{
				m_colliderConfig->m_fixtureDef.friction = propertyValue.get<float>();
			}

			if (propertyName == "colliderIsSensor")
			{
				m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
			}

			if (propertyName == "colliderLayer")
			{
				m_colliderConfig->m_layer = static_cast<PhysicsLayer>(propertyValue.get<int>());
			}

			if (propertyName == "colliderOffsetX")
			{
				m_colliderConfig->m_colliderOffsetX = propertyValue.get<float>();
			}

			if (propertyName == "colliderOffsetY")
			{
				m_colliderConfig->m_colliderOffsetY = propertyValue.get<float>();
			}

			if (propertyName == "colliderRadius")
			{
				if (m_colliderConfig)
				{
					if (auto* circleConfig = dynamic_cast<CircleColliderConfig*>(m_colliderConfig))
					{
						circleConfig->m_radius = propertyValue.get<float>();
					}
				}
			}

			if (propertyName == "colliderRestitution")
			{
				m_colliderConfig->m_fixtureDef.restitution = propertyValue.get<float>();
			}

			if (propertyName == "colliderType")
			{
				m_colliderConfig->m_bodyDef.type = static_cast<b2BodyType>(propertyValue.get<int>());
			}

			if (propertyName == "damage")
			{
				m_damage = propertyValue.get<float>();
			}

			if (propertyName == "isAnimationPlaying")
			{
				m_isAnimationPlaying = propertyValue.get<bool>();
			}

			if (propertyName == "spriteTexturePath")
			{
				spriteTexturePath = propertyValue.get<std::string>();
			}

			if (propertyName == "startSpriteTexturePath")
			{
				startSpriteTexturePath = propertyValue.get<std::string>();
			}

			if (propertyName == "bodyAligment")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_bodyAlignment = static_cast<BodyAlignment>(propertyValue.get<int>());
				}
			}
		}

		return true;
	}

}
