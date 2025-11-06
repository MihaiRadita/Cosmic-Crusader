#include "stdafx.h"
#include "SelfControlledCreature.h"


namespace ratchet
{

	ratchet::SelfControlledCreature::SelfControlledCreature(const SelfControlledCreatureConfig& config) : Creature(config)
	{

		m_targetMaxDistanceDetectionX = config.m_targetMaxDistanceDetectionX;
		m_targetMaxDistanceDetectionY = config.m_targetMaxDistanceDetectionY;
		m_targetMaxDistanceLoseX = config.m_targetMaxDistanceLoseX;
		m_targetMaxDistanceLoseY = config.m_targetMaxDistanceLoseY;
		m_targetMaxDistanceAttackX = config.m_targetMaxDistanceAttackX;
		m_targetMaxDistanceAttackY = config.m_targetMaxDistanceAttackY;
	}
	SelfControlledCreature::~SelfControlledCreature()
	{

	}
	void SelfControlledCreature::checkTargetToAttack(Creature* target)
	{
		sf::Vector2f m_targetAttackDistanceVector = this->getPosition() - target->getPosition();

		if (m_targetAttackDistanceVector.x < 0.0f)
		{
			m_targetAttackDistanceVector.x *= -1.f;
		}

		if (m_targetAttackDistanceVector.x <= m_targetMaxDistanceAttackX)
		{
			m_isAttacking = true;
		}
		else if (m_targetAttackDistanceVector.x > m_targetMaxDistanceAttackX)
		{
			m_isAttacking = false;
		}


	}
	void SelfControlledCreature::canJumpOver()
	{
		if (m_collider && !m_collider->m_skipRaycastThisFrame)
		{
			m_collider->m_collierFacingDirectionX = m_facingRight ? 1.0f : -1.0f;
			m_canJumpOver = m_collider->performJumpOverPlatformsRaycast(m_sprite, m_collider->m_collierFacingDirectionX);
		}
		else
		{
			m_canJumpOver = false;
			m_collider->m_skipRaycastThisFrame = false;
		}
	}
	void SelfControlledCreature::isFallingRisk()
	{
		if (m_collider && !m_collider->m_skipRaycastThisFrame)
		{
			m_collider->m_collierFacingDirectionX = m_facingRight ? 1.0f : -1.0f;
			m_isFallingRisk = m_collider->performCheckFallingRiskRaycast(m_sprite, m_collider->m_collierFacingDirectionX);
		}
		else
		{
			m_isFallingRisk = false;
			m_collider->m_skipRaycastThisFrame = false;
		}
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
	void SelfControlledCreature::PostCosntructFixup()
	{
		if (m_collider)
		{
			m_collider->SetOwner(this);
		}
	}
	void SelfControlledCreature::computeAimBulletRotation()
	{
		sf::Vector2f firePoint = m_currentFirePoint;
		sf::Vector2f targetPos = m_target->getPosition();

		sf::Vector2f direction = targetPos - firePoint;
		sf::Vector2f directionNormalised = sf::Vector2f(0.0f, 0.0f);
		calculateNormalised(direction.x, direction.y, directionNormalised.x, directionNormalised.y);

		float angleRad = std::atan2(directionNormalised.y, directionNormalised.x);
		float angleDeg = angleRad * 180.f / M_PI;

		m_currentFireRotationRadians = angleRad;
		m_currentFireRoationDegrees = angleDeg;
		m_currenFireDirectionNorm = directionNormalised;
	}
	void SelfControlledCreature::Start()
	{
		PostCosntructFixup();
		SetTarget(m_faction);
	}

	void SelfControlledCreature::handleEvent()
	{
		detectTarget(m_target);

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

			checkTargetToAttack(m_target);

			isFallingRisk();

			canJumpOver();

			if (m_isAttacking)
			{
				m_input.x = 0.f;
				m_input.isJump = false;

				if (m_isGround)
				{
					if (!m_waitTostartAttack)
					{
						m_fireCooldown.restart();
						m_waitTostartAttack = true;
						m_input.m_isFiring = false;

					}
					else
					{
						if (m_fireCooldown.getElapsedTime().asSeconds() >= m_fireRate)
						{
							m_input.m_isFiring = true;
						
						}		
					}
					
				}
			}
			else
			{
				if (m_input.m_isFiring == true)
				{

					if (m_currentCharacterState == WeaponAnimation::STATE::Recoil)
					{
						m_currentCharacterState = WeaponAnimation::STATE::Aim;
					}
					m_input.m_isFiring = false;
				}
				m_waitTostartAttack = false;

				m_fireCooldown.restart();

				if (m_canJumpOver)
				{
					if (m_isGround)
					{
						m_input.isJump = true;
					}
					else
					{
						m_input.isJump = false;
					}
				}
				else
				{
					m_input.isJump = false;
				}

				if (m_isFallingRisk)
				{
					if (m_facingRight)
					{
						m_input.x = 1.f;
					}
					else
					{
						m_input.x = -1.f;
					}
				}
				else
				{
					m_input.x = 0.0f;
				}
			}
		}
		else
		{
			m_input.x = 0;

			m_input.isJump = false;

			if (m_input.m_isFiring == true)
			{
				if (m_currentCharacterState == WeaponAnimation::STATE::Recoil)
				{
					m_currentCharacterState = WeaponAnimation::STATE::Aim;
				}
				m_input.m_isFiring = false;
			}
			m_waitTostartAttack = false;
			m_fireCooldown.restart();

		}

		if (m_canJumpOver == true)
		{
			TRACE_CHANNEL("AI_JUMP_OVER_PLATFORMS", "ENEMY CAN JUMP OVER PLATFORMS!");
		}
		else
		{
			TRACE_CHANNEL("AI_JUMP_OVER_PLATFORMS", "ENEMY CAN NOT JUMP OVER PLATFORMS!");
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

		m_characterShootingPosition.setPosition(getPosition().x, getPosition().y);

		handleEvent();

		Creature::update();
	}
	void SelfControlledCreature::updateMovement()
	{

		m_isMoving = false;
		bool changeX = false;
		float xVelocity = 0.0f;
		bool changeY = false;
		float yVelocity = 0.0f;

		if (m_input.x != 0)
		{
			m_isMoving = true;
			changeX = true;
			xVelocity = m_movementSpeed * m_input.x;
		}

		if (m_input.isJump && isGrounded())
		{
			m_isMoving = true;
			changeY = true;
			yVelocity = m_jumpImpulse;
		}

		m_collider->applyMovement(changeX, xVelocity, changeY, yVelocity);

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

	void SelfControlledCreature::render(sf::RenderTarget& target)
	{
		GameObject::render(target);
		target.draw(m_characterShootingPosition);
		target.draw(m_shootingPointDynamic);
		target.draw(m_shooitngPointCenter);
	}
}
