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
		bool m_IsWeaponAccessible = false;

		int m_weaponId;

		float m_weaponDamage = 0.0f;

		Weapon::TYPE m_weaponType;
		std::optional<WeaponConfig> m_weaponConfig;

		sf::Vector2f m_StartPointShootingOffset;

		sf::Vector2f m_shootingOffsetAngle0;
		sf::Vector2f m_shootingOffsetAngle45;
		sf::Vector2f m_shootingOffsetAngle90;
		sf::Vector2f m_shootingOffsetAngleMinus45;


		sf::SoundBuffer m_weaponSoundBuffer;
		sf::Sound m_weaponSound;

		std::string m_weaponSoundPath;
		bool m_weaponSoundLoop;
		float m_weaponSoundVolume;

		void PostCosntructFixup() override;
		void Start() override;


		void serialise(nlohmann::json& jsonFile) override;

		std::string m_weaponPickupID;

		void OnCollisionEnter(GameObject* obj) override;
		void OnCollisionExit(GameObject* obj) override;
		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;
	};

}


