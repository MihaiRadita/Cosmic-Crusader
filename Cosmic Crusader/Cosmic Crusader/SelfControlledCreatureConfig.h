#pragma once

#include "WeaponConfig.h"
#include "Weapon.h"

#include "animations/AnimationBase.h"

#include "CreatureConfig.h"


namespace ratchet
{

	enum class EnemyType{None =0 ,Ground , Flying};

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

		float m_minFollowHeightOffset;
		float m_minCeilingDistance;

		float m_flySpeed;

		EnemyType m_enemyType;

		std::string m_objectLayerName;

		//Constructor
		SelfControlledCreatureConfig();

		//
		~SelfControlledCreatureConfig();


		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;
	};
}


