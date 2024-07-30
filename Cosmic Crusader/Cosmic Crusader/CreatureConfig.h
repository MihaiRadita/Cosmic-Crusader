#pragma once
#include "GameObjectConfig.h"
namespace ratchet
{
	struct CreatureConfig : public GameObjectConfig
	{
		//Characters States

		//Characters Features
		float m_movingSpeed;
		float m_fallingSpeed;
		float m_jumpingSpeed;

		//Cosntructors
		CreatureConfig();

		//Destructors
		~CreatureConfig();
	};
}

