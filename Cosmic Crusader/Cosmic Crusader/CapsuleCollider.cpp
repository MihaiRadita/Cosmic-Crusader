#include "stdafx.h"
#include "CapsuleCollider.h"


namespace ratchet
{

	CapsuleCollider::CapsuleCollider(sf::Sprite& sprite, const CapsuleColliderConfig& config) : ColliderBase(config)
	{
		initVariables(sprite, config);
	}

	void CapsuleCollider::initVariables(sf::Sprite& sprite, const CapsuleColliderConfig& config)
	{
		m_bodyDef.type = config.m_bodyDef.type;
		m_bodyDef.fixedRotation = config.m_bodyDef.fixedRotation;
		
		m_scaleX = 1.0f;
		m_scaleY = 1.0f;

		if (config.m_radius.has_value() && config.m_height.has_value())
		{
			m_height = config.m_height.value();
			m_radius = config.m_radius.value();
		}
		else
		{
			m_height = sprite.getGlobalBounds().height;
			m_radius = sprite.getGlobalBounds().width / 2.0f;
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

		userDataName = static_cast<short>(config.m_layer);

		// Bottom Circle
		m_bottomCircleShape.m_radius = getGlobalRadius();
		m_bottomCircleShape.m_p.Set(m_origin.x, m_origin.y + (getGlobalHeight() / 2.0f) - getGlobalRadius());
		m_fixtureDef.shape = &m_bottomCircleShape;
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&userDataName);
		m_body->CreateFixture(&m_fixtureDef);
		// Top Circle
		m_topCircleShape.m_radius = getGlobalRadius();
		m_topCircleShape.m_p.Set(m_origin.x, m_origin.y - (getGlobalHeight() / 2.0f) + getGlobalRadius());
		m_fixtureDef.shape = &m_topCircleShape;
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&userDataName);
		m_body->CreateFixture(&m_fixtureDef);
		// Center Box
		const auto centerBoxHeight = std::abs(m_bottomCircleShape.m_p.y - m_topCircleShape.m_p.y);
		const auto centerBoxHalfHeight = centerBoxHeight / 2.0f;
		m_boxShape.SetAsBox(getGlobalRadius(), centerBoxHalfHeight, m_origin, m_body->GetAngle());
		m_fixtureDef.shape = &m_boxShape;
		m_fixtureDef.density = config.m_fixtureDef.density;
		m_fixtureDef.friction = config.m_fixtureDef.friction;
		m_fixtureDef.restitution = config.m_fixtureDef.restitution;
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&userDataName);
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

	CapsuleCollider::~CapsuleCollider()
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

	b2BodyDef* CapsuleCollider::getBodyDef()
	{
		return &m_bodyDef;
	}

	b2PolygonShape* CapsuleCollider::getColliderBoxShape()
	{
		return &m_boxShape;
	}

	b2CircleShape* CapsuleCollider::getBottomColliderCircleShape()
	{
		return &m_bottomCircleShape;
	}

	b2CircleShape* CapsuleCollider::getTopColliderCircleShape()
	{
		return &m_topCircleShape;
	}

	b2FixtureDef* CapsuleCollider::getFixtureDef()
	{
		return &m_fixtureDef;
	}

	b2Vec2 CapsuleCollider::getOffset()
	{
		return m_offset;
	}

	b2Vec2 CapsuleCollider::getColliderPosition()
	{
		return m_body->GetTransform().p;
	}

	float CapsuleCollider::getTopCircleRadius()
	{
		return m_topCircleShape.m_radius;
	}

	float CapsuleCollider::getBottomCircleRadius()
	{
		return m_bottomCircleShape.m_radius;
	}

	CapsuleColliderConfig::CapsuleColliderConfig()
	{
	}


