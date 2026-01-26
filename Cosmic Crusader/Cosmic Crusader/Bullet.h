#pragma once

#include "GameObject.h"
#include "Timer.h"


namespace ratchet
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		Bullet(const BulletConfig& config);
		~Bullet();

		virtual void setActive(bool active) override;

		void update() override;
		void setBulletPositionCenter(const sf::Vector2f& poisition, const sf::Vector2f& direction, const bool& facingRight);
		void invertCharacterMovingSpriteScale(int direction) override;

		void launchBullet(const sf::Vector2f& direction, const float& speed);

		void bulletHandleEvents();

		void setOrignAtCenter();

		void render(sf::RenderTarget& target) override;


		// Bullet Collision 
		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;
		
		float m_damage;
		float m_ammo;
		float m_bulletSpeed;
		float m_bulletLifeLimit;

		bool m_bulletTimerShouldReset = false;


		Timer m_bulletTimer;

	private:

	};
}

