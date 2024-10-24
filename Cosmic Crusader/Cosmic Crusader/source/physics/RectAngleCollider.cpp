#include "stdafx.h"
#include "RectAngleCollider.h"

namespace ratchet
{
	void GroundCheck::BeginContact(b2Contact* contact)
	{
	}

	void GroundCheck::EndContact(b2Contact* contact)
	{
	}

	GroundRayCastCallBack::GroundRayCastCallBack(b2Body* ignoredBody)
	{
		m_hit = false;
		m_fraction = 1.0f;

		m_ignoredBody = ignoredBody;
	}


	std::string GroundCheck::getCollisionSide(const b2Vec2& localPoint, const b2AABB& aabb) {

		float epsilon = 0.1f;
		float top = aabb.upperBound.y;
		float bottom = aabb.lowerBound.y;
		float left = aabb.lowerBound.x;
		float right = aabb.upperBound.x;

#ifdef IS_RATCHET_DEBUG
		//std::cout << std::endl;
		//std::cout << "Local point: (" << localPoint.x << ", " << localPoint.y << ")" << std::endl;
		//std::cout << "AABB: top = " << top << ", bottom = " << bottom << ", left = " << left << ", right = " << right << std::endl;
#endif


		if (localPoint.y >= bottom)
			return "bottom";
		if (localPoint.y <= top)
			return "top";
		if (localPoint.x <= left)
			return "left";
		if (localPoint.x >= right)
			return "right";

		return "unknown";
	}


	RectAngleCollider::RectAngleCollider(sf::Sprite& sprite, const RectAngleColliderConfig& config) : ColliderBase(config)
	{
		initVariables(sprite, config);
	}

	void RectAngleCollider::initVariables(sf::Sprite& sprite, const RectAngleColliderConfig& config)
	{
		m_bodyDef.type = config.m_bodyDef.type;
		m_bodyDef.fixedRotation = config.m_bodyDef.fixedRotation;

		m_offset = b2Vec2(20.0f, 0.0f);

		if (!m_contactListener)
		{
			m_contactListener = new GroundCheck();
			s_physicsWorld->SetContactListener(m_contactListener);
		}
		float scaleX = sprite.getScale().x;
		float scaleY = sprite.getScale().y;

		m_colliderOrigin = b2Vec2((sprite.getLocalBounds().width * scaleX) / 2.0, (sprite.getLocalBounds().height * scaleY) / 2.0f);


		m_colliderSpriteScale = b2Vec2(
			sprite.getLocalBounds().width * scaleX,
			sprite.getLocalBounds().height * scaleY
		);


		m_bodyDef.position.Set(sprite.getPosition().x, sprite.getPosition().y);
		m_body = s_physicsWorld->CreateBody(&m_bodyDef);


		//Box Dimensions
		m_boxShape.SetAsBox(m_colliderSpriteScale.x / 2.0f, m_colliderSpriteScale.y / 2.0f, m_colliderOrigin, m_body->GetAngle());


		//Box fixtures properties
		m_fixtureDef.shape = &m_boxShape;

		m_fixtureDef.density = config.m_fixtureDef.density;
		m_fixtureDef.friction = config.m_fixtureDef.friction;
		m_fixtureDef.restitution = config.m_fixtureDef.restitution;

		if (config.m_layer == PhysiscsLayer::Player)
		{
			userDataName = static_cast<short>(config.m_layer);
			m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&userDataName);

		}
		else if (config.m_layer == PhysiscsLayer::Platforms)
		{
			userDataName = static_cast<short>(config.m_layer);
			m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&userDataName);
		}

		m_body->CreateFixture(&m_fixtureDef);

		if (m_bodyDef.type == b2_staticBody)
		{
#ifdef IS_RATCHET_DEBUG
			//std::cout << std::endl;
			//std::cout << "Static Sprite position is " << sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
			//std::cout << "Static Sprite scale is " << sprite.getScale().x << " , " << sprite.getScale().y << std::endl;
#endif

			b2Vec2 origin = m_body->GetLocalCenter();
			b2Vec2 position = m_body->GetTransform().p;
			float rotaion = m_body->GetAngle();

#ifdef IS_RATCHET_DEBUG
			//std::cout << "Static Collider origin " << origin.x << " , " << origin.y << std::endl;
			//std::cout << "Static Collider position " << position.x << " , " << position.y << std::endl;
			//std::cout << "Static Collider roatation " << rotaion << std::endl;
			//std::cout << std::endl;
#endif
		}
		else if (m_bodyDef.type == b2_dynamicBody)
		{
#ifdef IS_RATCHET_DEBUG
			//std::cout << std::endl;
			//std::cout << "Dynamic Sprite position is " << sprite.getPosition().x << " , " << sprite.getPosition().y << std::endl;
			//std::cout << "Dynamic Sprite scale is " << sprite.getScale().x << " , " << sprite.getScale().y << std::endl;
#endif

			b2Vec2 origin = m_body->GetLocalCenter();
			b2Vec2 position = m_body->GetPosition();
			float rotaion = m_body->GetAngle();

#ifdef IS_RATCHET_DEBUG
			//std::cout << "Dynamic Collider origin " << origin.x << " , " << origin.y << std::endl;
			//std::cout << "Dynamic Collider position " << position.x << " , " << position.y << std::endl;
			//std::cout << "Dynamic Collider roatation " << rotaion << std::endl;
			//std::cout << std::endl;
#endif
		}
	}

	RectAngleCollider::~RectAngleCollider()
	{
		if (s_physicsWorld)
		{
			if (m_body)
			{
				s_physicsWorld->DestroyBody(m_body);
				m_body = nullptr;
			}
			delete m_contactListener;
		}
	}


	b2BodyDef* RectAngleCollider::getBodyDef()
	{
		return &m_bodyDef;
	}

	b2PolygonShape* RectAngleCollider::getColliderShape()
	{
		return &m_boxShape;
	}

	b2FixtureDef* RectAngleCollider::getFixtureDef()
	{
		return &m_fixtureDef;
	}

	b2Vec2 RectAngleCollider::getOffset()
	{
		return m_offset;
	}

	b2Vec2* RectAngleCollider::getColliderScale()
	{
		return &m_colliderSpriteScale;
	}

	b2Vec2 RectAngleCollider::getColliderPosition()
	{
		return m_body->GetTransform().p;
	}

