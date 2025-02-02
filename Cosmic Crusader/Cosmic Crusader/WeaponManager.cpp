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

}
