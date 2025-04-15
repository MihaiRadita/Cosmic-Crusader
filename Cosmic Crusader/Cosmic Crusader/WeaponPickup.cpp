#include "stdafx.h"
#include "WeaponPickup.h"

namespace ratchet
{
	void WeaponPickup::pickUp(Creature* creatureThatPickedUpTheWeapon)
	{
		creatureThatPickedUpTheWeapon->setWeaponAccessible(m_weaponType, m_IsWeaponAccessible);
		creatureThatPickedUpTheWeapon->addWeapon(m_weaponType, m_weaponConfig);
		creatureThatPickedUpTheWeapon->setWeaponIndex(creatureThatPickedUpTheWeapon->getWeaponListSize() - 1);
		creatureThatPickedUpTheWeapon->setWeapon(creatureThatPickedUpTheWeapon->m_currentEcquipedWeaponIndex);
	}
	WeaponPickup::WeaponPickup(const WeaponConfig& config): GameObject(config)
	{
		m_weaponConfig = config;
		
		if (m_weaponConfig.has_value())
		{
			m_weaponType = m_weaponConfig->m_weaponType;
		}
		m_IsWeaponAccessible = config.m_isWeaponAccessible;
	}

	WeaponPickup::~WeaponPickup()
	{
	}

	void WeaponPickup::OnCollisionEnter(GameObject* obj)
	{
		Player* player = dynamic_cast<Player*>(obj);

		if (player)
		{
			std::cout << "PLAYER HAS INTERACTING WITH WEAPON 1! " << std::endl;
		}
	}

	void WeaponPickup::OnCollisionExit(GameObject* obj)
	{
		Player* player = dynamic_cast<Player*>(obj);

		if (player)
		{
			std::cout << "PLAYER HAS EXIT WITH WEAPON 1! " << std::endl;
		}
	}

	void WeaponPickup::OnSensorEnter(GameObject* obj)
	{
		Player* player = dynamic_cast<Player*>(obj);
		if (player && m_isPickup == false)
		{
			m_isPickup = true;

			std::cout << "PLAYER HAS INTERACTING WITH WEAPON 1! " << std::endl;

			bool m_isWeaponCharacterMathc = player->isWeaponMatchCharacter(m_weaponType);
			if(m_isWeaponCharacterMathc)
			{
				
				pickUp(player);

				DestroyGameObject();
			}
			
			//m_collider->getBody()->SetEnabled(false);
			//Physics::addToDestroyList(this);
			
		}
	}

	void WeaponPickup::OnSensorExit(GameObject* obj)
	{
		Player* player = dynamic_cast<Player*>(obj);

		if (player)
		{
			std::cout << "PLAYER HAS EXIT WITH WEAPON 1! " << std::endl;
		}
	}

	/*
	* isSensorEnter(GameObject* obj)
	* {
		}
	*/

}