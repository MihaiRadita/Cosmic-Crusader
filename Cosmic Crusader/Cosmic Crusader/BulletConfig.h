#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	class BulletConfig : public GameObjectConfig
	{
	public:

		BulletConfig(); 

		float m_damage;
		float m_ammo;

		float m_bulletLifeLimit;

		float m_BulletSpeed;

		std::string m_ID;

	private:
	};
}


