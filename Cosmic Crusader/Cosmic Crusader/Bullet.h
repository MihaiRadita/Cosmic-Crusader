#pragma once

#include "GameObject.h"
#include "Timer.h"


namespace ratchet
{
	class Creature;
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
		void launchBomb(const sf::Vector2f& direction, const float& speed);

		void bulletHandleEvents();

		void setOrignAtCenter();

		void render(sf::RenderTarget& target) override;

		void buildExplosionAnimation();
		void playExplosionAnimation(sf::Sprite& sprite);


		// Bullet Collision 
		virtual void OnSensorEnter(GameObject* obj) override;
		virtual void OnSensorExit(GameObject* obj) override;


		void resetForReuse();
		
		float m_damage;
		float m_ammo;
		float m_bulletSpeed;
		float m_bulletLifeLimit;

		float m_bulletDamage = 0.0f;

		bool m_explosionAnimationSwitch;

		bool m_bulletTimerShouldReset = false;

		float m_explosionPositionOffset;

		bool m_explosionHasDamaged = false;

		bool m_explosioTochTarget = false;

		b2Vec2 m_explosionCenter = b2Vec2(0.0f, 0.0f);

		std::unordered_set<Creature*> m_hitCreatures;

		sf::Vector2f m_explosionCirclePos = sf::Vector2f(0.0f, 0.0f);

		float m_explosionAreaSize = 1.5f;


		bool getExplosionAnimationSwitch();


		void PostCosntructFixup() override;

		void drawExplosionArea(sf::Vector2f& position, float& m_radius, sf::RenderTarget& target);

		Timer m_bulletTimer;

		BulletType m_bulletType;
		std::string m_bulletExplosionPath;
		sf::Texture m_bulletBasicTexture;

		std::vector<sf::Texture>m_bulletExplosionAnimation;
		Timer m_explosionAnimationTimer;
		float m_explosionAnimationTimeLimit = 0.05;
		bool m_repeatExplosionAnimation;
		int m_currenExplosionIndex;
		bool m_isExpplosionAnimationTrasition;
		bool m_endExplosionAnimation;
		sf::Sprite m_currenExplosionAnimationSprite;

		bool m_isBulletExploding;

	private:

	};
}

