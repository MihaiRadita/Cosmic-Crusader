#include "stdafx.h"
#include "BulletConfig.h"

#include "game/Game.h"


namespace ratchet
{
	BulletConfig::BulletConfig()
	{
		m_ammo = 0.0f;
		m_damage = 0.0f;

		m_configLayer = "";
	}
	bool BulletConfig::serialise(nlohmann::json& jsonFile)
	{
		return GameObjectConfig::serialise(jsonFile);
	}
	bool BulletConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		m_objectID = jsonFile["id"].get<int>();

		float tileWidth = jsonFile["width"];
		float tileHeight = jsonFile["height"];

		scale = sf::Vector2f(1.0f, 1.0f) * Game::sc_tiledToGameScale;
		positionXOffset = 0.f;
		positionYOffset = -tileHeight * scale.y;

		float posX = jsonFile["x"].get<float>() * scale.x;
		float posY = jsonFile["y"].get<float>() * scale.y;

		posY += positionYOffset;

		position = sf::Vector2f(posX, posY);
		rotation = jsonFile["rotation"];
		startSpriteTexturePath = "";
		startSpriteTexturePathAddition = "";

		m_colliderConfig = new CircleColliderConfig();

		for (const auto& jsonProperty : jsonFile["properties"])
		{
			const auto& propertyName = jsonProperty["name"];
			const auto& propertyValue = jsonProperty["value"];

			if (propertyName == "objectType")
			{
				m_objectType = static_cast<ObjectType>(propertyValue.get<int>());
			}

			if (propertyName == "bulletLifeLimit")
			{
				m_bulletLifeLimit = propertyValue.get<float>();
			}
			if (propertyName == "bulletSpeed")
			{
				m_BulletSpeed = propertyValue.get<float>();
			}
		
			if (propertyName == "Faction")
			{
				m_Faction = static_cast<Faction>(propertyValue.get<int>());
			}

			if (propertyName == "bulletMovementType")
			{
				m_movementType = static_cast<MovementType>(propertyValue.get<int>());
			}

			if (propertyName == "activeObject")
			{
				m_activeObject = propertyValue.get<bool>();
			}

			if (propertyName == "activeRenderer")
			{
				m_activeRenderer = propertyValue.get<bool>();
			}

			if (propertyName == "bulletStartSpriteTexturePath")
			{
				startSpriteTexturePath = propertyValue.get<std::string>();
			}

			if (propertyName == "colliderBulletType")
			{
				m_colliderType = static_cast<ColliderType>(propertyValue.get<int>());
			}


			if (propertyName == "colliderBulletLayer")
			{
				m_colliderConfig->m_layer = static_cast<PhysicsLayer>(propertyValue.get<int>());
			}
			if (propertyName == "colliderBulletType")
			{
				m_colliderConfig->m_bodyDef.type = static_cast<b2BodyType>(propertyValue.get<int>());
			}
			if (propertyName == "colliderBulletDensity")
			{
				m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
			}
			if (propertyName == "colliderBulletFixedRotation")
			{
				m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
			}
			if (propertyName == "colliderBulletFriction")
			{
				m_colliderConfig->m_fixtureDef.friction = propertyValue.get<float>();
			}
			if (propertyName == "colliderBulletRestitution")
			{
				m_colliderConfig->m_fixtureDef.restitution = propertyValue.get<float>();
			}
			if (propertyName == "colliderBulletIsSensor")
			{
				m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
			}

			if (propertyName == "colliderBulletGravityScale")
			{
				m_colliderConfig->m_gravityScale = propertyValue.get<float>();
			}

			if (propertyName == "colliderBulletLinearDamping")
			{
					m_colliderConfig->m_linearDamping = propertyValue.get<float>();
			}

			if (propertyName == "colliderBulletAngularDamping")
			{
					m_colliderConfig->m_angularDamping = propertyValue.get<float>();
			}
			
		}

		return true;
	}
}
