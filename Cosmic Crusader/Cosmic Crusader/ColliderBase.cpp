#include "stdafx.h"
#include "ColliderBase.h"

#include "game/Player.h"
#include "SelfControlledCreature.h"

namespace ratchet
{
	ColliderBase::ColliderBase(const ColliderBaseConfig& config)
	{
		m_body = nullptr;

		m_obj = nullptr;
		

#ifdef IS_RATCHET_DEBUG
		m_debugDraw = config.m_debugDraw;
#endif

		m_checkTopPlatformsDirectionX = 1.f;
	}

	ColliderBase::~ColliderBase()
	{
	}

	void ColliderBase::applyMovement(const bool& changeX, const float& xVelocity, const bool& changeY, const float& yVelocity)
	{
		b2Vec2 velocity = m_body->GetLinearVelocity();

		velocity.x = 0.0f;

		if (changeX)
		{
			velocity.x = xVelocity;
		}
		if (changeY)
		{
			velocity.y = yVelocity;
		}
		m_body->SetAwake(true);

		m_body->SetLinearVelocity(velocity);
	}

	void ColliderBase::SetOwner(GameObject* obj)
	{
		m_obj = obj;
	}

	b2Body* ColliderBase::getBody()
	{
		return m_body;
	}

	b2Vec2 ColliderBase::getColliderOrigin() const 
	{ 
		return m_origin; 
	}

	void ColliderBase::printBodyPositionRotation()
	{
	}

	void ColliderBase::printSpriteColliderPosition(sf::Sprite& sprite, int bodyState)
	{
	}

	void ColliderBase::debugRender(sf::RenderTarget& target)
	{
#ifdef IS_RATCHET_DEBUG
		if (!m_debugDraw) return;
#endif
	}

	void ColliderBase::drawColliderCenterBased(sf::RenderTarget& target)
	{
	}

	void ColliderBase::setColliderPosition(float x, float y)
	{
		float currentAngle = m_body->GetAngle();
		b2Vec2 newPosition = b2Vec2(x, y);

		m_body->SetTransform(newPosition, currentAngle);
	}

	void ColliderBase::setColliderRotation(float angle)
	{
		float newAngle = angle;
		b2Vec2 currentPosition = m_body->GetPosition();

		m_body->SetTransform(currentPosition, newAngle);
	}

	void ColliderBase::getLeftPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
	{
		xStart = 0.0f;
		yStart = 0.0f;
		xEnd = 0.0f;
		yEnd = 0.0f;
	}

	void ColliderBase::getMiddlePointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
	{
		xStart = 0.0f;
		yStart = 0.0f;
		xEnd = 0.0f;
		yEnd = 0.0f;
	}

	void ColliderBase::getRightPointsForRaycast(float& xStart, float& yStart, float& xEnd, float& yEnd) const
	{
		xStart = 0.0f;
		yStart = 0.0f;
		xEnd = 0.0f;
		yEnd = 0.0f;
	}

	bool ColliderBase::performGroundRayCast(sf::Sprite& sprite)
	{
		return false;
	}

	void ColliderBase::getJumpOverPlatformsBottomRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const
	{
		xStart = 0.0f;
		yStart = 0.0f;
		xEnd = 0.0f;
		yEnd = 0.0f;
		direction = 0.0f;
	}

	void ColliderBase::getJumpOverPlatformsTopRaycastPoints( float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const
	{
		xStart = 0.0f;
		yStart = 0.0f;
		xEnd = 0.0f;
		yEnd = 0.0f;
		direction = 0.0f;
	}

	bool ColliderBase::performJumpOverPlatformsRaycast(sf::Sprite& sprite, float& direction)
	{
		return false;
	}

	float GroundRayCastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
 	{
		if (fixture)
		{
			b2Body* body = fixture->GetBody();

			if (!body || !body->IsEnabled())
			{
				return -1.0f;
			}

			if (body == m_ignoredBody)
			{
				return -1.0f;
			}
			const short* fixtureUserData = reinterpret_cast<const short*>(fixture->GetUserData().pointer);
			if (fixtureUserData && *fixtureUserData == static_cast<short>(PhysicsLayer::Platforms))
			{
				m_hit = true;
				m_point = point;
				m_normal = normal;
				m_fraction = fraction;
				return fraction;
			}
		}

		m_hit = false;
		return -1.0f;
	}
	ColliderBaseConfig::ColliderBaseConfig()
	{
	}
	float JumpOverPlatformsRayCastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		if (fixture)
		{
			b2Body* body = fixture->GetBody();

			if (!body || !body->IsEnabled())
			{
				return -1.0f;
			}

			if (body == m_ignoredBody)
			{
				return -1.0f;
			}
			const short* fixtureUserData = reinterpret_cast<const short*>(fixture->GetUserData().pointer);
			if (fixtureUserData && *fixtureUserData == static_cast<short>(PhysicsLayer::Platforms))
			{
				m_hit = true;
				m_point = point;
				m_normal = normal;
				m_fraction = fraction;
				return fraction;
			}
		}

		m_hit = false;
		return -1.0f;
	}
}




