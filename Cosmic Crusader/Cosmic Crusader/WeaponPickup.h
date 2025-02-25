#pragma once

#include "GameObject.h"
#include "Creature.h"
#include "Weapon.h"

namespace ratchet
{
	class WeaponPickup : public GameObject
	{
	public:
		void pickUp(Creature* creatureThatPickedUpTheWeapon);
		WeaponPickup(const WeaponConfig& config);

		Weapon::TYPE m_weaponType;
		std::optional<WeaponConfig> m_weaponConfig;
	};

}


