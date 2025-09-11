#include "stdafx.h"
#include "SelfControlledCreature.h"


namespace ratchet
{

	ratchet::SelfControlledCreature::SelfControlledCreature(const CreatureConfig& config) : Creature(config)
	{
		m_targetMaxDistanceDetectionX = config.m_targetMaxDistanceDetectionX;
		m_targetMaxDistanceDetectionY = config.m_targetMaxDistanceDetectionY;
		m_targetMaxDistanceLoseX = config.m_targetMaxDistanceLoseX;
		m_targetMaxDistanceLoseY = config.m_targetMaxDistanceLoseY;

		SetTarget(m_faction);
	}
	void SelfControlledCreature::SetTarget(Faction& faction)
	{
		for (auto* obj : s_gameObjects)
		{
			if (obj != this)
			{
				if (faction != Faction::FACTION_UNKNOWN && obj->m_faction != Faction::FACTION_UNKNOWN)
				{
					if (faction != obj->m_faction)
					{
						m_target = (Creature*)obj;
						break;
					}
				}
			}
		}
	}
	void SelfControlledCreature::handleEvent()
	{
		if (m_isTargetDetected)
		{
			TRACE_CHANNEL("AI_TARGETING", "Enemy detects target(PLAYER)!");
			if (m_isTagetBehindCharacter == false)
			{
				m_facingRight = true;

			}
			else if (m_isTagetBehindCharacter == true)
			{
				m_facingRight = false;
			}

			invertCharacterMovingSpriteScale(m_facingRight ? 1.0f : -1.0f);
		}
		else
		{

		}
	}
	void SelfControlledCreature::update()
	{
		if (!m_activeGameObject) return;

		if (m_collider && !m_collider->m_skipRaycastThisFrame)
		{
			m_isGround = m_collider->performGroundRayCast(m_sprite);
		}
		else
		{
			m_isGround = false;
			m_collider->m_skipRaycastThisFrame = false;
		}

		detectTarget(m_target);
		handleEvent();

		Creature::update();
	}
	void SelfControlledCreature::updateMovement()
	{
		auto position = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
		m_sprite.setPosition(position);

		// Sync sprite rotation with collider
		m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
		m_sprite.setRotation(m_rotation);

		auto aiCharacterPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
		setPosition(aiCharacterPosition);
	}
	void SelfControlledCreature::detectTarget(Creature* target)
	{
		sf::Vector2f targetdistancevector = this->getPosition() - target->getPosition();

		if (targetdistancevector.x > 0.0f)
		{
			m_isTagetBehindCharacter = true;
		}
		else if (targetdistancevector.x < 0.0f)
		{
			m_isTagetBehindCharacter = false;
			targetdistancevector.x *= -1.f;
		}

		if (targetdistancevector.y < 0.0f)
		{
			targetdistancevector.y *= -1.f;
		}

		if (targetdistancevector.y <= m_targetMaxDistanceDetectionY)
		{
			
			if (targetdistancevector.x <= m_targetMaxDistanceDetectionX)
			{
				m_isTargetDetected = true;
			}
			else if (targetdistancevector.x > m_targetMaxDistanceDetectionX)
			{
				m_isTargetDetected = false;
			}
		}
		else if (targetdistancevector.y > m_targetMaxDistanceDetectionY)
		{
			m_isTargetDetected = false;
		}
	}
}
