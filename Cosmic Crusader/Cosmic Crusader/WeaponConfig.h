#pragma once

#include "GameObjectConfig.h"

#include "Weapon.h"

namespace ratchet
{
	struct WeaponConfig : public GameObjectConfig
	{
	public:
		WeaponConfig(int ammo, int damage, bool isWeaponAccesible);

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;

		//Weapon features
		int m_damage;
		int m_MaxAmmo;
		bool m_isWeaponAccessible;

		int m_bulletID = -1;

		Weapon::TYPE m_weaponType;
		float m_weaponShootPointOffsetX;
		float m_weaponShootPointOffsetY;
		int m_bulletPoolIncrementation;


		float m_weponDamage;

		//Weapon Shooting Points Offsets
		sf::Vector2f m_shootingOffsetAngle0;
		sf::Vector2f m_shootingOffsetAngle45;
		sf::Vector2f m_shootingOffsetAngle90;
		sf::Vector2f m_shootingOffsetAngleMinus45;
		
		sf::Vector2f m_characterStartPointShootingOffset;

	};

}

