#include "stdafx.h"
#include "Weapon.h"

ratchet::Weapon::Weapon()
{
}

ratchet::Weapon::Weapon(const Weapon& weapon)
{
	m_weaponType = weapon.m_weaponType;
	m_currentAmmo = weapon.m_currentAmmo;
}
