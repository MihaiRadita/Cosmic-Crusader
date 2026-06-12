#include "stdafx.h"
#include "RectAngleCollider.h"

#include "game/Player.h"
#include "SelfControlledCreature.h"


namespace ratchet
{

	GroundRayCastCallBack::GroundRayCastCallBack(b2Body* ignoredBody)
	{
		m_hit = false;
		m_fraction = 1.0f;

		m_ignoredBody = ignoredBody;

	
	}

	JumpOverPlatformsRayCastCallBack::JumpOverPlatformsRayCastCallBack(b2Body* ingnoreddBoy)
	{
		m_hit = false;
		m_fraction = 1.0f;

		m_ignoredBody = ingnoreddBoy;
	}

	CheckFallingRiskRaycastCallBack::CheckFallingRiskRaycastCallBack(b2Body* ingnoreddBoy)
	{
		m_hit = false;
		m_fraction = 1.0f;

		m_ignoredBody = ingnoreddBoy;
	}

	RectAngleCollider::RectAngleCollider(sf::Sprite& sprite, const RectAngleColliderConfig& config) : ColliderBase(config)
	{
		initVariables(sprite, config);
	}

	void RectAngleCollider::initVariables(sf::Sprite& sprite, const RectAngleColliderConfig& config)
	{

		m_isColliderSetDestroy = false;

		m_colliderOffsetX = config.m_colliderOffsetX;
		m_colliderOffsetY = config.m_colliderOffsetY;

		m_bodyDef.type = config.m_bodyDef.type;
		m_bodyDef.fixedRotation = config.m_bodyDef.fixedRotation;

		m_offset = b2Vec2(20.0f, 0.0f);
		
		m_scaleX = sprite.getScale().x;
		m_scaleY = sprite.getScale().y;

		m_width = sprite.getLocalBounds().width;
		m_height = sprite.getLocalBounds().height;

		if (config.m_width && config.m_height &&
			config.m_width.value() > 0.0f &&
			config.m_height.value() > 0.0f)
		{
			m_width = *config.m_width;
			m_height = *config.m_height;
		}

		if (config.m_origin.has_value())
		{
			m_origin = config.m_origin.value();
		}
		else
		{
			m_origin = b2Vec2(getGlobalWidth() / 2.0f, getGlobalHeight() / 2.0f);
		}

		m_bodyDef.position.Set(sprite.getPosition().x + m_colliderOffsetX, sprite.getPosition().y + m_colliderOffsetY);

		if (!s_physicsWorld)
		{
			m_body = nullptr;
			return;
		}

		if (m_colliderOffsetX != 0)
		{
			m_colliderOffsetX = config.m_colliderOffsetX;
		}

		if (m_colliderOffsetY != 0)
		{
			m_colliderOffsetY = config.m_colliderOffsetY;
		}

		m_bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
		m_body = s_physicsWorld->CreateBody(&m_bodyDef);


		m_body->SetGravityScale(config.m_gravityScale);
		m_body->SetLinearDamping(config.m_linearDamping);
		m_body->SetAngularDamping(config.m_angularDamping);

		//Box Dimensions
		m_boxShape.SetAsBox(getGlobalWidth() / 2.0f, getGlobalHeight() / 2.0f, m_origin, m_body->GetAngle());


		//Box fixtures properties
		m_fixtureDef.shape = &m_boxShape;

		m_fixtureDef.density = config.m_fixtureDef.density;
		m_fixtureDef.friction = config.m_fixtureDef.friction;
		m_fixtureDef.restitution = config.m_fixtureDef.restitution;
		m_fixtureDef.isSensor = config.m_fixtureDef.isSensor;

		m_layer = config.m_layer;
		m_userDataName = static_cast<short>(config.m_layer);
		m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&m_userDataName);

		m_body->CreateFixture(&m_fixtureDef);

