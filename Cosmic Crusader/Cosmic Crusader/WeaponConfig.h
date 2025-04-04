#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	struct WeaponConfig : public GameObjectConfig
	{
	public:
		//WeaponConfig();
		WeaponConfig(int ammo, int damage, bool isWeaponAccesible);

		//Weapon features
		int m_damage;
		int m_MaxAmmo;
		bool m_isWeaponAccessible;
		Weapon::TYPE m_weaponType;
	};

}

