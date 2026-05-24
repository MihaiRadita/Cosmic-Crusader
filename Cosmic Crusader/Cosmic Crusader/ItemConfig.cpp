#include "stdafx.h"
#include "ItemConfig.h"

#include "SceneManager.h"

namespace ratchet
{
	ItemConfig::ItemConfig()
	{
		m_itemContenntValue = 0.0f;
		m_isItemAccessible = false;
	}

	bool ItemConfig::serialise(nlohmann::json& jsonFile)
	{
		return false;
	}
	bool ItemConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		m_objectID = jsonFile["id"];
		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		m_objectName = jsonFile["name"];

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
		if (m_objectName == "Ammo")
		{
			m_colliderConfig = new CircleColliderConfig();
		}

		if (m_objectName == "Health")
		{
			m_colliderConfig = new RectAngleColliderConfig();
		}

		if (m_objectName == "Health Recharger" || m_objectName =="Ammo Recharger")
		{
			m_colliderConfig = new RectAngleColliderConfig();
		}

		if (m_objectName == "Ammo")
		{
			m_colliderConfig = new CircleColliderConfig();
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

			if (propertyName == "itemRefferdID")
			{
				m_itemRefferdId = propertyValue.get<int>();
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

			if (propertyName == "isItemAccessible")
			{
				m_isItemAccessible = propertyValue.get<bool>();
			}

			if (propertyName == "isItemInteracting")
			{
				m_isItemInteracting = propertyValue.get<bool>();
			}

			if (propertyName == "isItemUsed")
			{
				m_isItemUsed = propertyValue.get<bool>();
			}

			if (propertyName == "itemType")
			{
				m_itemType = static_cast<ItemType>(propertyValue.get<int>());
			}

			if (propertyName == "itemContentValue")
			{
				m_itemContenntValue = propertyValue.get<float>();
			}

			if (propertyName == "itemDisabledTimePass")
			{
				m_itemDisableTimePass = propertyValue.get<float>();
			}

			if (propertyName == "startSpriteTexturePath")
			{
				startSpriteTexturePath = propertyValue.get<std::string>();
			}

			if (propertyName == "spriteTextureOnPath")
			{
				m_spriteTextureOnPath = propertyValue.get<std::string>();
			}

			if (propertyName == "spriteTextureOffPath")
			{
				m_spriteTextureOffPath = propertyValue.get<std::string>();
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