#include "stdafx.h"
#include "ColliderBase.h"

#include "game/Player.h"
#include "SelfControlledCreature.h"

#include "game/Game.h"

namespace ratchet
{
	bool ColliderBase::isColliderToDestroy()
	{
		return m_isColliderSetDestroy;
	}
	ColliderBase::ColliderBase(const ColliderBaseConfig& config)
	{
		m_body = nullptr;

		m_obj = nullptr;


#ifdef IS_RATCHET_DEBUG
		m_debugDraw = config.m_debugDraw;
#endif

		m_checkTopPlatformsDirectionX = 1.f;

		m_layer = config.m_layer;
	}


	void ColliderBase::applyMovement(const bool& changeX, const float& xVelocity, const bool& changeY, const float& yVelocity)
	{
		b2Vec2 velocity = m_body->GetLinearVelocity();

		velocity.x = 0.0f;


		if (auto* drone = dynamic_cast<SelfControlledCreature*>(m_obj))
		{
			if (drone->m_movementType == MovementType::AIR)
			{
				velocity.y = 0.0f;
			}
		}

		if (changeX)
		{
			velocity.x = xVelocity;
		}
		if (changeY)
		{
			velocity.y = yVelocity;
		}
		m_body->SetAwake(true);

		m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
	}

	void ColliderBase::aaplyForce(b2Vec2 direction, float force)
	{
		if (!m_body)
		{
			return;
		}

		b2Vec2 dir = direction;

		if (dir.LengthSquared() > 0.0f)
		{
			dir.Normalize();
		}

		b2Vec2 velocity = m_body->GetLinearVelocity();
		velocity.y = 0.0f;

		b2Vec2 impulse(dir.x * force, dir.y * force);


		m_body->SetLinearVelocity(impulse);
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

#ifdef IS_RATCHET_DEBUG
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

#endif

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

	bool ColliderBase::performSpringRayCast(sf::Sprite& sprite)
	{
		return false;
	}

	bool ColliderBase::performUpPlatformRayCast(sf::Sprite& sprite)
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

	void ColliderBase::getJumpOverPlatformsTopRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const
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

	void ColliderBase::getCheckFollowTargetRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction)
	{
		xStart = 0.0f;
		yStart = 0.0f;
		xEnd = 0.0f;
		yEnd = 0.0f;
		direction = 0.0f;
	}

	bool ColliderBase::performFollowTargetRayCast(const sf::Vector2f& charaterPosition, const sf::Vector2f& targetPosition)
	{
		return false;
	}

	void ColliderBase::getCheckFallingRiscRaycastPoints(float& xStart, float& yStart, float& xEnd, float& yEnd, float direction) const
	{
		xStart = 0.0f;
		yStart = 0.0f;
		xEnd = 0.0f;
		yEnd = 0.0f;
		direction = 0.0f;

	}

	bool ColliderBase::performCheckFallingRiskRaycast(sf::Sprite& sprite, float& direction)
	{
		return false;
	}

	std::vector<b2Fixture*>ColliderBase::performOverlapCircle(const b2Vec2& center, float radius)
	{
		b2AABB aabb;
		aabb.lowerBound = center - b2Vec2(radius, radius);
		aabb.upperBound = center + b2Vec2(radius, radius);

		CircleOverlapCallBack callback(m_body, center, radius);

		s_physicsWorld->QueryAABB(&callback, aabb);

		return callback.found;
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
	float CheckFallingRiskRaycastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
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

	float CheckFollowTargetRaycastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		if (!fixture)
			return -1.0f;

		b2Body* body = fixture->GetBody();

		if (!body || !body->IsEnabled())
			return -1.0f;

		if (body == m_ignoredBody)
			return -1.0f;


		const short* fixtureUserData =
			reinterpret_cast<const short*>(fixture->GetUserData().pointer);

		if (*fixtureUserData == static_cast<short>(PhysicsLayer::Projectile) || *fixtureUserData == static_cast<short>(PhysicsLayer::Items)||
			*fixtureUserData == static_cast<short>(PhysicsLayer::Springs) || *fixtureUserData == static_cast<short>(PhysicsLayer::CheckPoint) ||
			*fixtureUserData == static_cast<short>(PhysicsLayer::Obstacles))
		{
			return -1.0f;
		}

		if (!fixtureUserData)
			return -1.0f;

		if (*fixtureUserData == static_cast<short>(PhysicsLayer::Creature))
		{
			m_hit = true;
			m_point = point;
			m_normal = normal;
			m_fraction = fraction;

			return fraction;
		}

		m_hit = false;
		return 0.0f;
	}

	CircleOverlapCallBack::CircleOverlapCallBack(b2Body* ingnoredBody, const b2Vec2& c, float r)
	{
		m_ignoredBody = ingnoredBody;
		center = c;
		radius = r;
	}

	bool CircleOverlapCallBack::ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();

		if (body == m_ignoredBody)
		{
			return true;
		}

		b2Vec2 pos = body->GetPosition();

		float dx = pos.x - center.x;
		float dy = pos.y - center.y;

		if (dx * dx + dy * dy <= radius * radius)
		{
			found.push_back(fixture);
		}

		return true;

	}

	float SpringRayCastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
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
			if (fixtureUserData && *fixtureUserData == static_cast<short>(PhysicsLayer::Springs))
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

	SpringRayCastCallBack::SpringRayCastCallBack(b2Body* ingnoedBody)
	{
		m_hit = false;
		m_fraction = 1.0f;

		m_ignoredBody = ingnoedBody;
	}


	bool ContactFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
	{
		PhysicsLayer* dataA = (PhysicsLayer*)fixtureA->GetUserData().pointer;
		PhysicsLayer* dataB = (PhysicsLayer*)fixtureB->GetUserData().pointer;

		if ((*dataA == PhysicsLayer::Creature && *dataB == PhysicsLayer::Springs) ||
			(*dataB == PhysicsLayer::Creature && *dataA == PhysicsLayer::Springs))
		{
			if (*dataA == PhysicsLayer::Creature)
			{
				b2Body* bodyA = fixtureA->GetBody();
				ColliderBase* colliderA = (ColliderBase*)bodyA->GetUserData().pointer;
				GameObject* objectA = colliderA->m_obj;

				b2Body* bodyB = fixtureB->GetBody();
				ColliderBase* colliderB = (ColliderBase*)bodyB->GetUserData().pointer;
				GameObject* objectB = colliderB->m_obj;

				if (auto* creatureA = dynamic_cast<Creature*>(objectA))
				{
					if (creatureA->m_faction != objectB->m_faction)
					{
						return false;
					}
				}
				else if (auto* creatureB = dynamic_cast<Creature*>(objectB))
				{
					if (creatureB->m_faction != objectA->m_faction)
					{
						return true;
					}
				}
			}
			else if (*dataB == PhysicsLayer::Creature)
			{
				b2Body* bodyB = fixtureB->GetBody();
				ColliderBase* colliderB = (ColliderBase*)bodyB->GetUserData().pointer;
				GameObject* objectB = colliderB->m_obj;

				b2Body* bodyA = fixtureA->GetBody();
				ColliderBase* colliderA = (ColliderBase*)bodyA->GetUserData().pointer;
				GameObject* objectA = colliderA->m_obj;


				if (auto* creatureB = dynamic_cast<Creature*>(objectB))
				{
					if (creatureB->m_faction != objectA->m_faction)
					{
						return false;
					}
				}
				else if (auto* creatureA = dynamic_cast<Creature*>(objectA))
				{
					if (creatureA->m_faction != objectB->m_faction)
					{
						return true;
					}
				}
			}
		}
		return true;
	}

}




