#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	struct WeaponConfig : public GameObjectConfig
	{
	public:
		//WeaponConfig();
		WeaponConfig(int ammo, int damage);

		//Weapon features
		int m_damage;
		int m_MaxAmmo;
		Weapon::TYPE m_weaponType;
	};

}

