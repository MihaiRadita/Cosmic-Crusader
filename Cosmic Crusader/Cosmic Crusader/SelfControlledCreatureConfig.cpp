#include "stdafx.h"
#include "SelfControlledCreatureConfig.h"


namespace ratchet
{
	SelfControlledCreatureConfig::SelfControlledCreatureConfig() : CreatureConfig()
	{
		m_targetMaxDistanceDetectionX = 0.0f;
		m_targetMaxDistanceDetectionY = 0.0f;
		m_targetMaxDistanceLoseX = 0.0f;
		m_targetMaxDistanceLoseY = 0.0f;
		m_targetMaxDistanceAttackX = 0.0f;
		m_targetMaxDistanceAttackY = 0.0f;
	}

	SelfControlledCreatureConfig::~SelfControlledCreatureConfig()
	{

	}
}
