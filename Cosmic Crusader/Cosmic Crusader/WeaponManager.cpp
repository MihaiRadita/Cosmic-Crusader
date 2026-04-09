#include "stdafx.h"
#include "WeaponManager.h"

namespace ratchet
{
    WeaponManager* ratchet::WeaponManager::instance()
    {
        static WeaponManager instance;
        return &instance;
    }

    const Weapon* WeaponManager::getWeapon(Weapon::TYPE weaponType) const
    {
        for (const auto* weapon : m_weaponList)
        {
            if (weapon->m_weaponType == weaponType)
            {
                return weapon;
            }
        }

        return nullptr;
    }

    WeaponManager::~WeaponManager()
    {
        for (auto weapon : m_weaponList)
        {
            delete weapon;
        }
        m_weaponList.clear();
    }

    void WeaponManager::addAllWeapons()
    {
        Weapon* playerNoneWeapon = new Weapon(); 
        playerNoneWeapon->m_weaponType = Weapon::TYPE::None;
        m_weaponList.push_back(playerNoneWeapon);

        Weapon* playerBlaster1Weapon = new Weapon();
        playerBlaster1Weapon->m_weaponType = Weapon::TYPE::Blaster;
        m_weaponList.push_back(playerBlaster1Weapon);

        Weapon* enemy1Blaster1Weapon = new Weapon();
        enemy1Blaster1Weapon->m_weaponType = Weapon::TYPE::Enemy1Blaster;
        m_weaponList.push_back(enemy1Blaster1Weapon);

        Weapon* enemy2Blaster2Weapon = new Weapon();
        enemy2Blaster2Weapon->m_weaponType = Weapon::TYPE::Enemy2Blaster;
        m_weaponList.push_back(enemy2Blaster2Weapon);

    }

}
