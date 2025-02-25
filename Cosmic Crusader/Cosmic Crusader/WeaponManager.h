#pragma once

#include "Weapon.h"


namespace ratchet
{
	class WeaponManager
	{
	public:
		static WeaponManager* instance();
		const Weapon* getWeapon(Weapon::TYPE weaponType) const;

		~WeaponManager();

		void addAllWeapons();

		std::vector<Weapon*> m_weaponList;
	};

}

