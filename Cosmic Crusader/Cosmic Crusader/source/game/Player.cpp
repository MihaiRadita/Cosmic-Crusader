#include "stdafx.h"
#include "Player.h"

namespace ratchet
{
	void Player::destroyPlayerAnimations()
	{

	}

	Player::Player(const CreatureConfig& config) : Creature(config)
	{
		initVariables();
	}

	void Player::initVariables()
	{
		m_gravity = 0.090f;
		m_isMoving = false;
	}

	void Player::handleEvent(sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				if (m_input.x >= 0) m_input.x = -1;
				break;
			case sf::Keyboard::D:
				if (m_input.x <= 0) m_input.x = +1;
				break;
			case sf::Keyboard::Space:
				m_input.isJump = true;
				break;
			}
			break;
		}
		case sf::Event::KeyReleased:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				if (m_input.x < 0) m_input.x = 0;
				break;
			case sf::Keyboard::D:
				if (m_input.x > 0) m_input.x = 0;
				break;
			case sf::Keyboard::Space:
				m_input.isJump = false;
				break;
			}
			break;
		}
		}
	}

	void Player::setPlayerByColliderPos()
	{
	}

	void Player::setPosition(const float x, const float y)
	{
		m_sprite.setPosition(x, y);
	}

	//	void Player::updateMovement()
	//	{
	//		if (m_controls["left"] == true)
	//		{
	//			
	//			//if (m_isGround)
	//			{
	//				if (m_animationState != ANIMATION_STATE::JUMP)
	//				{
	//
	//					m_animationState = ANIMATION_STATE::MOVING_LEFT;
	//					switchAnimation();
	//					m_isMoving = true;
	//				}
	//			}
	//
	//			invertPlayerMovingSpriteScale(-1);
	//			if (m_isMoving)
	//			{
	//				m_collider->applyMovement(m_moveSpeed, m_controls["left"], -1);
	//				auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
	//				m_playerSprite.setPosition(playerPosition);
	//
	//				// m_playerSprite.move(m_playerPosition.x * -1.f * m_moveSpeed, 0.f);
	//
	//#ifdef IS_RATCHET_DEBUG
	//				std::cout << "Moving Left" << std::endl;
	//#endif
	//			}
	//#ifdef IS_RATCHET_DEBUG
	//			std::cout << "veloctiy x to left = " << getPlayerPosition().x << std::endl;
	//#endif
	//		}
	//		else if (m_controls["right"] == true)
	//		{
	//			//if (m_isGround)
	//			{
	//				if (m_animationState != ANIMATION_STATE::JUMP)
	//				{
	//					m_animationState = ANIMATION_STATE::MOVING_RIGHT;
	//					switchAnimation();
	//					m_isMoving = true;
	//				}
	//			}
	//
	//			invertPlayerMovingSpriteScale(1);
	//			if (m_isMoving)
	//			{
	//				m_collider->applyMovement(m_moveSpeed, m_controls["right"], 1);
	//				auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
	//				m_playerSprite.setPosition(playerPosition);
	//				// m_playerSprite.move(m_playerPosition.x * m_moveSpeed, 0.f);
	//#ifdef IS_RATCHET_DEBUG
	//				std::cout << "Moving Right" << std::endl;
	//#endif
	//			}
	//#ifdef IS_RATCHET_DEBUG
	//			std::cout << "veloctiy x to right = " << getPlayerPosition().x << std::endl;
	//#endif
	//		}
	//
	//		if (isNoControlActive() && m_animationState != ANIMATION_STATE::JUMP && m_animationState != ANIMATION_STATE::JUMP_RUNNING)
	//		{
	//#ifdef IS_RATCHET_DEBUG
	//			std::cout << "Idle" << std::endl;
	//			std::cout << m_animationState << std::endl;
	//#endif
	//			m_animationState = ANIMATION_STATE::IDLE;
	//			m_isMoving = false;
	//			switchAnimation();
	//		}
	//
	//	}

	void Player::updateMovement()
	{
		m_movementType = MOVEMENTTYPE_UNKNOWN;
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

		m_movementType = isGrounded() ? GROUND : UNGROUND;

		DBOUT("[PLAYER] BEFORE" << " Velocity " << " X: " << m_collider->m_body->GetLinearVelocity().x << ", Y: " << m_collider->m_body->GetLinearVelocity().y);

		m_collider->applyMovement(changeX, xVelocity, changeY, yVelocity);

		auto playerPosition = sf::Vector2f(getPosition().x, getPosition().y);
		m_sprite.setPosition(playerPosition);

		DBOUT("[PLAYER] AFTER" << " Velocity " << " X: " << m_collider->m_body->GetLinearVelocity().x << ", Y: " << m_collider->m_body->GetLinearVelocity().y);
//		if (m_input.x < 0)
//		{
//			if (m_movementType == GROUND)
//			{
//				if (m_isGround)
//				{
//					if (m_characterAnimationState != JUMP && m_characterAnimationState != JUMP_RUNNING)
//					{
//						if (m_characterAnimationState != MOVING)
//						{
//							m_characterAnimationState = MOVING;
//							switchAnimation();
//						}
//						m_isMoving = true;
//					}
//				}
//
//				invertCharacterMovingSpriteScale(-1);
//
//				if (m_isMoving)
//				{
//					m_collider->applyMovement(m_movementSpeed, m_isMoving, m_input.x, m_isGround);
//					auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
//					m_sprite.setPosition(playerPosition);
//				}
//			}
//		}
//		else if (m_input.x > 0)
//		{
//			m_isMoving = true;
//			if (m_movementType == GROUND)
//			{
//				if (m_isGround)
//				{
//					if (m_characterAnimationState != JUMP && m_characterAnimationState != JUMP_RUNNING)
//					{
//						if (m_characterAnimationState != MOVING)
//						{
//							m_characterAnimationState = MOVING;
//							switchAnimation();
//						}
//						m_isMoving = true;
//					}
//				}
//				invertCharacterMovingSpriteScale(1);
//				if (m_isMoving)
//				{
//					m_collider->applyMovement(m_movementSpeed, m_isMoving, m_input.x, m_isGround);
//					auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
//					m_sprite.setPosition(playerPosition);
//
//				}
//			}
//		}
//
//		if (isNoControlActive() && m_characterAnimationState != ANIMATION_STATE::JUMP && m_characterAnimationState != ANIMATION_STATE::JUMP_RUNNING)
//		{
//#ifdef IS_RATCHET_DEBUG
//			std::cout << "Idle" << std::endl;
//			std::cout << m_characterAnimationState << std::endl;
//#endif
//			m_characterAnimationState = ANIMATION_STATE::IDLE;
//			switchAnimation();
//			m_isMoving = false;
//		}

	}

	void Player::updateRotation()
	{
		m_sprite.rotate(m_rotation);
	}

	void Player::updateJump()
	{
		//if (m_movementType == GROUND)
		//{
		//	m_isGround = m_collider->performGroundRayCast(m_sprite);
		//	if (m_isGround && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) > 17)
		//	{
		//		if (m_characterAnimationState == JUMP)
		//		{
		//			m_characterAnimationState = IDLE;
		//		}
		//	}

		//	if (m_isGround && m_input.isJump == true && m_characterAnimationState != JUMP && m_characterAnimationState != JUMP_RUNNING)
		//	{
		//		if (m_characterAnimationState == IDLE)
		//		{
		//			m_characterAnimationState = JUMP;
		//			switchAnimation();
		//		}
		//	}

		//	if (m_characterAnimationState == JUMP && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) < 17)
		//	{
		//		m_isMoving = false;
		//	}
		//	else if (m_characterAnimationState == JUMP && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) == 17 && m_isGround)
		//	{
		//		m_isMoving = true;
		//		m_collider->applyJump(m_jumpImpulse, m_isGround);
		//		m_isGround = false;
		//	}

		//	// DBOUT("isGround = " << (m_isGround ? "TRUE" : "FALSE"));
		//}
	}

	void Player::updateRunningJump()
	{
		//if (m_movementType == GROUND)
		//{
		//	m_isGround = m_collider->performGroundRayCast(m_sprite);
		//	if (m_isGround == true && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) >= 16)
		//	{
		//		if (m_characterAnimationState == ANIMATION_STATE::JUMP_RUNNING)
		//		{
		//			m_characterAnimationState = ANIMATION_STATE::IDLE;

		//		}
		//	}

		//	if (m_input.isJump == true && m_characterAnimationState != ANIMATION_STATE::JUMP_RUNNING && m_characterAnimationState != ANIMATION_STATE::JUMP && m_isGround)
		//	{
		//		if (m_characterAnimationState == ANIMATION_STATE::MOVING)
		//		{
		//			m_characterAnimationState = ANIMATION_STATE::JUMP_RUNNING;
		//			switchAnimation();
		//		}
		//	}

		//	if (m_characterAnimationState == JUMP_RUNNING && m_isGround)
		//	{
		//		m_collider->applyJump(m_jumpImpulse, m_isGround);
		//		m_isGround = false;
		//	}
		//}
	}


	void Player::setIsOnGround(bool isGround)
	{
		// m_isGround = isGround;
	}

	void Player::updateInput()
	{
	}

	Player::~Player() 
	{
	}

#ifdef IS_RATCHET_DEBUG
	void Player::printSpriteColliderPositionPlayer()
	{
		//m_collider->printSpriteColliderPosition(m_sprite, DYNAMIC);
	}
#endif
}