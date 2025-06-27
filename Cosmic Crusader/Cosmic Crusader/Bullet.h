#pragma once

#include "GameObject.h"
#include "Weapon.h"


namespace ratchet
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		Bullet(const BulletConfig& config);
		~Bullet();
		
		float m_damage;
		float m_ammo;

	private:

	};
}

