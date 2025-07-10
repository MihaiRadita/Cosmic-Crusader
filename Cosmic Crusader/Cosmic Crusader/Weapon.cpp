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

	void Weapon::Fire(const sf::Vector2f& positon, const float& rotation, const float& direction, bool& m_facingRight)
	{
	#ifdef IS_RATCHET_DEBUG
		TRACE_CHANNEL("WEAPON_FIRE", "Spawning bullet");
	#endif	

		GameObject::Instantiate<Bullet, BulletConfig>(*PrefabAssets::Get().GetBulletConfig(m_WeaponID), positon, rotation, m_facingRight);

		//sf::Vector2f positiontoModify = positon;
		//if (auto* bulletObj = dynamic_cast<Bullet*>(bullet))
		//{
		//	bulletObj->setBulletPositionCenter(positiontoModify, 1);
		//}

		m_weaponType;
	}
}

