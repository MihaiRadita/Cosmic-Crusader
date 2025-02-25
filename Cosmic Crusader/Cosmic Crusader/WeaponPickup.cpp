#include "stdafx.h"
#include "WeaponPickup.h"

namespace ratchet
{
	void WeaponPickup::pickUp(Creature* creatureThatPickedUpTheWeapon)
	{
		creatureThatPickedUpTheWeapon->addWeapon(m_weaponType, m_weaponConfig);
	}
	WeaponPickup::WeaponPickup(const WeaponConfig& config): GameObject(config)
	{
		m_weaponConfig = config;
		
		if (m_weaponConfig.has_value())
		{
			m_weaponType = m_weaponConfig->m_weaponType;
		}

	}
}