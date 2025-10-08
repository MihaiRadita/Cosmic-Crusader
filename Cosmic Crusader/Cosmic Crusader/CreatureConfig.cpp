#include "stdafx.h"
#include "CreatureConfig.h"



namespace ratchet
{
	ratchet::CreatureConfig::CreatureConfig() : GameObjectConfig()
	{
		m_movingSpeed = 0.f;
		m_fallingSpeed = 0.f;
		m_jumpImpulse = 0.f;

		m_recoilTime = 0.0f;
		m_fireRate = 0.0f;
	}

	ratchet::CreatureConfig::~CreatureConfig()
	{
	}
}

