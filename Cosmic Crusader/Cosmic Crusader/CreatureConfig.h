#pragma once
#include "GameObjectConfig.h"
#include "WeaponConfig.h"

namespace ratchet
{
	struct CreatureConfig : public GameObjectConfig
	{
		//Characters States

		//Characters Features
		float m_movingSpeed;
		float m_fallingSpeed;
		float m_jumpImpulse;
		float m_movingAirSpeed;


		std::map<Weapon::TYPE, bool> m_usableWeaponTypeList;
		std::vector <Weapon::TYPE> m_weaponTypeList;

		std::vector<std::pair<Weapon::TYPE, std::optional<WeaponConfig>>> m_initialWeaponConfigList;

		WeaponAnimation::ANGLE m_currentAngle;
		WeaponAnimation::STATE m_currentState;
		Weapon::TYPE m_currentWeaponType;

		int m_currentlyEquippedWeaponIndex = 0;

		//Cosntructors
		CreatureConfig();

		//Destructors
		~CreatureConfig();
	};
}

