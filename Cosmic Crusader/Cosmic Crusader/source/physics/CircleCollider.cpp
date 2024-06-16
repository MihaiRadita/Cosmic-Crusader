#include "stdafx.h"
#include "CircleCollider.h"

namespace ratchet
{
	CircleCollider::CircleCollider(sf::Sprite& sprite, float radius)
	{
		initVariables(sprite, radius);
	}

	void CircleCollider::initVariables(sf::Sprite& sprite, float radius)
	{
		m_radius = radius;

		m_bodyDef.type = b2_dynamicBody;
		m_bodyDef.position.Set((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / sc_metersScale, (sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / sc_metersScale);
		m_body = s_physicsWorld->CreateBody(&m_bodyDef);

		//circleShape.m_p.Set((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / metersScale, (sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / metersScale);
		m_circleShape.m_radius = m_radius / sc_metersScale;

		m_fixtureDef.shape = &m_circleShape;
		m_fixtureDef.density = 1.0f;
		m_fixtureDef.friction = 0.3f;
		m_fixtureDef.restitution = 0.5f;
		m_body->CreateFixture(&m_fixtureDef);
	}

	CircleCollider::~CircleCollider()
	{
		if (s_physicsWorld)
		{
			if (m_body)
			{
				s_physicsWorld->DestroyBody(m_body);
				m_body = nullptr;
			}
		}
	}

	b2BodyDef CircleCollider::getBodyDef()
	{
		return m_bodyDef;
	}

	b2Body* CircleCollider::getBody()
	{
		return m_body;
	}

	b2CircleShape CircleCollider::getColliderShape()
	{
		return m_circleShape;
	}

	b2FixtureDef CircleCollider::getFixtureDef()
	{
		return m_fixtureDef;;
	}


	void CircleCollider::setColliderPosition(sf::Sprite& sprite)
	{
		m_body->SetTransform(b2Vec2((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / sc_metersScale,
			(sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / sc_metersScale), m_body->GetAngle());
	}
}