#include "stdafx.h"
#include "CreatureConfig.h"


namespace ratchet
{
	ratchet::CreatureConfig::CreatureConfig() : GameObjectConfig()
	{
		m_movingSpeed = 0.f;
		m_fallingSpeed = 0.f;
		m_jumpingSpeed = 0.f;
	}

	ratchet::CreatureConfig::~CreatureConfig()
	{
	}
}

