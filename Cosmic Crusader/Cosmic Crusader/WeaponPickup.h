#pragma once

#include "GameObject.h"
#include "Creature.h"
#include "Weapon.h"
#include "WeaponConfig.h"

namespace ratchet
{
	class WeaponPickup : public GameObject
	{
		void pickUp(Creature* creatureThatPickedUpTheWeapon);

		Weapon::TYPE m_weaponType;
		std::optional<WeaponConfig> m_weaponConfig;
	};

}