#ifdef IS_RATCHET_DEBUG
	void RectAngleCollider::printBodyPositionRotation()
	{
		//std::cout << getColliderPosition().x << " x axis " << getColliderPosition().y << " y axis " << std::endl;
		//std::cout << m_body->GetAngle() << " degrees " << std::endl;
	}

	void RectAngleCollider::printSpriteColliderPosition(sf::Sprite& sprite, int bodyState)
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

	void RectAngleCollider::debugRender(sf::RenderTarget& target)
	{
		auto* fixture = m_body->GetFixtureList();
		while (fixture)
		{
			b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
			int32 vertexCount = poly->m_count;
			for (int32 i = 0; i < vertexCount; ++i)
			{
				//they are polygen's vertices, you can use these to get the height / width
				b2Vec2 vertex = b2Mul(m_body->GetTransform(), poly->m_vertices[i]);

				sf::CircleShape circle(0.01f);
				circle.setFillColor(sf::Color::Green);
				circle.setPosition(vertex.x, vertex.y);
				target.draw(circle);
			}
			fixture = fixture->GetNext();
		}

		// DRAW COLLIDER BEGIN AND END
		auto outline = sf::RectangleShape(
			sf::Vector2f(
				getColliderScale()->x,
				getColliderScale()->y
			)
		);

		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Blue);
		outline.setOutlineThickness(0.01f);
		outline.setPosition(
			getColliderPosition().x,
			getColliderPosition().y
		);

		auto bodyPosition = sf::CircleShape(0.01f);
		bodyPosition.setFillColor(sf::Color::Yellow);
		bodyPosition.setPosition(m_body->GetPosition().x, m_body->GetPosition().y);

		//sf::Vertex line[] = { sf::Vertex(sf::Vector2f(500.f, 10.f), sf::Color::Green), sf::Vertex(sf::Vector2f(700.f, 10.f), sf::Color::Green) };

		if (m_body->GetType() == b2BodyType::b2_dynamicBody)
		{
			b2Vec2 startPointLeft = b2Vec2{};
			b2Vec2 endPointLeft = b2Vec2{};
			getLeftPointsForRaycast(startPointLeft.x, startPointLeft.y, endPointLeft.x, endPointLeft.y);

			sf::Vertex rayCastLeft[] = { sf::Vertex(sf::Vector2f(startPointLeft.x, startPointLeft.y), sf::Color::Green), sf::Vertex(sf::Vector2f(startPointLeft.x, endPointLeft.y), sf::Color::Green) };

			auto pointLeftStart = sf::CircleShape(0.01f);
			pointLeftStart.setFillColor(sf::Color::Red);
			pointLeftStart.setPosition(startPointLeft.x, startPointLeft.y);

			b2Vec2 startPointRight = b2Vec2{};
			b2Vec2 endPointRight = b2Vec2{};
			getRightPointsForRaycast(startPointRight.x, startPointRight.y, endPointRight.x, endPointRight.y);

			sf::Vertex rayCastRight[] = { sf::Vertex(sf::Vector2f(startPointRight.x, startPointRight.y), sf::Color::Green), sf::Vertex(sf::Vector2f(startPointRight.x, endPointRight.y), sf::Color::Green) };

			auto pointRightStart = sf::CircleShape(0.01f);
			pointRightStart.setFillColor(sf::Color::Red);
			pointRightStart.setPosition(startPointRight.x, startPointRight.y);

			b2Vec2 startPointMiddle = b2Vec2{};
			b2Vec2 endPointMiddle = b2Vec2{};
			getMiddlePointsForRaycast(startPointMiddle.x, startPointMiddle.y, endPointMiddle.x, endPointMiddle.y);

			sf::Vertex rayCastMiddle[] = { sf::Vertex(sf::Vector2f(startPointMiddle.x, startPointMiddle.y), sf::Color::Green), sf::Vertex(sf::Vector2f(startPointMiddle.x, endPointMiddle.y), sf::Color::Green) };

			auto pointMiddleStart = sf::CircleShape(0.01f);
			pointMiddleStart.setFillColor(sf::Color::Red);
			pointMiddleStart.setPosition(startPointRight.x, startPointRight.y);

			target.draw(rayCastLeft, 2, sf::Lines);
			target.draw(rayCastRight, 2, sf::Lines);
			target.draw(rayCastMiddle, 2, sf::Lines);
			target.draw(pointLeftStart);
			target.draw(pointRightStart);
			target.draw(pointMiddleStart);
		}

		target.draw(outline);
		target.draw(bodyPosition);
	}
