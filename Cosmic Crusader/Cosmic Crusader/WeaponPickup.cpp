#include "stdafx.h"
#include "WeaponPickup.h"

namespace ratchet
{
	void WeaponPickup::pickUp(Creature* creatureThatPickedUpTheWeapon)
	{
		creatureThatPickedUpTheWeapon->addWeapon(m_weaponType, m_weaponConfig);
	}
}