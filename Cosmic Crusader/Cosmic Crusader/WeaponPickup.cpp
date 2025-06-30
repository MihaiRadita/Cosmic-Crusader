#include "stdafx.h"
#include "WeaponPickup.h"

namespace ratchet
{
	void WeaponPickup::pickUp(Creature* creatureThatPickedUpTheWeapon)
	{
		creatureThatPickedUpTheWeapon->m_weaponsStartShootingPoint[m_weaponType] = m_StartPointShootingOffset;

		std::map<WeaponAnimation::ANGLE, sf::Vector2f> angleOffsets;

		for (auto& angle : creatureThatPickedUpTheWeapon->m_characterAngles)
		{
			if (angle == WeaponAnimation::ANGLE::Angle0)
			{
				angleOffsets[angle] = m_shootingOffsetAngle0;
			}
			else if (angle == WeaponAnimation::ANGLE::Angle45)
			{
				angleOffsets[angle] = m_shootingOffsetAngle45;
			}
			else if (angle == WeaponAnimation::ANGLE::Angle90)
			{
				angleOffsets[angle] = m_shootingOffsetAngle90;
			}
			else if (angle == WeaponAnimation::ANGLE::AngleMinus45)
			{
				angleOffsets[angle] = m_shootingOffsetAngleMinus45;
			}
		}

		for (const auto& [angle, offset] : angleOffsets)
		{
			creatureThatPickedUpTheWeapon->m_shootingPointsOffsets[m_weaponType][angle] = offset;
		}

		creatureThatPickedUpTheWeapon->setWeaponAccessible(m_weaponType, m_IsWeaponAccessible);
		creatureThatPickedUpTheWeapon->addWeapon(m_weaponType, m_weaponConfig);
		creatureThatPickedUpTheWeapon->setWeaponIndex(creatureThatPickedUpTheWeapon->getWeaponListSize() - 1);
		creatureThatPickedUpTheWeapon->setWeapon(creatureThatPickedUpTheWeapon->m_currentEquippedWeaponIndex);
	}
	WeaponPickup::WeaponPickup(const WeaponConfig& config): GameObject(config)
	{
		m_weaponConfig = config;
		
		if (m_weaponConfig.has_value())
		{
			m_weaponType = m_weaponConfig->m_weaponType;

			m_StartPointShootingOffset = m_weaponConfig->m_characterStartPointShootingOffset;

			m_shootingOffsetAngle0 = m_weaponConfig->m_shootingOffsetAngle0;
			m_shootingOffsetAngle45 = m_weaponConfig->m_shootingOffsetAngle45;
			m_shootingOffsetAngle90 = m_weaponConfig->m_shootingOffsetAngle90;
			m_shootingOffsetAngleMinus45 = m_weaponConfig->m_shootingOffsetAngleMinus45;
			m_weaponConfig->m_configLayer = config.m_configLayer;

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
			TRACE_CHANNEL(TR_WEAPON_PICKUP, "PLAYER HAS INTERACTING WITH WEAPON 1! ");
		}
	}

	void WeaponPickup::OnCollisionExit(GameObject* obj)
	{
		Player* player = dynamic_cast<Player*>(obj);

		if (player)
		{
			TRACE_CHANNEL(TR_WEAPON_PICKUP, "PLAYER HAS EXIT WITH WEAPON 1! ");
		}
	}

	void WeaponPickup::OnSensorEnter(GameObject* obj)
	{
		Player* player = dynamic_cast<Player*>(obj);
		if (player && m_isPickup == false)
		{
			m_isPickup = true;

			TRACE_CHANNEL(TR_WEAPON_PICKUP, "PLAYER HAS INTERACTING WITH WEAPON 1! ");

			bool m_isWeaponCharacterMathc = player->isWeaponMatchCharacter(m_weaponType);
			if (m_isWeaponCharacterMathc)
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
			TRACE_CHANNEL(TR_WEAPON_PICKUP, "PLAYER HAS EXIT WITH WEAPON 1! ");
		}
	}

	/*
	* isSensorEnter(GameObject* obj)
	* {
		}
	*/

}