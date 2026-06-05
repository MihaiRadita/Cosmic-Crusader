#include "stdafx.h"
#include "CreatureConfig.h"

#include "SceneManager.h"

#include "EnumMask.h"

namespace ratchet
{
	bool CreatureConfig::serialise(nlohmann::json& jsonFile)
	{
		return false;
	}

	ratchet::CreatureConfig::CreatureConfig() : GameObjectConfig()
	{
		m_movingSpeed = 0.f;
		m_fallingSpeed = 0.f;
		m_jumpImpulse = 0.f;

		m_recoilTime = 0.0f;
		m_fireRate = 0.0f;

		m_health = 0.0f;
		m_maxHealth = 0.0f;
	}

	bool CreatureConfig::deserialise(const nlohmann::json& jsonFile)
	{
		GameObjectConfig::deserialise(jsonFile);

		m_objectID = jsonFile["id"];
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
		m_colliderConfig = new CapsuleColliderConfig();

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
				if (m_colliderConfig)
				{
					m_colliderConfig->m_bodyDef.bullet = propertyValue.get<bool>();
				}

			}

			if (propertyName == "colliderHeight")
			{
				if (m_colliderConfig)
				{
					if (auto* capsule =dynamic_cast<CapsuleColliderConfig*>(m_colliderConfig))
					{
						capsule->m_height = propertyValue.get<float>();

					}
				}
			}