#ifdef IS_RATCHET_DEBUG
	void CapsuleCollider::printBodyPositionRotation()
	{
		//std::cout << getColliderPosition().x << " x axis " << getColliderPosition().y << " y axis " << std::endl;
		//std::cout << m_body->GetAngle() << " degrees " << std::endl;
	}

	void CapsuleCollider::printSpriteColliderPosition(sf::Sprite& sprite, int bodyState)
	{
		//if (bodyState == STATIC)
		//{
		//	std::cout << "Static position is " << m_body->GetTransform().p.x << " , " << m_body->GetTransform().p.y << " VS Sprite position " <<
		//		sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
		//}
		//else if (bodyState == DYNAMIC)
		//{
		//	std::cout << "Dynamic position is " << m_body->GetTransform().p.x << " , " << m_body->GetTransform().p.y << " VS Sprite position " <<
		//		sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
		//}
	}

	void CapsuleCollider::debugRender(sf::RenderTarget& target)
	{
		const auto worldOrigin = getColliderPosition() + m_origin;

		// Origin
		{
			auto circleShape = sf::CircleShape(getGlobalRadius() * 0.7f);
			circleShape.setFillColor(sf::Color::Magenta);
			const auto position = worldOrigin;
			circleShape.setPosition(position.x - circleShape.getRadius(), position.y - circleShape.getRadius());
			target.draw(circleShape);
		}

		// DRAW COLLIDER BEGIN AND END
		// Center Box
		{
			auto rectangleShape = sf::RectangleShape();
			rectangleShape.setFillColor(sf::Color::Transparent);
			rectangleShape.setOutlineColor(sf::Color::Green);
			rectangleShape.setOutlineThickness(0.03f);

			float maxWidth = std::numeric_limits<float>().min();
			float maxHeight = std::numeric_limits<float>().min();
			for (int i = 0; i < 4; i++)
			{
				if (i > 0)
				{
					const auto width = std::abs(m_boxShape.m_vertices[i].x - m_boxShape.m_vertices[i - 1].x);
					if (width > maxWidth)
					{
						maxWidth = width;
					}

					const auto height = std::abs(m_boxShape.m_vertices[i].y - m_boxShape.m_vertices[i - 1].y);
					if (height > maxHeight)
					{
						maxHeight = height;
					}
				}
			}
			rectangleShape.setSize(sf::Vector2f(maxWidth, maxHeight));
			rectangleShape.setPosition(worldOrigin.x - maxWidth / 2.0f, worldOrigin.y - maxHeight / 2.0f);
			target.draw(rectangleShape);
		}
		// Bottom Circle
		{
			auto circleShape = sf::CircleShape(m_bottomCircleShape.m_radius);
			circleShape.setFillColor(sf::Color::Transparent);
			circleShape.setOutlineColor(sf::Color::Green);
			circleShape.setOutlineThickness(0.03f);
			const auto position = getColliderPosition() + m_bottomCircleShape.m_p;
			circleShape.setPosition(position.x - circleShape.getRadius(), position.y - circleShape.getRadius());
			target.draw(circleShape);
		}
		// Top Circle
		{
			auto circleShape = sf::CircleShape(m_topCircleShape.m_radius);
			circleShape.setFillColor(sf::Color::Transparent);
			circleShape.setOutlineColor(sf::Color::Green);
			circleShape.setOutlineThickness(0.03f);
			const auto position = getColliderPosition() + m_topCircleShape.m_p;
			circleShape.setPosition(position.x - circleShape.getRadius(), position.y - circleShape.getRadius());
			target.draw(circleShape);
		}
		// Body
		{
			auto bodyCircle = sf::CircleShape(0.01f);
			bodyCircle.setFillColor(sf::Color::Yellow);
			bodyCircle.setPosition(worldOrigin.x, worldOrigin.y);
			target.draw(bodyCircle);
		}

		b2Vec2 startPointMiddle = b2Vec2{};
		b2Vec2 endPointMiddle = b2Vec2{};
		getMiddlePointsForRaycast(startPointMiddle.x, startPointMiddle.y, endPointMiddle.x, endPointMiddle.y);

		sf::Vertex rayCastMiddle[] = { sf::Vertex(sf::Vector2f(startPointMiddle.x, startPointMiddle.y), sf::Color::Green), sf::Vertex(sf::Vector2f(startPointMiddle.x, endPointMiddle.y), sf::Color::Green) };
		target.draw(rayCastMiddle, 2, sf::Lines);
	}
#endif
		void CapsuleCollider::getMiddlePointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
		{
			ColliderBase::getMiddlePointsForRaycast(xStart, yStart, xEnd, yEnd);

			b2Vec2 playerPosition = m_body->GetPosition();

			//float distanceCeneteX = std::abs(playerPosition.x - m_bottomCircleShape.m_p.x);
			xStart =  playerPosition.x +  m_bottomCircleShape.m_p.x;



			yStart = playerPosition.y + m_bottomCircleShape.m_p.y;

			xEnd = xStart;
			yEnd = yStart + m_bottomCircleShape.m_radius + 0.02;
		}
		bool CapsuleCollider::performGroundRayCast(sf::Sprite& sprite)
		{
			b2Vec2 startPointMiddle = b2Vec2{};
			b2Vec2 endPointMiddle = b2Vec2{};
			getMiddlePointsForRaycast(startPointMiddle.x, startPointMiddle.y, endPointMiddle.x, endPointMiddle.y);

			GroundRayCastCallBack callbackMiddle(m_body);
			s_physicsWorld->RayCast(&callbackMiddle, startPointMiddle, endPointMiddle);

			if (callbackMiddle.m_fraction <= 1.0f && callbackMiddle.m_hit)
			{
				return true;
			}

	#ifdef IS_RATCHET_DEBUG
			//std::cout << "HIT : " << callbackLeft.m_hit;
	#endif
			return false;
		}
}

