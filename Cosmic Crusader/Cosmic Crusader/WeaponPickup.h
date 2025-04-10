#pragma once

#include "GameObject.h"
#include "Creature.h"
#include "Weapon.h"
#include "game/Player.h"

namespace ratchet
{
	class WeaponPickup : public GameObject
	{
	public:
		void pickUp(Creature* creatureThatPickedUpTheWeapon);
		WeaponPickup(const WeaponConfig& config);
		~WeaponPickup() override;

		bool m_isPickup = false;

		Weapon::TYPE m_weaponType;
		std::optional<WeaponConfig> m_weaponConfig;

		void OnCollisionEnter(GameObject* obj) override;
		void OnCollisionExit(GameObject* obj) override;
		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;
	};

}


