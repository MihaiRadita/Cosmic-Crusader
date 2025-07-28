#include "stdafx.h"
#include "Weapon.h"
#include "Bullet.h"

#include "PrefabAssets.h"



namespace ratchet
{
	Weapon::Weapon()
	{
	}

	Weapon::Weapon(const Weapon& weapon)
	{
		m_weaponType = weapon.m_weaponType;
		m_currentAmmo = weapon.m_currentAmmo;
	}

	void Weapon::Fire(const sf::Vector2f& position, const float& rotation, const sf::Vector2f& direction, bool& m_facingRight)
	{
	#ifdef IS_RATCHET_DEBUG
		TRACE_CHANNEL("WEAPON_FIRE", "Spawning bullet");
	#endif	

		auto* bullet = GameObject::Instantiate<Bullet, BulletConfig>(*PrefabAssets::Get().GetBulletConfig(m_WeaponID), position, rotation, m_facingRight);

		if (auto* bulletObj = dynamic_cast<Bullet*>(bullet))
		{
			bulletObj->setBulletPositionCenter(position, direction, m_facingRight);

			bulletObj->launchBullet(direction, bulletObj->m_bulletSpeed);
		}
	}
}

