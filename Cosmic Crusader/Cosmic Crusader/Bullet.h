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
		void setBulletPositionCenter(sf::Vector2f& poisition, int yDirection);
		void invertCharacterMovingSpriteScale(int direction) override;

		void render(sf::RenderTarget& target) override;
		
		float m_damage;
		float m_ammo;

	private:

	};
}

