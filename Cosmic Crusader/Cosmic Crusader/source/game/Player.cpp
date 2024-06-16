#include "stdafx.h"
#include "Player.h"

namespace ratchet
{
	constexpr float M_PI = 22.0f / 7.0f;

	void Player::destroyPlayerAnimations()
	{
		delete m_animator;
		delete m_animationIdle;
		delete m_animationRun;
		delete m_animationJump;
		delete m_animationJumpRun;
	}

	void Player::destroyPlayerPhysics()
	{
		delete m_collider;
	}

	Player::Player()
	{
		initTexture();
		initVariables();
		initAnimations();
		initSprite();
		initPhysics();
	}

	void Player::initVariables()
	{
		m_userData = new UserData();
		m_userData->type = PLAYER;
		m_playerSpriteScale = sf::Vector2f(1.f, 1.f);
		m_isPLayerEvent = false;
		m_animationState = ANIMATION_STATE::IDLE;
		m_playerAnimSwitch = -1;
		m_moveSpeed = 2.3f;
		m_gravity = 0.090f;
		m_jumpForce = 40.f;
		m_isGround = false;
		m_isJumping = false;
		m_isMoving = false;
		m_isJumpStage = false;
		m_yVelocity = 0.0f;
		m_rotationAngle = 0.f;
	}

	void Player::initTexture()
	{
		if (m_textureSheet.loadFromFile("Textures/PlayerTextures/Player1Textures/IdleTextures/Idle1.png") == false)
		{
#ifdef IS_RATCHET_DEBUG
			std::cout << "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET" << std::endl;
#endif
		}
	}

	void Player::initSprite()
	{
		m_playerSprite.setTexture(m_textureSheet);
		m_playerSprite.setScale(m_playerSpriteScale);
		m_playerSprite.setPosition(200.f, -100.f);
		m_playerSprite.setRotation(m_rotationAngle);
	}

	void Player::initAnimations()
	{
		m_animator = new Animator();
		m_animationIdle = new AnimationIdle();
		m_animationRun = new AnimationRun();
		m_animationJump = new AnimationJump();
		m_animationJumpRun = new AnimationJumpRun();
	}

	void Player::initPhysics()
	{
		m_collider = new RectAngleCollider(m_playerSprite, DYNAMIC, PLAYER);

		b2Vec2 playerBodyPosition = m_collider->getBody()->GetPosition();
		m_collider->setColliderPosition(m_playerSprite.getPosition().x, m_playerSprite.getPosition().y);;
	}

	const sf::FloatRect Player::getBounds() const
	{
		return m_playerSprite.getGlobalBounds();
	}

	sf::Sprite Player::getPlayerSprite()
	{
		return m_playerSprite;
	}

	const sf::Vector2f Player::getPlayerPosition() const
	{
		return m_playerSprite.getPosition();
	}

	sf::Vector2f Player::getPlayerScale()
	{
		return m_playerSprite.getScale();
	}

	bool Player::checkEvent()
	{
		return m_isPLayerEvent;
	}

	void Player::setBoolEvent(bool isEv)
	{
		m_isPLayerEvent = isEv;
	}

