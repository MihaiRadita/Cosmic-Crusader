#include "stdafx.h"
#include "Item.h"

namespace ratchet
{
   
    Item::Item(ItemConfig& config) : GameObject(config)
    {
        m_itemType = config.m_itemType;
        m_itemContenntValue = config.m_itemContenntValue;
        m_itemRefferdId = config.m_itemRefferdId;
        m_itemDisableTimePass = config.m_itemDisableTimePass;
        m_spriteTextureOnPath = config.m_spriteTextureOnPath;
        m_spriteTextureOffPath = config.m_spriteTextureOffPath;
        m_isItemInteracting = config.m_isItemInteracting;
        m_isItemUsed = config.m_isItemUsed;

        if (!m_spriteTextureOn.loadFromFile(m_spriteTextureOnPath))
        {
            std::cout << "Texture On Culd not load!" << std::endl;
        }

        if (!m_spriteTextureOff.loadFromFile(m_spriteTextureOffPath))
        {
            std::cout << "Texture Off Culd not load!" << std::endl;
        }

        m_itemDisabledTimer.Restart();
    }

    Item::~Item()
    {

    }

    void Item::handleItemtEvent(sf::Event& event)
    {

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::E)
            {
                if (m_isItemInteracting)
                {
                    if (!m_isItemUsed)
                    {
                        if (m_itemType == ItemType::HealthRecharger)
                        {
                            if (m_target->m_health < m_target->m_maxHealth)
                            {
                                m_target->restoreMaxHealth();
                                m_itemDisabledTimer.Restart();
                                m_isItemUsed = true;
                            }
                        }
                        else if (m_itemType == ItemType::AmmoRecharger)
                        {
                            if (m_target->checkAnyWeaponAmmoNeedsRestore())
                            {
                                m_target->restoreMaxWeaponsAmmo();
                                m_itemDisabledTimer.Restart();
                                m_isItemUsed = true;
                            }
                        }
                    }
                }
            }
        }
    }

    void Item::update()
    {
        if (m_itemType == ItemType::HealthRecharger || m_itemType == ItemType::AmmoRecharger)
        {
            if (!m_isItemUsed)
            {
                if (m_sprite.getTexture() != &m_spriteTextureOn)
                {
                    m_sprite.setTexture(m_spriteTextureOn);
                }
                m_itemDisabledTimer.Restart();
            }
            else
            {
                if (m_sprite.getTexture() != &m_spriteTextureOff)
                {
                    m_sprite.setTexture(m_spriteTextureOff);
                }

                if (m_itemDisabledTimer.GetElapsed().asSeconds() >= m_itemDisableTimePass)
                {
                    m_isItemUsed = false;
                    m_itemDisabledTimer.Restart();
                }
            }
        }
    }

    void Item::render(sf::RenderTarget& target)
    {
        GameObject::render(target);
        m_collider->drawColliderCenterBased(target);
    }

    void Item::SetFriendTarget(Faction& faction)
    {
        for (auto* obj : s_gameObjects)
        {
            if (obj != this)
            {
                if (faction != Faction::FACTION_UNKNOWN && obj->m_faction != Faction::FACTION_UNKNOWN)
                {
                    if (faction == obj->m_faction)
                    {
                        auto* player = dynamic_cast<Player*>(obj);
                        if (player)
                        {
                            m_target = (Creature*)obj;
                            break;
                        }
                    }
                }
            }
        }
    }

    void Item::OnSensorEnter(GameObject* obj)
    {
        Player* player = dynamic_cast<Player*>(obj);
        if (player && m_isPickup == false)
        {

            if (m_itemType == ItemType::HealthRecharger || m_itemType == ItemType::AmmoRecharger)
            {
                m_isItemInteracting = true;
            }
            else
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
    }

    void Item::OnSensorExit(GameObject* obj)
    {
        if (m_itemType == ItemType::HealthRecharger || m_itemType == ItemType::AmmoRecharger)
        {
           m_isItemInteracting = false;
        }
    }

    void Item::Start()
    {
        if (m_itemType == ItemType::HealthRecharger)
        {
            m_sprite.setTexture(m_spriteTextureOn);
        }
        SetFriendTarget(m_faction);
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