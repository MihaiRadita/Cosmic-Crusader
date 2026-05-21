#include "stdafx.h"
#include "Item.h"

namespace ratchet
{
    Item::Item(ItemConfig& config) : GameObject(config)
    {
        m_itemType = config.m_itemType;
        m_itemContenntValue = config.m_itemContenntValue;
        m_itemRefferdId = config.m_itemRefferdId;
    }

    Item::~Item()
    {

    }

    void Item::update()
    {

    }

    void Item::render(sf::RenderTarget& target)
    {
        GameObject::render(target);
        m_collider->drawColliderCenterBased(target);
    }

    void Item::OnSensorEnter(GameObject* obj)
    {
        Player* player = dynamic_cast<Player*>(obj);
        if (player && m_isPickup == false)
        {
            TRACE_CHANNEL("WEAPON_PICKUP", "PLAYER HAS INTERACTING WITH WEAPON 1! ");

            if (m_itemType == ItemType::Ammo)
            {
                for (auto* weapon : player->m_ownedWeaponList)
                {
                    if (weapon->m_WeaponID == m_itemRefferdId)
                    {
                        if (weapon->m_currentAmmo < weapon->m_maxAmmo)
                        {

                            m_isPickup = true;
                            pickUpItem(player);

                            GameObject::addGameObjectoDestory(this);
                        }
 
                    }
                }
            }
            else if (m_itemType == ItemType::Health)
            {
                if (player->m_health < player->m_maxHealth)
                {
                    m_isPickup = true;
                    pickUpItem(player);

                    GameObject::addGameObjectoDestory(this);
                }
            }
        }
    }

    void Item::OnSensorExit(GameObject* obj)
    {

    }

    void Item::Start()
    {
        
    }

    void Item::pickUpItem(Creature* creatureThatPickedUpItem)
    {
        if (m_itemType == ItemType::Health)
        {
            creatureThatPickedUpItem->increaseHealth(m_itemContenntValue);
        }
        else if (m_itemType == ItemType::Ammo)
        {
            creatureThatPickedUpItem->increaseAmmo(m_itemContenntValue, m_itemRefferdId);
        }
    }
}