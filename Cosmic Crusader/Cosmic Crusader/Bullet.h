#pragma once

#include "GameObject.h"
#include "Weapon.h"


namespace ratchet
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		Bullet(const Weapon& originWeapon);
		~Bullet();
		
	private:

	};
}

