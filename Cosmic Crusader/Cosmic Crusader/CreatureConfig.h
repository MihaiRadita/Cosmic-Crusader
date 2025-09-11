#pragma once
#include "WeaponConfig.h"
#include "Weapon.h"

#include "animations/AnimationBase.h"


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

		//target detect distance 
		float m_targetMaxDistanceDetectionX;
		float m_targetMaxDistanceDetectionY;

		//target lose distance
		float m_targetMaxDistanceLoseX;
		float m_targetMaxDistanceLoseY;
	
		//Anlges
		float m_AngleBase;
		std::vector<WeaponAnimation::ANGLE> m_characterAngles;

		//Character Body Areas
		sf::Vector2f m_bodyShoulderPosition;
		float m_bodShoulderOffset;


		std::map<Weapon::TYPE, bool> m_usableWeaponTypeList;
		std::vector <Weapon::TYPE> m_weaponTypeList;

		std::vector<std::pair<Weapon::TYPE, std::optional<WeaponConfig>>> m_initialWeaponConfigList;

		WeaponAnimation::ANGLE m_currentAngle;
		WeaponAnimation::STATE m_currentState;
		Weapon::TYPE m_currentWeaponType;

		std::vector<ANIMATION_STATE> m_animationStates;

		ANIMATION_STATE m_currentAnimationState;

		int m_currentlyEquippedWeaponIndex = 0;

		//Cosntructors
		CreatureConfig();

		//Destructors
		~CreatureConfig();
	};
}

