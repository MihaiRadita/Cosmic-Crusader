#pragma once

#include "GameObjectConfig.h"
//#include "WeaponConfig.h"

namespace ratchet
{
	class BulletConfig : public GameObjectConfig
	{
	public:


		BulletConfig(); 

		float m_damage;
		float m_ammo;

		std::string m_ID;

	private:
	};
}


