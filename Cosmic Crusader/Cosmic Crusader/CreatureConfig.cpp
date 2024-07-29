#include "stdafx.h"
#include "CreatureConfig.h"


namespace ratchet
{
	ratchet::CreatureConfig::CreatureConfig() : GameObjectConfig()
	{
		m_movingSpeed = 0.f;
		m_fallingSpeed = 0.f;
		m_jumpingSpeed = 0.f;

		m_Faction = Faction::FACTION_UNKNOWN;
		m_movementType = MovementType::MOVEMENTTYPE_UNKNOWN;
		m_colliderType = ColliderType::COLLIDERTYPE_UNKNOWN;
		m_colliderShapeType = ColliderShapeType::COLLIDERSHAPETYPE_UNKNOWN;

	}

	ratchet::CreatureConfig::~CreatureConfig()
	{
	}
}