		if (m_bodyDef.type == b2_staticBody)
		{
			TRACE_CHANNEL("COLLISION", "Static Sprite position is ", sprite.getPosition().x, " , ", sprite.getPosition().y);
			TRACE_CHANNEL("COLLISION", "Static Sprite scale is ", sprite.getScale().x, " , ", sprite.getScale().y);

			b2Vec2 origin = m_body->GetLocalCenter();
			b2Vec2 position = m_body->GetTransform().p;
			float rotaion = m_body->GetAngle();

			TRACE_CHANNEL("COLLISION", "Static Collider origin ", origin.x, " , ", origin.y);
			TRACE_CHANNEL("COLLISION", "Static Collider position ", position.x, " , ", position.y);
			TRACE_CHANNEL("COLLISION", "Static Collider roatation ", rotaion);
		}
		else if (m_bodyDef.type == b2_dynamicBody)
		{
			TRACE_CHANNEL("COLLISION", "Dynamic Sprite position is ", sprite.getPosition().x, " , ", sprite.getPosition().y);
			TRACE_CHANNEL("COLLISION", "Dynamic Sprite scale is ", sprite.getScale().x, " , ", sprite.getScale().y);

			b2Vec2 origin = m_body->GetLocalCenter();
			b2Vec2 position = m_body->GetPosition();
			float rotaion = m_body->GetAngle();

			TRACE_CHANNEL("COLLISION", "Dynamic Collider origin ", origin.x, " , ", origin.y);
			TRACE_CHANNEL("COLLISION", "Dynamic Collider position ", position.x, " , ", position.y);
			TRACE_CHANNEL("COLLISION", "Dynamic Collider roatation ", rotaion);
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

	b2Vec2 RectAngleCollider::getColliderPosition()
	{
		if (!m_body)
		{
			return b2Vec2_zero;
		}
		return m_body->GetTransform().p;
	}

#ifdef IS_RATCHET_DEBUG
	void RectAngleCollider::printBodyPositionRotation()
	{
		if (!m_body)
		{
			return;
		}
		TRACE_CHANNEL("PHYSICS", getColliderPosition().x, " x axis ", getColliderPosition().y, " y axis ");
		TRACE_CHANNEL("PHYSICS", m_body->GetAngle(), " degrees ");
	}

	void RectAngleCollider::printSpriteColliderPosition(sf::Sprite& sprite, int bodyState)
	{
		if (!m_body)
		{
			return;
		}

		if (bodyState == STATIC)
		{
			TRACE_CHANNEL("PHYSICS", "Static position is ", m_body->GetTransform().p.x, " , ", m_body->GetTransform().p.y, " VS Sprite position ",
				sprite.getPosition().x, " , ", sprite.getPosition().y);
		}
		else if (bodyState == DYNAMIC)
		{
			TRACE_CHANNEL("PHYSICS", "Dynamic position is ", m_body->GetTransform().p.x, " , ", m_body->GetTransform().p.y, " VS Sprite position ",
				sprite.getPosition().x, " , ", sprite.getPosition().y);
		}
	}

	void RectAngleCollider::debugRender(sf::RenderTarget& target)
	{

		if (!m_body)
		{
			return;
		}
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
				getGlobalWidth(),
				getGlobalHeight()
			)
		);

		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Green);
		outline.setOutlineThickness(0.025f);
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
		//target.draw(bodyPosition);
	}
#endif

	void RectAngleCollider::drawColliderCenterBased(sf::RenderTarget& target)
	{
		sf::RectangleShape colliderOutline;

		colliderOutline.setSize(sf::Vector2f(
			getGlobalWidth(),
			getGlobalHeight()));

		colliderOutline.setFillColor(sf::Color::Transparent);
		colliderOutline.setOutlineColor(sf::Color::Green);
		colliderOutline.setOutlineThickness(0.01f);

		colliderOutline.setOrigin(
			colliderOutline.getSize().x / 2.0f,
			colliderOutline.getSize().y / 2.0f);

		b2Vec2 worldPos = m_body->GetWorldPoint(m_boxShape.m_centroid);

		colliderOutline.setPosition(
			worldPos.x,
			worldPos.y);

		colliderOutline.setRotation(
			m_body->GetAngle() * (180.f / M_PI));

		target.draw(colliderOutline);
	}

	void RectAngleCollider::getLeftPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
	{

		if (!m_body)
		{
			return;
		}
		ColliderBase::getLeftPointsForRaycast(xStart, yStart, xEnd, yEnd);

		b2Vec2 playerPosition = m_body->GetPosition();

		xStart = playerPosition.x + getGlobalWidth() * 0.018f;
		yStart = playerPosition.y + (getGlobalHeight() / 2.f);

		xEnd = xStart;
		yEnd = (yStart + (getGlobalHeight() / 2.f)) + getGlobalHeight() * 0.018f;
	}

	void RectAngleCollider::getMiddlePointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
	{
		if (!m_body)
		{
			return;
		}

		ColliderBase::getMiddlePointsForRaycast(xStart, yStart, xEnd, yEnd);

		b2Vec2 playerPosition = m_body->GetPosition();

		xStart = playerPosition.x + (getGlobalWidth() / 2.f);
		yStart = playerPosition.y + (getGlobalHeight() / 2.f);

		xEnd = xStart;
		yEnd = (yStart + (getGlobalHeight() / 2.f)) + getGlobalHeight() * 0.018f;
	}

	void RectAngleCollider::getRightPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
	{
		if (!m_body)
		{
			return;
		}
		ColliderBase::getRightPointsForRaycast(xStart, yStart, xEnd, yEnd);

		b2Vec2 playerPosition = m_body->GetPosition();

		xStart = (playerPosition.x + getGlobalWidth()) - getGlobalWidth() * 0.018f;
		yStart = playerPosition.y + (getGlobalHeight() / 2.f);

		xEnd = xStart;
		yEnd = (yStart + (getGlobalHeight() / 2.f)) + getGlobalHeight() * 0.018f;
	}

	bool RectAngleCollider::performGroundRayCast(sf::Sprite& sprite)
	{
		if (!m_body || !s_physicsWorld)
		{
			return false;
		}

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

		if ((callbackLeft.m_fraction <= 1.0f || callbackRight.m_fraction <= 1.0f || callbackMiddle.m_fraction <= 1.0f) && (callbackLeft.m_hit || callbackRight.m_hit || callbackMiddle.m_hit))
		{
			TRACE_CHANNEL("COLLISION", "Is grounded");
			return true;
		}

		TRACE_CHANNEL("COLLISION", "HIT : ", callbackLeft.m_hit);
		

		return false;

	}

	RectAngleColliderConfig::RectAngleColliderConfig()
	{
	}
}