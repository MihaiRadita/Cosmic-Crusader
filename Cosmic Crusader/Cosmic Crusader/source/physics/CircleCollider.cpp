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
		m_isColliderSetDestroy = false;
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

		if (m_massValue != 0.0f)
		{
			m_massData.mass = m_massValue;

			m_body->SetMassData(&m_massData);
		}


		
		m_bodyDef.position.Set(sprite.getPosition().x, sprite.getPosition().y);
		m_body = s_physicsWorld->CreateBody(&m_bodyDef);

		m_body->SetGravityScale(config.m_gravityScale);
		m_body->SetLinearDamping(config.m_linearDamping);
		m_body->SetAngularDamping(config.m_angularDamping);

		m_userDataName = static_cast<short>(config.m_layer);

		// Circle Shape
		m_circleShape.m_radius = getGlobalRadius();
		m_circleShape.m_p.Set(m_origin.x, m_origin.y);
		m_fixtureDef.shape = &m_circleShape;
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&m_userDataName);
		m_fixtureDef.isSensor = config.m_fixtureDef.isSensor;

		m_fixtureDef.density = 1.f;
		m_fixtureDef.friction = config.m_fixtureDef.friction;
		m_fixtureDef.restitution = config.m_fixtureDef.restitution;

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

	void CircleCollider::printBodyPositionRotation()
	{
		TRACE_CHANNEL("COLLISION",getCircleColliderPosition().x, " x axis ",getCircleColliderPosition().y, " y axis ");
		TRACE_CHANNEL("COLLISION", m_body->GetAngle(), " degrees ");
	}

	void CircleCollider::printSpriteColliderPosition(sf::Sprite& sprite, int bodyState)
	{
		if (!m_body)
		{
			return;
		}

		if (bodyState == STATIC)
		{
			TRACE_CHANNEL("COLLISION", "Static position is ", m_body->GetTransform().p.x, " , ", m_body->GetTransform().p.y, " VS Sprite position ",
				sprite.getPosition().x, " , ", sprite.getPosition().y);
		}
		else if (bodyState == DYNAMIC)
		{
			TRACE_CHANNEL("COLLISION", "Dynamic position is ", m_body->GetTransform().p.x, " , ", m_body->GetTransform().p.y, " VS Sprite position ",
				sprite.getPosition().x, " , ", sprite.getPosition().y);
		}
	}

	void CircleCollider::debugRender(sf::RenderTarget& target)
	{
		if (!m_body)
			return;

		b2Vec2 bodyPos = m_body->GetPosition();

		b2Vec2 offset = m_circleShape.m_p;

		float radius = m_circleShape.m_radius;
		float x = bodyPos.x + offset.x;
		float y = bodyPos.y + offset.y;

		sf::CircleShape circle(radius);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Green);
		circle.setOutlineThickness(0.02f);

		circle.setOrigin(radius, radius);

		circle.setPosition(x, y);

		target.draw(circle);


		if (auto* enemy = dynamic_cast<SelfControlledCreature*>(m_obj))
		{
			auto* targetPlayer = enemy->m_target;

			if (auto* player = dynamic_cast<Player*>(targetPlayer))
			{
				if (enemy->m_isTargetDetected)
				{
					sf::Vector2f startPoint = sf::Vector2f{};
					sf::Vector2f endPoint = sf::Vector2f{};

					startPoint = enemy->getPosition();
					endPoint = player->getPosition();

					sf::Vertex rayCast[] = { sf::Vertex(sf::Vector2f(startPoint.x, startPoint.y), sf::Color::Green), sf::Vertex(sf::Vector2f(endPoint.x, endPoint.y), sf::Color::Green) };
					target.draw(rayCast, 2, sf::Lines);
				}

				
			}
		}

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


	b2Vec2 CircleCollider::getCircleColliderPosition()
	{
		if (!m_body)
		{
			return b2Vec2_zero;
		}
		return m_circleShape.m_p;
	}

	void CircleCollider::setColliderPosition(sf::Sprite& sprite)
	{
		m_body->SetTransform(b2Vec2((sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.f)) / sc_metersScale,
			(sprite.getPosition().y + (sprite.getGlobalBounds().height / 2.f)) / sc_metersScale), m_body->GetAngle());
	}

	bool CircleCollider::performFollowTargetRayCast(const sf::Vector2f& charaterPosition, const sf::Vector2f& targetPosition)
	{
		if (!m_body || !s_physicsWorld)
		{
			return false;
		}

		b2Vec2 startPoint(charaterPosition.x, charaterPosition.y);
		b2Vec2 endPoint(targetPosition.x, targetPosition.y);


		CheckFollowTargetRaycastCallBack followTarget(m_body);

		s_physicsWorld->RayCast(&followTarget, startPoint, endPoint);

		if (SelfControlledCreature* self = dynamic_cast<SelfControlledCreature*>(m_obj))
		{
			if (followTarget.m_hit)
			{
				return true;
			}
		}

		return false;
	}

	CheckFollowTargetRaycastCallBack::CheckFollowTargetRaycastCallBack(b2Body* ignoredBody)
	{
		m_hit = false;
		m_fraction = 1.0f;

		m_ignoredBody = ignoredBody;
	}

	void CircleCollider::getCheckFollowTargetRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction)
	{
		if (m_body)
		{
			return;
		}

		xStart = m_origin.x;
		yStart = m_origin.y;


	}

	CircleColliderConfig::CircleColliderConfig()
	{
	}
}