#pragma once
#include "GameObjectConfig.h"
namespace ratchet
{
	struct CreatureConfig : public GameObjectConfig
	{
		Faction m_Faction;
		MovementType m_movementType;
		ColliderType m_colliderType;
		ColliderShapeType m_colliderShapeType;

		float m_movingSpeed;
		float m_fallingSpeed;
		float m_jumpingSpeed;

		//Cosntructors
		CreatureConfig();

		//Destructors
		~CreatureConfig();
	};
}

