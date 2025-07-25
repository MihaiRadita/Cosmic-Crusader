#pragma once

#include "GameObjectConfig.h"

#include "Weapon.h"

namespace ratchet
{
	struct WeaponConfig : public GameObjectConfig
	{
	public:
		WeaponConfig(int ammo, int damage, bool isWeaponAccesible);

		//Weapon features
		int m_damage;
		int m_MaxAmmo;
		bool m_isWeaponAccessible;
		Weapon::TYPE m_weaponType;
		float m_weaponShootPointOffsetX;
		float m_weaponShootPointOffsetY;

		//Weapon Shooting Points Offsets
		sf::Vector2f m_shootingOffsetAngle0;
		sf::Vector2f m_shootingOffsetAngle45;
		sf::Vector2f m_shootingOffsetAngle90;
		sf::Vector2f m_shootingOffsetAngleMinus45;
		
		sf::Vector2f m_characterStartPointShootingOffset;
	};

}

