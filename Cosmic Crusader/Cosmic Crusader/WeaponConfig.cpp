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


		//Weapon Shooting Points Offsets
		
		//Start
		m_characterStartPointShootingOffset = sf::Vector2f(0.0f, 0.0f);

		//Angles
		m_shootingOffsetAngle0 = sf::Vector2f(0.0f, 0.0f);
		m_shootingOffsetAngle45 = sf::Vector2f(0.0f, 0.0f);
		m_shootingOffsetAngle90 = sf::Vector2f(0.0f, 0.0f);
		m_shootingOffsetAngleMinus45 = sf::Vector2f(0.0f, 0.0f);


	}
}