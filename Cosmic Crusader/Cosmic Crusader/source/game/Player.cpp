#include "stdafx.h"
#include "Player.h"

namespace ratchet
{
	constexpr float M_PI = 22.0f / 7.0f;

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
		m_isGround = false;
		m_isMoving = false;
	}

	void Player::handleEvent(sf::Event& event)
	{
		m_playerEvents.push_back(event);
	}

	void Player::setPlayerByColliderPos()
	{
	}

	void Player::setPosition(const float x, const float y)
	{
		m_sprite.setPosition(x, y);
	}
	void Player::update()
	{
		updateInput();
		updateMovement();
		updateJump();
		updateRunningJump();
		updateAnimations();
		updatePhysics();
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
		if (m_Input.x < 0)
		{
			if (m_movementType == GROUND)
			{
				if (m_isGround)
				{
					if (m_characterAnimationState != JUMP && m_characterAnimationState != JUMP_RUNNING)
					{
						if (m_characterAnimationState != MOVING)
						{
							m_characterAnimationState = MOVING;
							switchAnimation();
						}
						m_isMoving = true;
					}
				}

				invertCharacterMovingSpriteScale(-1);

				if (m_isMoving)
				{
					m_collider->applyMovement(m_movementSpeed, m_isMoving, m_Input.x);
					auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
					m_sprite.setPosition(playerPosition);

				}
			}
		}
		else if (m_Input.x > 0)
		{
			m_isMoving = true;
			if (m_movementType == GROUND)
			{
				if (m_isGround)
				{
					if (m_characterAnimationState != JUMP && m_characterAnimationState != JUMP_RUNNING)
					{
						if (m_characterAnimationState != MOVING)
						{
							m_characterAnimationState = MOVING;
							switchAnimation();
						}
						m_isMoving = true;
					}
				}
				invertCharacterMovingSpriteScale(1);
				if (m_isMoving)
				{
					m_collider->applyMovement(m_movementSpeed, m_isMoving, m_Input.x);
					auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
					m_sprite.setPosition(playerPosition);

				}
			}
		}

			if (isNoControlActive() && m_characterAnimationState != ANIMATION_STATE::JUMP && m_characterAnimationState != ANIMATION_STATE::JUMP_RUNNING)
			{
#ifdef IS_RATCHET_DEBUG
				std::cout << "Idle" << std::endl;
				std::cout << m_characterAnimationState << std::endl;
#endif
				m_characterAnimationState = ANIMATION_STATE::IDLE;
				switchAnimation();
				m_isMoving = false;
			}
	}

	void Player::updateRotation()
	{
		m_sprite.rotate(m_rotation);
	}
	
	//	void Player::updateJump()
	//	{
	//		m_isGround = m_collider->performGroundRayCast(m_playerSprite);
	//
	//#ifdef IS_RATCHET_DEBUG
	//		std::cout << "IS GROUND GROUND " << m_isGround << std::endl;
	//#endif
	//
	//		if (m_isGround == true && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) > 17)
	//		{
	//			if (m_animationState == ANIMATION_STATE::JUMP)
	//			{
	//				m_animationState = ANIMATION_STATE::IDLE;
	//			}
	//		}
	//
	//		if (m_controls["jump"] == true && m_animationState != ANIMATION_STATE::JUMP && m_animationState != ANIMATION_STATE::JUMP_RUNNING && m_isGround)
	//		{
	//			if (m_animationState == ANIMATION_STATE::IDLE)
	//			{
	//				m_animationState = ANIMATION_STATE::JUMP;
	//				switchAnimation();
	//			}
	//		}
	//
	//		if ((m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) < 17 && m_animationState == ANIMATION_STATE::JUMP)
	//		{
	//			m_isMoving = false;
	//		}
	//		else if ((m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) == 17 && m_animationState == ANIMATION_STATE::JUMP && m_isGround)
	//		{
	//
	//			m_isMoving = true;
	//			m_collider->applyJump(m_jumpForce, m_isGround);
	//#ifdef IS_RATCHET_DEBUG
	//			std::cout << "JUMP JUMP " << std::endl;
	//#endif
	//			//m_isGround = false;
	//
	//
	//		}
	//		//m_playerSprite.move(0.f, m_yVelocity);
	//
	//	}

	//	void Player::updateRunningJump()
	//	{
	//		m_isGround = m_collider->performGroundRayCast(m_playerSprite);
	//
	//		if (m_isGround == true && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) >= 16)
	//		{
	//			if (m_animationState == ANIMATION_STATE::JUMP_RUNNING)
	//			{
	//				m_animationState = ANIMATION_STATE::IDLE;
	//
	//			}
	//			m_yVelocity = 0.f;
	//		}
	//		else
	//		{
	//			m_yVelocity += m_gravity;
	//		}
	//
	//
	//
	//		if (m_controls["jump"] == true && m_animationState != ANIMATION_STATE::JUMP_RUNNING && m_animationState != ANIMATION_STATE::JUMP && m_isGround)
	//		{
	//			if (m_animationState == ANIMATION_STATE::MOVING_LEFT || m_animationState == ANIMATION_STATE::MOVING_RIGHT)
	//			{
	//				m_animationState = ANIMATION_STATE::JUMP_RUNNING;
	//				switchAnimation();
	//			}
	//
	//
	//		}
	//
	//		if (m_animationState == ANIMATION_STATE::JUMP_RUNNING && m_isGround)
	//		{
	//
	//			m_collider->applyJump(m_jumpForce, m_isGround);
	//#ifdef IS_RATCHET_DEBUG
	//			std::cout << "JUMP JUMP " << std::endl;
	//#endif
	//			//m_isGround = false;
	//		}
	//
	//		//m_playerSprite.move(0.f, m_yVelocity);
	//
	//	}

	void Player::updateJump()
	{
		if (m_movementType == GROUND)
		{
			m_isGround = m_collider->performGroundRayCast(m_sprite);
			if (m_isGround && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) > 17)
			{
				if (m_characterAnimationState == JUMP)
				{
					m_characterAnimationState = IDLE;
				}
			}

			if (m_isGround && m_Input.isJump == true && m_characterAnimationState != JUMP && m_characterAnimationState != JUMP_RUNNING)
			{
				if (m_characterAnimationState == IDLE)
				{
					m_characterAnimationState = JUMP;
					switchAnimation();
				}
			}

			if (m_characterAnimationState == JUMP && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) < 17)
			{
				m_isMoving = false;
			}
			else if (m_characterAnimationState == JUMP && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) == 17 && m_isGround)
			{
				m_isMoving = true;
				m_collider->applyJump(m_jumpingSpeed, m_isGround);
				m_isGround = false;
			}

			std::cout << m_isGround << std::endl;
		}
	}

	void Player::updateRunningJump()
	{
		if (m_movementType == GROUND)
		{
			m_isGround = m_collider->performGroundRayCast(m_sprite);
			if (m_isGround == true && (m_characterAnimator->getAbstractAnimation()->getCurrentAnimIndex()) >= 16)
			{
				if (m_characterAnimationState == ANIMATION_STATE::JUMP_RUNNING)
				{
					m_characterAnimationState = ANIMATION_STATE::IDLE;

				}
			}

			if (m_Input.isJump == true && m_characterAnimationState != ANIMATION_STATE::JUMP_RUNNING && m_characterAnimationState != ANIMATION_STATE::JUMP && m_isGround)
			{
				if (m_characterAnimationState == ANIMATION_STATE::MOVING)
				{
					m_characterAnimationState = ANIMATION_STATE::JUMP_RUNNING;
					switchAnimation();
				}
			}

			if (m_characterAnimationState == JUMP_RUNNING && m_isGround)
			{
				m_collider->applyJump(m_jumpingSpeed, m_isGround);
				m_isGround = false;
			}
		}
	}

	void Player::updatePhysics()
	{

		auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
		m_sprite.setPosition(playerPosition);

		b2Vec2 playerBoyPosition = m_collider->getBody()->GetPosition();

		sf::Vector2f playerSpritePosition;
		playerSpritePosition = m_sprite.getPosition();

#ifdef IS_RATCHET_DEBUG
		std::cout << m_sprite.getPosition().x << " , " << m_sprite.getPosition().y;
#endif
		m_rotation = m_collider->getBody()->GetAngle() * (180.f / M_PI);
		m_sprite.setRotation(m_rotation);
	}


	void Player::setIsOnGround(bool isGround)
	{
		m_isGround = isGround;
	}

	void Player::updateInput()
	{

		for (auto& ev : m_playerEvents)
		{
			if (ev.type == sf::Event::KeyPressed)
			{
				if (ev.key.code == sf::Keyboard::A)
				{
					if (m_Input.x >= 0)
					{
						m_Input.x = -1;
					}
#ifdef IS_RATCHET_DEBUG
					std::cout << "Moving POSITION X :" << m_Input.x << std::endl;
#endif
				}
				else if (ev.key.code == sf::Keyboard::D)
				{
					if (m_Input.x <= 0)
					{
						m_Input.x = 1;
					}
#ifdef IS_RATCHET_DEBUG
					std::cout << "Moving POSITION X :" << m_Input.x << std::endl;
#endif
				}

				if (ev.key.code == sf::Keyboard::Space)
				{
					m_Input.isJump = true;
				}
			}
			else if (ev.type == sf::Event::KeyReleased)
			{
				if (ev.key.code == sf::Keyboard::A)
				{
					if (m_Input.x < 0)
					{
						m_Input.x = 0;
					}
				}
				else if (ev.key.code == sf::Keyboard::D)
				{
					if (m_Input.x > 0)
					{
						m_Input.x = 0;
					}
				}

				if (ev.key.code == sf::Keyboard::Space)
				{
					m_Input.isJump = false;
				}
			}

		}
		m_playerEvents.clear();
	}

	Player::~Player() 
	{
	}

#ifdef IS_RATCHET_DEBUG
	void Player::printSpriteColliderPositionPlayer()
	{
		m_collider->printSpriteColliderPosition(m_sprite, DYNAMIC);
	}
#endif
}