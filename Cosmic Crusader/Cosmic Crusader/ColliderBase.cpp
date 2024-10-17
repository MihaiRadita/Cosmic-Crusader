#include "stdafx.h"
#include "ColliderBase.h"

namespace ratchet
{
	ColliderBase::ColliderBase(const BaseColliderConfig& config)
	{
		m_body = nullptr;

	}

	void ColliderBase::applyMovement(const bool& changeX, const float& xVelocity, const bool& changeY, const float& yVelocity)
	{
		b2Vec2 velocity = m_body->GetLinearVelocity();
		if (changeX)
		{
			velocity.x = xVelocity;
		}
		if (changeY)
		{
			velocity.y = yVelocity;
		}

		m_body->SetLinearVelocity(velocity);
	}

	b2Body* ColliderBase::getBody()
	{
		return m_body;
	}

	void ColliderBase::printBodyPositionRotation()
	{
	}

	void ColliderBase::printSpriteColliderPosition(sf::Sprite& sprite, int bodyState)
	{
	}

	void ColliderBase::debugRender(sf::RenderTarget& target)
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

	bool ColliderBase::performGroundRayCast(sf::Sprite& sprite)
	{
		return false;
	}

	float GroundRayCastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		if (fixture)
		{
			b2Body* body = fixture->GetBody();
			if (body == m_ignoredBody)
			{
				return -1.0f;
			}
			const short* fixtureUserData = reinterpret_cast<const short*>(fixture->GetUserData().pointer);
			if (fixtureUserData && *fixtureUserData == static_cast<short>(PhysiscsLayer::Platforms))
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
	BaseColliderConfig::BaseColliderConfig()
	{
	}
}




