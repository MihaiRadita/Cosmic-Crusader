#include "stdafx.h"
#include "Item.h"

#include "SceneManager.h"

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
        m_springForce = config.m_springForce;
        m_animationTimeLimit = config.m_animationTimeLimit;
        m_isAnimationPlaying = config.m_isAnimationPlaying;
        m_spritePath = config.spriteTexturePath;
        //m_isItemAccessible = config.m_isItemAccessible;


        if (m_itemType == ItemType::AmmoRecharger || m_itemType == ItemType::HealthRecharger)
        {
            if (!m_spriteTextureOn.loadFromFile(m_spriteTextureOnPath))
            {
                std::cout << "Texture On Culd not load!" << std::endl;
            }

            if (!m_spriteTextureOff.loadFromFile(m_spriteTextureOffPath))
            {
                std::cout << "Texture Off Culd not load!" << std::endl;
            }
        }


        if (m_itemType == ItemType::Spring)
        {
            m_itemAnimator = new Animator();

            m_itemAnimation = new AnimationItem(m_spritePath);

            m_itemAnimator->setAnimation(m_itemAnimation);
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
        else if (m_itemType == ItemType::Spring)
        {

            updateItemsAnimations();
            Player* player = dynamic_cast<Player*>(m_target);
            if (player)
            {
                if (player->getIsOnSpring())
                {
                    player->m_collider->aaplyForce(b2Vec2(0.f, -1), m_springForce);
                }
            }
        }
    }

    void Item::render(sf::RenderTarget& target)
    {
        GameObject::render(target);
        //m_collider->drawColliderCenterBased(target);
    }

    void Item::updateItemsAnimations()
    {
        if (m_itemType == ItemType::Spring)
        {
            if (!m_itemAnimator && !m_itemAnimation)
            {
                return;
            }

            if (m_itemAnimation->isAnimationReachedEnd())
            {

                m_isAnimationPlaying = false;
                m_itemAnimation->resetAnimationFrame(m_sprite);
                m_itemAnimation->resetPlayerAnimTimer();
                m_itemAnimation->resetCurrentAnimIndex();
        
            }

            if (auto* player = dynamic_cast<Player*>(m_target))
            {
                if (player->getIsOnSpring())
                {
                    m_isAnimationPlaying = true;
                }
            }

            if (m_isAnimationPlaying)
            {
                m_itemAnimator->play(m_itemAnimator->getAbstractAnimation(), m_sprite);
            }
        }
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


                                AddItemDestroyedID();
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

                        AddItemDestroyedID();
                        GameObject::addGameObjectoDestory(this);
                    }
                }
            }
           
            if (m_itemType == ItemType::Spring)
            {
                if (player->getIsOnSpring())
                {
                    player->m_collider->aaplyForce(b2Vec2(0.f, -1), m_springForce);
                    
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

    void Item::OnCollisionEnter(GameObject* obj)
    {

        

      
    }

    void Item::OnCollisionExit(GameObject* obj)
    {
    
    }

    void Item::serialise(nlohmann::json& jsonFile)
    {
        GameObject::serialise(jsonFile);

        auto& propID = jsonFile["id"];


        for (auto& prop : jsonFile["properties"])
        {
            auto& propName = prop["name"];
            auto& proValue = prop["value"];
           

         
            if (propName == "isItemAccessible")
            {

                if (!SceneManager::Get().m_items_destroyedID_index.empty())
                {
                    auto& map = SceneManager::Get().m_items_destroyedID_index;

                    for (auto it = map.begin(); it != map.end(); )
                    {
                        if (it->first == propID)
                        {
                            proValue = false;
                            it = map.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }
            }
        }
    }

    void Item::Start()
    {
        if (m_itemType == ItemType::HealthRecharger)
        {
            m_sprite.setTexture(m_spriteTextureOn);
        }

        if (m_itemType == ItemType::Spring)
        {
            m_itemAnimation->SetAnimTimeLimit(m_animationTimeLimit);
        
            PostCosntructFixup();
        }

        SetFriendTarget(m_faction);
    }

    void Item::AddItemDestroyedID()
    {

        //GameObject::DestroyCollider();

        for (size_t i = 0; i < GameObject::s_gameObjects.size(); i++)
        {
            if (GameObject::s_gameObjects[i] == this)
            {
                SceneManager::Get().m_items_destroyedID_index.insert({ m_objectId, i });
                break;
            }
        }
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