#endif

	void RectAngleCollider::getLeftPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
	{
		ColliderBase::getLeftPointsForRaycast(xStart, yStart, xEnd, yEnd);

		b2Vec2 playerPosition = m_body->GetPosition();

		xStart = playerPosition.x;
		yStart = playerPosition.y + (m_colliderSpriteScale.y / 2.f);

		xEnd = xStart;
		yEnd = yEnd + m_colliderSpriteScale.y * 1.5f;
	}

	void RectAngleCollider::getMiddlePointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
	{
		ColliderBase::getMiddlePointsForRaycast(xStart, yStart, xEnd, yEnd);

		b2Vec2 playerPosition = m_body->GetPosition();

		xStart = playerPosition.x + (m_colliderSpriteScale.x / 2.f);
		yStart = playerPosition.y + (m_colliderSpriteScale.y / 2.f);

		xEnd = xStart;
		yEnd = yEnd + m_colliderSpriteScale.y * 1.5f;
	}

	void RectAngleCollider::getRightPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
	{
		ColliderBase::getRightPointsForRaycast(xStart, yStart, xEnd, yEnd);

		b2Vec2 playerPosition = m_body->GetPosition();

		xStart = playerPosition.x + m_colliderSpriteScale.x;
		yStart = playerPosition.y + (m_colliderSpriteScale.y / 2.f);

		xEnd = xStart;
		yEnd = yEnd + m_colliderSpriteScale.y * 1.5f;
	}

	bool RectAngleCollider::performGroundRayCast(sf::Sprite& sprite)
	{
		float playerWidth = sprite.getGlobalBounds().width;
		float playerHeight = sprite.getGlobalBounds().height;
		b2Vec2 playerPosition = m_body->GetPosition();

		b2Vec2 startPointLeft = b2Vec2{};
		b2Vec2 endPointLeft = b2Vec2{};
		getLeftPointsForRaycast(startPointLeft.x, startPointLeft.y, endPointLeft.x, endPointLeft.y);

		b2Vec2 startPointMiddle = b2Vec2{};
		b2Vec2 endPointMiddle = b2Vec2{};
		getMiddlePointsForRaycast(startPointMiddle.x, startPointMiddle.y, endPointMiddle.x, endPointMiddle.y);

		b2Vec2 startPointRight = b2Vec2{};
		b2Vec2 endPointRight = b2Vec2{};
		getRightPointsForRaycast(startPointRight.x, startPointRight.y, endPointRight.x, endPointRight.y);

		GroundRayCastCallBack callbackLeft(m_body);
		s_physicsWorld->RayCast(&callbackLeft, startPointLeft, endPointLeft);

		GroundRayCastCallBack callbackRight(m_body);
		s_physicsWorld->RayCast(&callbackRight, startPointRight, endPointRight);

		GroundRayCastCallBack callbackMiddle(m_body);
		s_physicsWorld->RayCast(&callbackMiddle, startPointMiddle, endPointMiddle);

		if ((callbackLeft.m_fraction <= 2.0f || callbackRight.m_fraction <= 2.0f || callbackMiddle.m_fraction <= 2.0f) && (callbackLeft.m_hit || callbackRight.m_hit || callbackMiddle.m_hit))
		{
#ifdef IS_RATCHET_DEBUG
			//std::cout << "Victory " << std::endl;
#endif
			return true;
		}

#ifdef IS_RATCHET_DEBUG
		//std::cout << "HIT : " << callbackLeft.m_hit;
#endif
		return false;
	}

	GroundCheck* RectAngleCollider::m_contactListener;
	RectAngleColliderConfig::RectAngleColliderConfig()
	{
	}
}