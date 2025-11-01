#include "stdafx.h"
#include "SelfControlledCreatureConfig.h"

#include "game/Game.h"


namespace ratchet
{
	SelfControlledCreatureConfig::SelfControlledCreatureConfig() : CreatureConfig()
	{
		m_targetMaxDistanceDetectionX = 0.0f;
		m_targetMaxDistanceDetectionY = 0.0f;
		m_targetMaxDistanceLoseX = 0.0f;
		m_targetMaxDistanceLoseY = 0.0f;
		m_targetMaxDistanceAttackX = 0.0f;
		m_targetMaxDistanceAttackY = 0.0f;
	}

	SelfControlledCreatureConfig::~SelfControlledCreatureConfig()
	{

	}
	bool SelfControlledCreatureConfig::serialise(nlohmann::json& jsonFile)
	{
		return GameObjectConfig::serialise(jsonFile);
	}
	bool SelfControlledCreatureConfig::deserialise(const nlohmann::json& jsonFile)
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

			if (propertyName == "movementType")
			{
				m_movementType = static_cast<MovementType>( propertyValue.get<int>());
			}

			if (propertyName == "colliderType")
			{
				m_colliderType = static_cast<ColliderType>(propertyValue.get<int>());
			}

			if (propertyName == "movingSpeed")
			{
				m_movingSpeed = propertyValue.get<float>();
			}

			if (propertyName == "jumpImpulse")
			{
				m_jumpImpulse = propertyValue.get<float>();
			}

			if (propertyName == "fallingSpeed")
			{
				m_fallingSpeed = propertyValue.get<float>();
			}

			if (propertyName == "angleBase")
			{
				m_AngleBase = propertyValue.get<float>();
			}

			if (propertyName == "recoilTime")
			{
				m_recoilTime = propertyValue.get<float>();;
			}

			if (propertyName == "fireRate")
			{
				m_fireRate = propertyValue.get<float>();
			}

			if (propertyName == "targetMaxDistanceDetectionX")
			{
				m_targetMaxDistanceDetectionX = propertyValue.get<float>();
			}

			if (propertyName == "targetMaxDistanceDetectionY")
			{
				m_targetMaxDistanceDetectionY = propertyValue.get<float>();
			}

			if (propertyName == "targetMaxDistanceLoseX")
			{
				m_targetMaxDistanceLoseX = propertyValue.get<float>();
			}

			if (propertyName == "targetMaxDistanceLoseY")
			{
				m_targetMaxDistanceLoseY = propertyValue.get<float>();
			}

			if (propertyName == "targetMaxDistanceAttackX")
			{
				m_targetMaxDistanceAttackX = propertyValue.get<float>();
			}

			if (propertyName == "targetMaxDistanceAttackY")
			{
				m_targetMaxDistanceAttackY = propertyValue.get<float>();
			}

			if (propertyName == "startSpriteTexturePath")
			{
				startSpriteTexturePath = propertyValue.get<std::string>();
			}

			if (propertyName == "spriteTexturePath")
			{
				spriteTexturePath = propertyValue.get<std::string>();
			}

			if (propertyName == "activeRenderer")
			{
				m_activeRenderer = propertyValue.get<bool>();
			}

			if (propertyName == "colliderLayer")
			{
				m_colliderConfig->m_layer = static_cast<PhysicsLayer>(propertyValue.get<int>());
			}

			if (propertyName == "colliderType")
			{
				m_colliderConfig->m_bodyDef.type = static_cast<b2BodyType>(propertyValue.get<int>());
			}

			if (propertyName == "colliderBullet")
			{
				m_colliderConfig->m_bodyDef.bullet = propertyValue.get<bool>();
			}

			if (propertyName == "colliderFixedRotation")
			{
				m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
			}

			if (propertyName == "colliderFriction")
			{
				m_colliderConfig->m_fixtureDef.friction = propertyValue.get<float>();
			}

			if (propertyName == "colliderRestitution")
			{
				m_colliderConfig->m_fixtureDef.restitution = propertyValue.get<float>();
			}

			if (propertyName == "colliderDensity")
			{
				m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
			}

			if (propertyName == "colliderHeight")
			{
				if (auto* capsule = dynamic_cast<CapsuleColliderConfig*>(m_colliderConfig))
				{
					capsule->m_height = propertyValue.get<float>();
				}

			}

			if (propertyName == "colliderRadius")
			{
				if (auto* capsule = dynamic_cast<CapsuleColliderConfig*>(m_colliderConfig))
				{
					capsule->m_radius = propertyValue.get<float>();
				}

			}

			if (propertyName == "colliderMassValue")
			{
				m_colliderConfig->m_massValue = propertyValue.get<float>();
			}

			if (propertyName == "colliderIsSensor")
			{
				m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
			}

			if (propertyName == "colliderIsGroundRaycastOffset")
			{
				m_colliderConfig->m_isGroundRaycastOffset = propertyValue.get<float>();
			}

			if (propertyName == "colliderJumpOverBottomRaycastOffsetX")
			{
				m_colliderConfig->m_JumpOverBottomRaycastOffsetX = propertyValue.get<float>();
			}

			if (propertyName == "colliderJumpOverBottomRaycastOffsetY")
			{
				m_colliderConfig->m_JumpOverBottomRaycastOffsetY = propertyValue.get<float>();
			}

			if (propertyName == "colliderJumpOverTopRaycastOffsetX")
			{
				m_colliderConfig->m_JumpOverTopRaycastOffsetX = propertyValue.get<float>();
			}

			if (propertyName == "colliderJumpOverTopRaycastOffsetY")
			{
				m_colliderConfig->m_JumpOverTopRaycastOffsetY = propertyValue.get<float>();
			}

			if (propertyName == "colliderCheckFallingRiskRaycastStartOffsetX")
			{
				m_colliderConfig->m_checkFallingRiskRaycastStartOffsetX = propertyValue.get<float>();
			}

			if (propertyName == "colliderCheckFallingRiskRaycastStartOffsetY")
			{
				m_colliderConfig->m_checkFallingRiskRaycastStartOffsetY = propertyValue.get<float>();
			}

			if (propertyName == "colliderCheckFallingRiskRaycastEndOffsetY")
			{
				m_colliderConfig->m_checkFallingRiskRaycastEndOffsetY = propertyValue.get<float>();
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
			
			if (propertyName == "bodyShoulderOffset")
			{
				m_bodShoulderOffset = propertyValue.get<float>();
			}
		}
		return true;
	}
}
