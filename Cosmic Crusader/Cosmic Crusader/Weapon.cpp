#include "stdafx.h"
#include "Weapon.h"
#include "Bullet.h"

#include "PrefabAssets.h"

#include "SceneManager.h"



namespace ratchet
{
	std::map<Weapon::TYPE, std::queue<Bullet*>> Weapon::s_availableBulletList;
	std::map<Weapon::TYPE, std::list<Bullet*>> Weapon::s_inUseBulletList;

	Weapon::Weapon()
	{
		if (s_availableBulletList.empty())
		{
			for (int weaponTypeIndex = 0; weaponTypeIndex < static_cast<int>(Weapon::TYPE::Count); weaponTypeIndex++)
			{
				auto weaponType = static_cast<Weapon::TYPE>(weaponTypeIndex);
				s_availableBulletList.emplace(weaponType, std::queue<Bullet*>());
			}
		}

		if (s_inUseBulletList.empty())
		{
			for (int weaponTypeIndex = 0; weaponTypeIndex < static_cast<int>(Weapon::TYPE::Count); weaponTypeIndex++)
			{
				auto weaponType = static_cast<Weapon::TYPE>(weaponTypeIndex);
				s_inUseBulletList.emplace(weaponType, std::list<Bullet*>());
			}
		}
	}

	Weapon::Weapon(const Weapon& weapon) : Weapon()
	{
		m_weaponType = weapon.m_weaponType;
		m_currentAmmo = weapon.m_currentAmmo;
	}

	void Weapon::ClearWeaponList()
	{
		for (auto& pair : s_availableBulletList)
		{
			auto& bulletQueue = pair.second;
			while (!bulletQueue.empty())
			{
				bulletQueue.pop();
			}
		}

		s_availableBulletList.clear();
	}

	void Weapon::ClearBulletList()
	{

		for (auto& pair : s_inUseBulletList)
		{
			pair.second.clear();
		}
		s_inUseBulletList.clear();

		for (auto& pair : s_availableBulletList)
		{
			while (!pair.second.empty())
			{
				pair.second.pop();
			}
		}
		s_availableBulletList.clear();
	}

	void Weapon::Fire(const sf::Vector2f position, const float rotation, const sf::Vector2f direction, const bool facingRight)
	{
	#ifdef IS_RATCHET_DEBUG
		TRACE_CHANNEL("WEAPON_FIRE", "Spawning bullet");
	#endif	
		auto* bullet = findOrCreateBulletFromPool(position, rotation, facingRight);
		bullet->setPositionRotationOrientation(position, rotation, facingRight);
		bullet->setActive(true);
		if (auto* bulletObj = dynamic_cast<Bullet*>(bullet))
		{
			bulletObj->setBulletPositionCenter(position, direction, facingRight);

			bulletObj->launchBullet(direction, bulletObj->m_bulletSpeed);

			float volume = m_weaponSound.getVolume();

			volume = SceneManager::Get().GetSoundEffectsVolume();

			m_weaponSound.setVolume(volume);

			m_weaponSound.play();

			s_inUseBulletList[m_weaponType].push_back(bulletObj);

		}
	}

	void Weapon::releaseBullet(Bullet* bulletToRelease)
	{
		for (int weaponTypeIndex = 0; weaponTypeIndex < static_cast<int>(Weapon::TYPE::Count); weaponTypeIndex++)
		{
			auto weaponType = static_cast<Weapon::TYPE>(weaponTypeIndex);
			for (auto inUseIt = s_inUseBulletList[weaponType].begin(); inUseIt != s_inUseBulletList[weaponType].end(); inUseIt++)
			{
				if (*inUseIt == bulletToRelease)
				{
					inUseIt = s_inUseBulletList[weaponType].erase(inUseIt);

					bulletToRelease->setActive(false);
					s_availableBulletList[weaponType].push(bulletToRelease);
					return;
				}
			}
		}
	}

	Bullet* Weapon::findOrCreateBulletFromPool(const sf::Vector2f position, const float rotationDegrees, const bool orientation)
	{
		if (s_availableBulletList[m_weaponType].empty() == false)
		{
			auto* availableBullet = s_availableBulletList[m_weaponType].front();
			availableBullet->setPositionRotationOrientation(position, rotationDegrees, orientation);
			s_availableBulletList[m_weaponType].pop();

			auto& bulletList = s_inUseBulletList[m_weaponType];

			for (auto& bullet : bulletList)
			{
				if (auto* buletobj = dynamic_cast<Bullet*>(bullet))
				{
					float dmamage = buletobj->m_damage;
				}
			}

			return availableBullet;
		}
		else
		{
			// Create new inactive bullets in the pool.
			for (int i = 0; i < m_bulletPoolIncrementation; i++)
			{
				auto* obj = GameObject::Instantiate<Bullet, BulletConfig>(*PrefabAssets::Get().GetBulletConfig(m_bulletID), position, rotationDegrees, orientation);
				obj->setActive(false);
				if (auto* bullet = dynamic_cast<Bullet*>(obj))
				{
					bullet->m_damage = m_weaponDamage;
					s_availableBulletList[m_weaponType].push(bullet);

				}
			}

			return findOrCreateBulletFromPool(position, rotationDegrees, orientation);
		}
	}
}

