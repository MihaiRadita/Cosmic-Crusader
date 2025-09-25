#include "stdafx.h"
#include "CircleCollider.h"

#include "game/Player.h"
#include "SelfControlledCreature.h"

namespace ratchet
{
	CircleCollider::CircleCollider(sf::Sprite& sprite, const CircleColliderConfig& config) : ColliderBase(config)
	{
		initVariables(sprite, config);
	}

	void CircleCollider::initVariables(sf::Sprite& sprite, const CircleColliderConfig& config)
	{

		m_bodyDef.type = config.m_bodyDef.type;
		m_bodyDef.fixedRotation = config.m_bodyDef.fixedRotation;

		m_scaleX = 1.0f;
		m_scaleY = 1.0f;

		if (config.m_radius.has_value())
		{
			m_radius = config.m_radius.value();
		}
		else
		{
			m_radius = std::max(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height) / 2.0f;
		}


		if (config.m_origin.has_value())
		{
			m_origin = config.m_origin.value();
		}
		else
		{
			m_origin = b2Vec2(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
		}

		m_bodyDef.position.Set(sprite.getPosition().x, sprite.getPosition().y);
		m_body = s_physicsWorld->CreateBody(&m_bodyDef);

		m_body->SetGravityScale(config.m_gravityScale);
		m_body->SetLinearDamping(config.m_linearDamping);
		m_body->SetAngularDamping(config.m_angularDamping);

		m_userDataName = static_cast<short>(config.m_layer);

		// Circle Shape
		m_shape.m_radius = getGlobalRadius();
		m_shape.m_p.Set(m_origin.x, m_origin.y);
		m_fixtureDef.shape = &m_shape;
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&m_userDataName);
		m_fixtureDef.isSensor = config.m_fixtureDef.isSensor;
		m_body->CreateFixture(&m_fixtureDef);

		if (m_bodyDef.type == b2_staticBody)
		{
#ifdef IS_RATCHET_DEBUG
			b2Vec2 origin = m_body->GetLocalCenter();
			b2Vec2 position = m_body->GetTransform().p;
			float rotation = m_body->GetAngle();
#endif
		}
		else if (m_bodyDef.type == b2_dynamicBody)
		{
#ifdef IS_RATCHET_DEBUG
			b2Vec2 origin = m_body->GetLocalCenter();
			b2Vec2 position = m_body->GetPosition();
			float rotation = m_body->GetAngle();
#endif
		}

	}

	void CircleCollider::drawColliderCenterBased(sf::RenderTarget& target)
	{
		auto colliderOutline = sf::CircleShape(getGlobalRadius());
		colliderOutline.setFillColor(sf::Color::Transparent);
		colliderOutline.setOutlineColor(sf::Color::Green);
		colliderOutline.setOutlineThickness(0.01f);
		colliderOutline.setOrigin(colliderOutline.getRadius(), colliderOutline.getRadius());

		colliderOutline.setPosition(
			getBody()->GetPosition().x,
			getBody()->GetPosition().y);
		colliderOutline.setRotation(getBody()->GetAngle() * (180.f / M_PI));
		target.draw(colliderOutline);
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
	CircleColliderConfig::CircleColliderConfig()
	{
	}
}