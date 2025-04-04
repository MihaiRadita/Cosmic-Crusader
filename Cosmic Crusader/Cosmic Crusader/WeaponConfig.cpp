#include "stdafx.h"
#include "WeaponConfig.h"

namespace ratchet 
{
	/*WeaponConfig::WeaponConfig()
	{
	}*/
	WeaponConfig::WeaponConfig(int ammo, int damage, bool isWeaponAccessible) : GameObjectConfig()
	{
		m_MaxAmmo = ammo;
		m_damage = damage;
		m_isWeaponAccessible = isWeaponAccessible;
	}
}