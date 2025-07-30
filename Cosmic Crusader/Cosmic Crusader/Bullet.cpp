#include "stdafx.h"
#include "Bullet.h"



namespace ratchet
{
	Bullet::Bullet()
	{
	}

	Bullet::Bullet(const BulletConfig& config) : GameObject(config)
	{
		m_damage = config.m_damage;
		m_ammo = config.m_ammo;
		m_bulletSpeed = config.m_BulletSpeed;
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::update()
	{
		auto spritePosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);

		m_sprite.setPosition(spritePosition);
	}

	void Bullet::setBulletPositionCenter(const sf::Vector2f& position, const sf::Vector2f& direction, const bool& facingRight)
	{

		if (auto* rectangleCollider = dynamic_cast<RectAngleCollider*>(m_collider))
		{

			// Collider position and rotation
			sf::Vector2f colliderPos = position;
			float rotationRadians = this->m_collider->getBody()->GetAngle();
			m_collider->getBody()->SetTransform(b2Vec2(colliderPos.x, colliderPos.y), rotationRadians);
			const auto& bodyPos = m_collider->getBody()->GetPosition();
			
			//Sprite position
			sf::Vector2f spritePos;
			spritePos = sf::Vector2f(bodyPos.x, bodyPos.y );
			m_sprite.setPosition(spritePos);

			// Sprite Rotation
			float angleDeg = (std::atan2(direction.y, direction.x) / M_PI) * 180.0f;
			if (direction.x < 0.0f)
			{
				angleDeg = -180.0f + angleDeg;
			}
			m_sprite.setRotation(angleDeg);
		}
		else if (auto* circleCollider = dynamic_cast<CircleCollider*>(m_collider))
		{

			// Collider position and rotation
			sf::Vector2f colliderPos = position;
			float rotationRadians = this->m_collider->getBody()->GetAngle();
			m_collider->getBody()->SetTransform(b2Vec2(colliderPos.x, colliderPos.y), rotationRadians);
			const auto& bodyPos = m_collider->getBody()->GetPosition();

			//Sprite position
			sf::Vector2f spritePos;
			spritePos = sf::Vector2f(bodyPos.x, bodyPos.y);
			m_sprite.setPosition(spritePos);

			// Sprite Rotation
			float angleDeg = (std::atan2(direction.y, direction.x) / M_PI) * 180.0f;
			if (direction.x < 0.0f)
			{
				angleDeg = -180.0f + angleDeg;
			}
			m_sprite.setRotation(angleDeg);
		}
		
	}

	void Bullet::invertCharacterMovingSpriteScale(int direction)
	{
		m_sprite.setScale(m_scale.x * (float)direction, m_scale.y);

		auto bounds = m_sprite.getLocalBounds();  
		m_sprite.setOrigin( bounds.width / 2.f,
			 bounds.height / 2.f);

		sf::Vector2f origin = sf::Vector2f(m_sprite.getOrigin().x, m_sprite.getOrigin().y);



	}
	void Bullet::launchBullet(const sf::Vector2f& direction, const float& speed)
	{
		b2Vec2 velocity(direction.x * speed, direction.y * speed);

		m_collider->getBody()->SetLinearVelocity(velocity);
	}
	void Bullet::render(sf::RenderTarget& target)
	{

		m_collider->drawColliderCenterBased(target);

		GameObject::render(target);

	}
	void Bullet::OnSensorEnter(GameObject* obj)
	{
		short* layerPTr = reinterpret_cast<short*> (obj->m_collider->m_fixtureDef.userData.pointer);

		if (layerPTr && *layerPTr == static_cast<short>(PhysicsLayer::Platforms))
		{
			GameObject::addGameObjectoDestory(this);
		}
	}
	void Bullet::OnSensorExit(GameObject* obj)
	{
	}
}

