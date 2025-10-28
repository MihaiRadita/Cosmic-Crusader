#include "stdafx.h"
#include "WeaponConfig.h"

#include "game/Game.h"

namespace ratchet 
{
	WeaponConfig::WeaponConfig(int ammo, int damage, bool isWeaponAccessible) : GameObjectConfig()
	{
		m_MaxAmmo = ammo;
		m_damage = damage;
		m_isWeaponAccessible = isWeaponAccessible;


		//Weapon Shooting Points Offsets
		
		//Start
		m_characterStartPointShootingOffset = sf::Vector2f(0.0f, 0.0f);

		//Angles
		m_shootingOffsetAngle0 = sf::Vector2f(0.0f, 0.0f);
		m_shootingOffsetAngle45 = sf::Vector2f(0.0f, 0.0f);
		m_shootingOffsetAngle90 = sf::Vector2f(0.0f, 0.0f);
		m_shootingOffsetAngleMinus45 = sf::Vector2f(0.0f, 0.0f);


	}
	bool WeaponConfig::serialise(nlohmann::json& jsonFile)
	{
		return GameObjectConfig::serialise(jsonFile);
	}
	bool WeaponConfig::deserialise(const nlohmann::json& jsonFile)
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
		m_colliderConfig = new RectAngleColliderConfig();

		float angle0X = 0.0f;
		float angle0Y = 0.0f;
		float angle45X = 0.0f;
		float angle45Y = 0.0f;
		float angle90X = 0.0f;
		float angle90Y = 0.0f;
		float angleMinus45X = 0.0f;
		float angleMinus45Y = 0.0f;

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
			if (propertyName == "ammo")
			{
				m_MaxAmmo = propertyValue.get<float>();
			}
			if (propertyName == "bulletIncrementation")
			{
				m_bulletPoolIncrementation = propertyValue.get<int>();
			}

			if (propertyName == "characterStartPointShootingOffsetX")
			{
				m_weaponShootPointOffsetX = propertyValue.get<float>();
			}
			if (propertyName == "characterStartPointShootingOffsetY")
			{
				m_weaponShootPointOffsetY = propertyValue.get<float>();
			}

			m_characterStartPointShootingOffset = sf::Vector2f(m_weaponShootPointOffsetX, m_weaponShootPointOffsetY);

			if (propertyName == "layer")
			{
				m_configLayer = propertyValue.get<std::string>();
			}

			if (propertyName == "damage")
			{
				m_damage = propertyValue.get<float>();
			}

			if (propertyName == "movementType")
			{
				m_movementType = static_cast<MovementType>(propertyValue.get<int>());
			}
			if (propertyName == "colliderType")
			{
				m_colliderType = static_cast<ColliderType>(propertyValue.get<int>());
			}
			if (propertyName == "weaponType")
			{
				m_weaponType = static_cast<Weapon::TYPE>(propertyValue.get<int>());
			}


			if (propertyName == "startSpriteTexturePath")
			{
				startSpriteTexturePath = propertyValue.get<std::string>();
			}

			//Weapon Shooting Config Points Angles


			if (propertyName == "shootingOffsetAngle0X")
			{
				angle0X = propertyValue.get<float>();
			}
			if (propertyName == "shootingOffsetAngle0Y")
			{
				angle0Y = propertyValue.get<float>();
			}
			m_shootingOffsetAngle0 = sf::Vector2f(angle0X, angle0Y);

			if (propertyName == "shootingOffsetAngle45X")
			{
				angle45X = propertyValue.get<float>();
			}
			if (propertyName == "shootingOffsetAngle45Y")
			{
				angle45Y = propertyValue.get<float>();
			}
			m_shootingOffsetAngle45 = sf::Vector2f(angle45X, angle45Y);

			if (propertyName == "shootingOffsetAngle90X")
			{
				angle90X = propertyValue.get<float>();
			}
			if (propertyName == "shootingOffsetAngle90Y")
			{
				angle90Y = propertyValue.get<float>();
			}
			m_shootingOffsetAngle90 = sf::Vector2f(angle90X, angle90Y);

			if (propertyName == "shootingOffsetAngleMinus45X")
			{
				angleMinus45X = propertyValue.get<float>();
			}
			if (propertyName == "shootingOffsetAngleMinus45Y")
			{
				angleMinus45Y = propertyValue.get<float>();
			}
			m_shootingOffsetAngleMinus45 = sf::Vector2f(angleMinus45X, angleMinus45Y);


			if (propertyName == "colliderLayer")
			{
				m_colliderConfig->m_layer = static_cast<PhysicsLayer>(propertyValue.get<int>());
			}
			if (propertyName == "colliderType")
			{
				m_colliderConfig->m_bodyDef.type = static_cast<b2BodyType>(propertyValue.get<int>());

			}

			if (propertyName == "fixedRotation")
			{
				m_colliderConfig->m_bodyDef.fixedRotation = propertyValue.get<bool>();
			}

			if (propertyName == "density")
			{
				m_colliderConfig->m_fixtureDef.density = propertyValue.get<float>();
			}
			if (propertyName == "friction")
			{
				m_colliderConfig->m_fixtureDef.friction = propertyValue.get<float>();
			}

			if (propertyName == "restitution")
			{
				m_colliderConfig->m_fixtureDef.restitution = propertyValue.get<float>();
			}
			if (propertyName == "isSensor")
			{
				m_colliderConfig->m_fixtureDef.isSensor = propertyValue.get<bool>();
			}

		}

		return true;
	}
}