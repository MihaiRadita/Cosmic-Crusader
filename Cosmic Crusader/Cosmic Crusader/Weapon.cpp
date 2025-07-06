#include "stdafx.h"
#include "Weapon.h"
#include "Bullet.h"

#include "PrefabAssets.h"

ratchet::Weapon::Weapon()
{
}

ratchet::Weapon::Weapon(const Weapon& weapon)
{
	m_weaponType = weapon.m_weaponType;
	m_currentAmmo = weapon.m_currentAmmo;
}

void ratchet::Weapon::Fire(const sf::Vector2f& positon, const float& rotation, const float& direction)
{
#ifdef IS_RATCHET_DEBUG
	TRACE_CHANNEL(TR_WEAPON_FIRE, "Spawning bullet");
#endif	
	GameObject::Instantiate<Bullet, BulletConfig>(*PrefabAssets::Get().GetBulletConfig(m_WeaponID), positon, rotation);
}
