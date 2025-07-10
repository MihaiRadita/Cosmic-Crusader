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
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::update()
	{

	}



	void Bullet::setBulletPositionCenter(sf::Vector2f& poisition, int yDirection)
	{
		float boundeHeight = m_sprite.getGlobalBounds().height;
		float hlfPosiiton = m_sprite.getGlobalBounds().top + (boundeHeight / 2.0f) * yDirection;
		poisition.y = hlfPosiiton;

		if (this->m_collider)
		{
			b2Vec2	colliderPosition = b2Vec2(poisition.x, poisition.y);
			float rotationRadians = this->m_collider->getBody()->GetAngle();

			this->m_collider->getBody()->SetTransform(colliderPosition, rotationRadians);
		}

		auto objectPosition = sf::Vector2f(this->m_collider->getBody()->GetPosition().x, this->m_collider->getBody()->GetPosition().y);
		this->setPosition(objectPosition);
	}
	void Bullet::invertCharacterMovingSpriteScale(int direction)
	{
		m_sprite.setScale(m_scale.x * (float)direction, m_scale.y);
		if (direction < 0)
		{
			m_sprite.setOrigin(getBounds().width / m_scale.x, 0.f);
		}
		else
		{
			m_sprite.setOrigin(0.f, 0.f);
		}
	}
	void Bullet::render(sf::RenderTarget& target)
	{

		auto spriteOutline = sf::RectangleShape(sf::Vector2f(
			m_sprite.getGlobalBounds().width,
			m_sprite.getGlobalBounds().height)
		);
		spriteOutline.setFillColor(sf::Color::Transparent);
		spriteOutline.setOutlineColor(sf::Color::Red);
		spriteOutline.setOutlineThickness(0.01f);
		spriteOutline.setPosition(
			m_sprite.getPosition().x,
			m_sprite.getPosition().y);
		target.draw(spriteOutline);
		
		if (auto* bulletCollder = dynamic_cast<RectAngleCollider*>(m_collider))
		{
			/*auto spriteOutline = sf::RectangleShape(sf::Vector2f(
				bulletCollder->getGlobalWidth(),
				bulletCollder->getGlobalHeight())
			);
			spriteOutline.setFillColor(sf::Color::Transparent);
			spriteOutline.setOutlineColor(sf::Color::Green);
			spriteOutline.setOutlineThickness(0.01f);
			spriteOutline.setPosition(
				bulletCollder->getBody()->GetPosition().x,
				bulletCollder->getBody()->GetPosition().y);
			target.draw(spriteOutline);*/

		}
		/*auto spriteCollderPos = sf::CircleShape(0.01f);
		spriteCollderPos.setFillColor(sf::Color::Green);
		spriteCollderPos.setOutlineColor(sf::Color::Green);
		spriteCollderPos.setOutlineThickness(0.01f);
		spriteCollderPos.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
		target.draw(spriteCollderPos);*/


		auto spriteOriginWorldPos = m_sprite.getTransform().transformPoint(m_sprite.getOrigin());
		sf::CircleShape spriteCollderPos2(0.01f);
		spriteCollderPos2.setFillColor(sf::Color::White);
		spriteCollderPos2.setOutlineColor(sf::Color::White);
		spriteCollderPos2.setOutlineThickness(0.01f);
		spriteCollderPos2.setPosition(spriteOriginWorldPos);
		target.draw(spriteCollderPos2);


		GameObject::render(target);
	}
}

