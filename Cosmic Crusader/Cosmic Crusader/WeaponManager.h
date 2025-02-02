#pragma once

#include "Weapon.h"


namespace ratchet
{
	class WeaponManager
	{
	public:
		static WeaponManager* instance();
		const Weapon* getWeapon(Weapon::TYPE weaponType) const;

		std::vector<Weapon*> m_weaponList;
	};

}

