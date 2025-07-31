#pragma once

#include "GameObject.h"



namespace ratchet
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		Bullet(const BulletConfig& config);
		~Bullet();

		void update() override;
		void setBulletPositionCenter(const sf::Vector2f& poisition, const sf::Vector2f& direction, const bool& facingRight);
		void invertCharacterMovingSpriteScale(int direction) override;

		void launchBullet(const sf::Vector2f& direction, const float& speed);

		void render(sf::RenderTarget& target) override;


		// Bullet Collision 
		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;
		
		float m_damage;
		float m_ammo;
		float m_bulletSpeed;
		float m_bulletLifeLimit;

		sf::Clock m_bulletTimer;

	private:

	};
}

