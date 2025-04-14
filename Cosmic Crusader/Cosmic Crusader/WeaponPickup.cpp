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
				player->setWeaponAccessible(m_weaponType, m_IsWeaponAccessible);
				pickUp(player);
				player->setWeaponIndex(player->getWeaponListSize() - 1);
				player->setWeapon(player->m_currentEcquipedWeaponIndex);

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