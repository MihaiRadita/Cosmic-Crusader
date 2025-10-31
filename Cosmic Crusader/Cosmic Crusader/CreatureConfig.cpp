#include "stdafx.h"
#include "CreatureConfig.h"

#include "game/Game.h"

namespace ratchet
{
	bool CreatureConfig::serialise(nlohmann::json& jsonFile)
	{
		return GameObjectConfig::serialise(jsonFile);
	}
	bool CreatureConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

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

		// Custom Properties
		m_colliderConfig = new CapsuleColliderConfig();

		for (const auto& jsonProperty : jsonFile["properties"])
		{
			const auto& propertyName = jsonProperty["name"];
			const auto& propertyValue = jsonProperty["value"];

			if (propertyName == "Faction")
			{
				m_Faction = static_cast<Faction>(propertyValue.get<int>());
			}

			if (propertyName == "activeRenderer")
			{
				m_activeRenderer = propertyValue.get<bool>();
			}

			if (propertyName == "angleBase")
			{
				m_AngleBase = propertyValue.get<float>();
			}

			if (propertyName == "bodyShoulderOffset")
			{
				m_bodShoulderOffset = propertyValue.get<float>();
			}

			if (propertyName == "colliderBullet")
			{
				m_colliderConfig->m_bodyDef.bullet = propertyValue.get<bool>();
			}

			if (propertyName == "colliderHeight")
			{
				if (auto* capsule =dynamic_cast<CapsuleColliderConfig*>(m_colliderConfig))
				{
					capsule->m_height = propertyValue.get<float>();

				}
			}

			if (propertyName == "colliderLayer")
			{
				m_colliderConfig->m_layer = static_cast<PhysicsLayer>(propertyValue.get<int>());
			}

			if (propertyName == "colliderRadius")
			{
				if (auto* capsule = dynamic_cast<CapsuleColliderConfig*>(m_colliderConfig))
				{
					capsule->m_radius = propertyValue.get<float>();

				}
			}

			if (propertyName == "colliderType")
			{
				m_colliderConfig->m_bodyDef.type = static_cast<b2BodyType>(propertyValue.get<int>());

			}

			if (propertyName == "density")
			{
				m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
			}

			if (propertyName == "fallingSpeed")
			{
				m_fallingSpeed = propertyValue.get<float>();
			}

			if (propertyName == "fireRate")
			{
				m_fireRate = propertyValue.get<float>();
			}

			if (propertyName == "fixedRotation")
			{
				m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
			}

			if (propertyName == "friction")
			{
				m_colliderConfig->m_fixtureDef.friction = propertyValue.get<float>();
			}

			if (propertyName == "isGroundRaycastOffset")
			{
				m_colliderConfig->m_isGroundRaycastOffset = propertyValue.get<float>();
			}

			if (propertyName == "isSensor")
			{
				m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
			}

			if (propertyName == "jumpImpulse")
			{
				m_jumpImpulse = propertyValue.get<float>();
			}

			if (propertyName == "massValue")
			{
				m_colliderConfig->m_massValue = propertyValue.get<float>();
			}

			if (propertyName == "movementType")
			{
				m_movementType = static_cast<MovementType>(propertyValue.get<int>());
			}

			if (propertyName == "movingSpeed")
			{
				m_movingSpeed = propertyValue.get<float>();
			}

			if (propertyName == "recoilTime")
			{
				m_recoilTime = propertyValue.get<float>();
			}

			if (propertyName == "restitution")
			{
				m_colliderConfig->m_fixtureDef.restitution = propertyValue.get<float>();
			}

			if (propertyName == "spriteTexturePath")
			{
				spriteTexturePath = propertyValue.get<std::string>();
			}

			if (propertyName == "startSpriteTexturePath")
			{
				startSpriteTexturePath = propertyValue.get<std::string>();
			}

			if (propertyName == "colliderGravityScale")
			{
				m_colliderConfig->m_gravityScale = propertyValue.get<float>();
			}

			if (propertyName == "colliderLinearDamping")
			{
				m_colliderConfig->m_linearDamping = propertyValue.get<float>();
			}

			if (propertyName == "colliderAngularDamping")
			{
				m_colliderConfig->m_angularDamping = propertyValue.get<float>();
			}
		}

		return true;
	}
	ratchet::CreatureConfig::CreatureConfig() : GameObjectConfig()
	{
		m_movingSpeed = 0.f;
		m_fallingSpeed = 0.f;
		m_jumpImpulse = 0.f;

		m_recoilTime = 0.0f;
		m_fireRate = 0.0f;
	}

	ratchet::CreatureConfig::~CreatureConfig()
	{
	}
}