	void Player::handleEvent(const sf::Event& ev)
	{
#ifdef IS_RATCHET_DEBUG
		std::cout << ev.type << std::endl;
#endif
		if (ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::A)
			{
#ifdef IS_RATCHET_DEBUG
				std::cout << "Press left" << std::endl;
#endif
				m_controls["left"] = true;

			}
			else if (ev.key.code == sf::Keyboard::D)
			{
				m_controls["right"] = true;
#ifdef IS_RATCHET_DEBUG
				std::cout << "Press right" << std::endl;
#endif
			}

			if (ev.key.code == sf::Keyboard::Space)
			{
				m_controls["jump"] = true;
#ifdef IS_RATCHET_DEBUG
				std::cout << "Press jump" << std::endl;
#endif
			}
		}
		else if (ev.type == sf::Event::KeyReleased)
		{
			if (ev.key.code == sf::Keyboard::A)
			{
#ifdef IS_RATCHET_DEBUG
				std::cout << "Release left" << std::endl;
#endif
				m_controls["left"] = false;

			}
			else if (ev.key.code == sf::Keyboard::D)
			{
				m_controls["right"] = false;
#ifdef IS_RATCHET_DEBUG
				std::cout << "Release right" << std::endl;
#endif
			}

			if (ev.key.code == sf::Keyboard::Space)
			{
				m_controls["jump"] = false;
#ifdef IS_RATCHET_DEBUG
				std::cout << "Release jump" << std::endl;
#endif
			}
		}
	}

	void Player::setPlayerByColliderPos()
	{
	}

	void Player::setPosition(const float x, const float y)
	{
		m_playerSprite.setPosition(x, y);
	}

	void Player::resetControls()
	{
		for (auto& pair : m_controls)
		{
			pair.second = false;
		}
	}

	bool Player::isNoControlActive()
	{
		for (auto& pair : m_controls)
		{
			if (pair.second == true)
			{
				return false;
			}
		}

		return true;
	}

	void Player::update()
	{
		updateMovement();
		updateJump();
		updateRotation();
		updateRunningJump();
		updateAnimations();
		updatePhysics();
	}

	void Player::updateMovement()
	{
		if (m_controls["left"] == true)
		{
			//if (m_isGround)
			{
				if (m_animationState != ANIMATION_STATE::JUMP)
				{

					m_animationState = ANIMATION_STATE::MOVING_LEFT;
					switchAnimation();
					m_isMoving = true;
				}
			}

			invertPlayerMovingSpriteScale(-1);
			if (m_isMoving)
			{
				m_collider->applyMovement(m_moveSpeed, m_controls["left"], -1);
				auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
				m_playerSprite.setPosition(playerPosition);

				// m_playerSprite.move(m_playerPosition.x * -1.f * m_moveSpeed, 0.f);

#ifdef IS_RATCHET_DEBUG
				std::cout << "Moving Left" << std::endl;
#endif
			}
#ifdef IS_RATCHET_DEBUG
			std::cout << "veloctiy x to left = " << getPlayerPosition().x << std::endl;
#endif
		}
		else if (m_controls["right"] == true)
		{
			//if (m_isGround)
			{
				if (m_animationState != ANIMATION_STATE::JUMP)
				{
					m_animationState = ANIMATION_STATE::MOVING_RIGHT;
					switchAnimation();
					m_isMoving = true;
				}
			}

			invertPlayerMovingSpriteScale(1);
			if (m_isMoving)
			{
				m_collider->applyMovement(m_moveSpeed, m_controls["right"], 1);
				auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
				m_playerSprite.setPosition(playerPosition);
				// m_playerSprite.move(m_playerPosition.x * m_moveSpeed, 0.f);
#ifdef IS_RATCHET_DEBUG
				std::cout << "Moving Right" << std::endl;
#endif
			}
#ifdef IS_RATCHET_DEBUG
			std::cout << "veloctiy x to right = " << getPlayerPosition().x << std::endl;
#endif
		}

		if (isNoControlActive() && m_animationState != ANIMATION_STATE::JUMP && m_animationState != ANIMATION_STATE::JUMP_RUNNING)
		{
#ifdef IS_RATCHET_DEBUG
			std::cout << "Idle" << std::endl;
			std::cout << m_animationState << std::endl;
#endif
			m_animationState = ANIMATION_STATE::IDLE;
			m_isMoving = false;
			switchAnimation();
		}

	}

	void Player::updateRotation()
	{
		m_playerSprite.rotate(m_rotationAngle);
	}

	void Player::updateJump()
	{
		m_isGround = m_collider->performGroundRayCast(m_playerSprite);

#ifdef IS_RATCHET_DEBUG
		std::cout << "IS GROUND GROUND " << m_isGround << std::endl;
#endif

		if (m_isGround == true && (m_animator->getAbstractAnimation()->getCurrentAnimIndex()) > 17)
		{
			if (m_animationState == ANIMATION_STATE::JUMP)
			{
				m_animationState = ANIMATION_STATE::IDLE;
			}
		}

		if (m_controls["jump"] == true && m_animationState != ANIMATION_STATE::JUMP && m_animationState != ANIMATION_STATE::JUMP_RUNNING && m_isGround)
		{
			if (m_animationState == ANIMATION_STATE::IDLE)
			{
				m_animationState = ANIMATION_STATE::JUMP;
				switchAnimation();
			}
		}

		if ((m_animator->getAbstractAnimation()->getCurrentAnimIndex()) < 17 && m_animationState == ANIMATION_STATE::JUMP)
		{
			m_isMoving = false;
		}
		else if ((m_animator->getAbstractAnimation()->getCurrentAnimIndex()) == 17 && m_animationState == ANIMATION_STATE::JUMP && m_isGround)
		{

			m_isMoving = true;
			m_collider->applyJump(m_jumpForce, m_isGround);
#ifdef IS_RATCHET_DEBUG
			std::cout << "JUMP JUMP " << std::endl;
#endif
			//m_isGround = false;


		}
		//m_playerSprite.move(0.f, m_yVelocity);

	}

	void Player::updateRunningJump()
	{
		m_isGround = m_collider->performGroundRayCast(m_playerSprite);

		if (m_isGround == true && (m_animator->getAbstractAnimation()->getCurrentAnimIndex()) >= 16)
		{
			if (m_animationState == ANIMATION_STATE::JUMP_RUNNING)
			{
				m_animationState = ANIMATION_STATE::IDLE;

			}
			m_yVelocity = 0.f;
		}
		else
		{
			m_yVelocity += m_gravity;
		}



		if (m_controls["jump"] == true && m_animationState != ANIMATION_STATE::JUMP_RUNNING && m_animationState != ANIMATION_STATE::JUMP && m_isGround)
		{
			if (m_animationState == ANIMATION_STATE::MOVING_LEFT || m_animationState == ANIMATION_STATE::MOVING_RIGHT)
			{
				m_animationState = ANIMATION_STATE::JUMP_RUNNING;
				switchAnimation();
			}


		}

		if (m_animationState == ANIMATION_STATE::JUMP_RUNNING && m_isGround)
		{

			m_collider->applyJump(m_jumpForce, m_isGround);
#ifdef IS_RATCHET_DEBUG
			std::cout << "JUMP JUMP " << std::endl;
#endif
			//m_isGround = false;
		}

		//m_playerSprite.move(0.f, m_yVelocity);

	}


	void Player::updateAnimations()
	{
		m_animator->play(m_animator->getAbstractAnimation(), m_playerSprite);
	}

	void Player::updatePhysics()
	{

		auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
		m_playerSprite.setPosition(playerPosition);

		b2Vec2 playerBoyPosition = m_collider->getBody()->GetPosition();

		sf::Vector2f playerSpritePosition;
		playerSpritePosition = m_playerSprite.getPosition();

#ifdef IS_RATCHET_DEBUG
		std::cout << m_playerSprite.getPosition().x << " , " << m_playerSprite.getPosition().y;
#endif
		m_rotationAngle = m_collider->getBody()->GetAngle() * (180.f / M_PI);
		m_playerSprite.setRotation(m_rotationAngle);
	}


	void Player::setIsOnGround(bool isGround)
	{
		m_isGround = isGround;
	}

	void Player::invertPlayerMovingSpriteScale(int direction)
	{
		m_playerSprite.setScale(m_playerSpriteScale.x * (float)direction, m_playerSpriteScale.y);
		if (direction < 0)
		{
			m_playerSprite.setOrigin(getBounds().width / m_playerSpriteScale.x, 0.f);
		}
		else
		{
			m_playerSprite.setOrigin(0.f, 0.f);
		}
	}

	void Player::switchAnimation()
	{
		if (m_animationState != m_playerAnimSwitch) {

			//	aplica modificare
			switch (m_animationState)
			{
			case ANIMATION_STATE::IDLE:
#ifdef IS_RATCHET_DEBUG
				std::cout << "Player Runs idle Animation" << std::endl;
#endif
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				m_animator->setAnimation(m_animationIdle);
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				break;


			case ANIMATION_STATE::MOVING_LEFT:
#ifdef IS_RATCHET_DEBUG
				std::cout << "Player Runs left Animation" << std::endl;
#endif
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				m_animator->setAnimation(m_animationRun);
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				break;

			case ANIMATION_STATE::MOVING_RIGHT:
#ifdef IS_RATCHET_DEBUG
				std::cout << "Player Runs right Animation" << std::endl;
#endif
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				m_animator->setAnimation(m_animationRun);
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				break;
			case ANIMATION_STATE::JUMP:
#ifdef IS_RATCHET_DEBUG
				std::cout << "Player Jump Animation" << std::endl;
#endif
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				m_animator->setAnimation(m_animationJump);
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				break;
			case ANIMATION_STATE::JUMP_RUNNING:
#ifdef IS_RATCHET_DEBUG
				std::cout << "Player Jump Animation" << std::endl;
#endif
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				m_animator->setAnimation(m_animationJumpRun);
				m_animator->resetAnimationTimer(m_animator->getAbstractAnimation());
				m_animator->resetAnimIndex(m_animator->getAbstractAnimation());
				break;

			default:
				break;
			}
			// salveaza stare curenta in stare anterioara
			m_playerAnimSwitch = m_animationState;
		}
	}

	bool Player::isJumping()
	{
		if (m_animationState == ANIMATION_STATE::JUMP || m_animationState == ANIMATION_STATE::JUMP_RUNNING)
		{
			return true;
		}

		return false;
	}

	void Player::render(sf::RenderTarget& target)
	{
#ifdef IS_RATCHET_DEBUG
		m_collider->debugRender(target);

		// DRAW SPRITE BOUNDS
		auto spriteOutline = sf::RectangleShape(sf::Vector2f(
			m_playerSprite.getGlobalBounds().width,
			m_playerSprite.getGlobalBounds().height)
		);
		spriteOutline.setFillColor(sf::Color::Transparent);
		spriteOutline.setOutlineColor(sf::Color::Red);
		spriteOutline.setOutlineThickness(1.0f);
		spriteOutline.setPosition(
			m_playerSprite.getPosition().x,
			m_playerSprite.getPosition().y);
		target.draw(spriteOutline);
#endif

		target.draw(m_playerSprite);
	}

	Player::~Player()
	{
		destroyPlayerAnimations();
		destroyPlayerPhysics();
		delete m_userData;
	}

#ifdef IS_RATCHET_DEBUG
	void Player::printSpriteColliderPositionPlayer()
	{
		m_collider->printSpriteColliderPosition(m_playerSprite, DYNAMIC);
	}
#endif
}