			if (propertyName == "colliderLayer")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_layer = static_cast<PhysicsLayer>(propertyValue.get<int>());
				}
			}

			if (propertyName == "colliderRadius")
			{
				if (m_colliderConfig)
				{
					if (auto* capsule = dynamic_cast<CapsuleColliderConfig*>(m_colliderConfig))
					{
						capsule->m_radius = propertyValue.get<float>();

					}
				}
			}

			if (propertyName == "colliderType")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_bodyDef.type = static_cast<b2BodyType>(propertyValue.get<int>());
				}

			}

			if (propertyName == "density")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
				}
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
				if (m_colliderConfig)
				{
					m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
				}
			}

			if (propertyName == "colliderFriction")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.friction = propertyValue.get<float>();
				}
			}

			if (propertyName == "health")
			{
				m_health = propertyValue.get<float>();
			}


			if (propertyName == "maxHealth")
			{
				m_maxHealth = propertyValue.get<float>();
			}

			if (propertyName == "isGroundRaycastOffset")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_isGroundRaycastOffset = propertyValue.get<float>();
				}
			}

			if (propertyName == "isSensor")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
				}
			}

			if (propertyName == "jumpImpulse")
			{
				m_jumpImpulse = propertyValue.get<float>();
			}

			if (propertyName == "massValue")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_massValue = propertyValue.get<float>();
				}
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
				if (m_colliderConfig)
				{
					m_colliderConfig->m_fixtureDef.restitution = propertyValue.get<float>();
				}
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
				if (m_colliderConfig)
				{
					m_colliderConfig->m_gravityScale = propertyValue.get<float>();
				}
			}

			if (propertyName == "colliderLinearDamping")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_linearDamping = propertyValue.get<float>();
				}
			}

			if (propertyName == "colliderAngularDamping")
			{
				if (m_colliderConfig)
				{
					m_colliderConfig->m_angularDamping = propertyValue.get<float>();
				}
			}

			if (propertyName == "animationStateListMask")
			{
				EnumMask<ANIMATION_STATE> animationStateMask;

				animationStateMask.setValue(propertyValue.get<int>());

				m_animationStates = animationStateMask.getValueList(ANIMATION_STATE::Count);
			}

			if (propertyName == "currentAnimationState")
			{
				m_currentAnimationState = static_cast<ANIMATION_STATE>(propertyValue.get<int>());
			}

			if (propertyName == "currentState")
			{
				m_currentState = static_cast<WeaponAnimation::STATE>(propertyValue.get<int>());

			}

			if (propertyName == "characterAnglesMask")
			{
				EnumMask<WeaponAnimation::ANGLE> anglesMask;

				anglesMask.setValue(propertyValue.get<int>());

				m_characterAngles = anglesMask.getValueList(static_cast<int>(WeaponAnimation::ANGLE::Count));
			}

			if (propertyName == "currentAngle")
			{
				m_currentAngle = static_cast<WeaponAnimation::ANGLE>(propertyValue.get<int>());

			}

			if (propertyName == "weaponTypeListMask")
			{
				EnumMask<Weapon::TYPE> weaponTypeMask;

				weaponTypeMask.setValue(propertyValue.get<int>());

				m_weaponTypeList = weaponTypeMask.getValueList(static_cast<int>(Weapon::TYPE::Count));
										
			}

			if (propertyName == "currentWeaponType")
			{
				m_currentWeaponType = static_cast<Weapon::TYPE>(propertyValue.get<int>());
			}

			if (propertyName == "currentWeaponIndex")
			{
				m_currentlyEquippedWeaponIndex = propertyValue.get<int>();
			}

			if (propertyName == "usableWeaponTypeListMask")
			{
				EnumMask<Weapon::TYPE> weaponTypeMask;
				EnumMask<Weapon::TYPE> weaponCheckMask;


				weaponTypeMask.setValue(propertyValue.get<int>());

				auto weponTypeList = weaponTypeMask.getValueList(static_cast<int>(Weapon::TYPE::Count));

				for (const auto& prop : jsonFile["properties"])
				{
					const auto& propertyName = prop["name"];
					const auto& propertyValue = prop["value"];

					if (propertyName == "usableWeaponCheckListMask")
					{
						weaponCheckMask.setValue(prop["value"].get<int>());
						break;
					}
				}

				m_usableWeaponTypeList.clear();

				for (auto& weaponType : weponTypeList)
				{
					bool isUsable = weaponCheckMask.hasValue(weaponType);

					m_usableWeaponTypeList[weaponType] = isUsable;
				}
			}

			if (propertyName == "creatureSoundLoop")
			{
				m_creatureSoundLoop = propertyValue.get<bool>();
			}

			if (propertyName == "creatureSoundVolume")
			{
				m_creatureSoundVolume = propertyValue.get<float>();
			}

			if (propertyName == "creatureHurtSoundPath")
			{
				m_creatureHurtSoundPath = propertyValue.get<std::string>();
			}

			if (propertyName == "creatureDeathSoundPath")
			{
				m_creatureDeathSoundPath = propertyValue.get<std::string>();
			}

			if (propertyName == "creatureDeathFallSoundPath")
			{
				m_creatureDeathFallSoundPath = propertyValue.get<std::string>();
			}

			if (propertyName == "creatureJumpSoundPath")
			{
				m_creatureJumpSoundPath = propertyValue.get<std::string>();
			}

			if (propertyName == "creatureLandingSoundPath")
			{
				m_creatureLandingSoundPath = propertyValue.get<std::string>();
			}

			if (propertyName == "creatureWalkSoundPath")
			{
				m_creatureWalkSoundPath = propertyValue.get<std::string>();
			}

			if (propertyName == "uiHealthBar")
			{
				if (propertyValue.is_number_integer())
				{
					m_healthBarID = propertyValue.get<int>();
				}
			}

			if (propertyName == "ammoUItext")
			{
				if (propertyValue.is_number_integer())
				{
					m_UIAmmoFractionTextId = propertyValue.get<int>();
				}
			}
		}

		for (const auto& jsonProperty : jsonFile["properties"])
		{
			const auto& propertyName = jsonProperty["name"];
			const auto& propertyValue = jsonProperty["value"];

			const auto& propertyType = jsonProperty["type"];
			if (propertyName.get<std::string>().find("initialWeapon_") != std::string::npos)
			{
				const auto id = propertyValue.get<int>();
				std::optional<WeaponConfig> weaponConfig = std::nullopt;
				Weapon::TYPE weaponType = Weapon::TYPE::None;

				if (id > 0)
				{
					if (auto* weaponConfigPtr = PrefabAssets::Get().GetWeaponConfig(id))
					{
						if (m_usableWeaponTypeList[weaponConfigPtr->m_weaponType] == true)
						{
							weaponConfig.emplace(*weaponConfigPtr);
							weaponType = weaponConfigPtr->m_weaponType;
						}
					}
				}

				auto it = std::find_if(m_initialWeaponConfigList.begin(), m_initialWeaponConfigList.end(),
					[&](auto elemPair) { return elemPair.first == weaponType; });
				if (it == m_initialWeaponConfigList.end())
				{
					m_initialWeaponConfigList.emplace_back(std::make_pair(weaponType, weaponConfig));
				}
				else
				{
					TRACE_CHANNEL("GAMEOBJECT_INIT", "Loading the same weapon type more than once - this should never happen!");
					it->second = weaponConfig;
				}
			}
		}

		return true;
	}

	ratchet::CreatureConfig::~CreatureConfig()
	{
	}
}

