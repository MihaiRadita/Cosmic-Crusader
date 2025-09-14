#pragma once

#include "WeaponConfig.h"
#include "Weapon.h"

#include "animations/AnimationBase.h"

#include "CreatureConfig.h"


namespace ratchet
{
	struct SelfControlledCreatureConfig : public CreatureConfig
	{

		//Variables

		//Target detection distance
		float m_targetMaxDistanceDetectionX;
		float m_targetMaxDistanceDetectionY;

		//target lose distance
		float m_targetMaxDistanceLoseX;
		float m_targetMaxDistanceLoseY;

		//target distance to attack
		float m_targetMaxDistanceAttackX;
		float m_targetMaxDistanceAttackY;

		//Constructor
		SelfControlledCreatureConfig();

		//
		~SelfControlledCreatureConfig();
	};
}


