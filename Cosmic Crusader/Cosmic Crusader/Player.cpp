#include "stdafx.h"
#include "Player.h"

constexpr float M_PI = 22.0f / 7.0f;

void Player::destroyPlayerAnimations()
{
	delete m_playerAnimator;
	delete m_playerIdleAnimation;
	delete m_playerRunningAnimation;
	delete m_playerJumpAnimation;
	delete m_playerJumpRunningAnimation;
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
	m_animationState = PLAYER_ANIMATION_STATES::IDLE;
	m_playerAnimSwitch = -1;
	m_moveSpeed = 2.3f;
	m_gravity = 0.090f;
	m_jumpForce = 9.f;
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
		std::cout << "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET" << std::endl;
	}
}

void Player::initSprite()
{
	m_playerSprite.setTexture(m_textureSheet);
	m_playerSprite.setScale(m_playerSpriteScale);
	m_playerSprite.setPosition(300.f,40.f);
	m_playerSprite.setRotation(m_rotationAngle);
}

void Player::initAnimations()
{
	m_playerAnimator = new Animator();
	m_playerIdleAnimation = new PlayerIdleAnimation();
	m_playerRunningAnimation = new PlayerRunningAnimation();
	m_playerJumpAnimation = new PlayerJumpAnimation();
	m_playerJumpRunningAnimation = new PlayerJumpRunningAnimation();
}

void Player::initPhysics()
{
	m_collider = new RectAngleCollider(m_playerSprite, DYNAMIC);
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
	std::cout << ev.type << std::endl;
	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::A)
		{
			std::cout << "Press left" << std::endl;
			m_controls["left"] = true;

		}
		else if (ev.key.code == sf::Keyboard::D)
		{
			m_controls["right"] = true;
			std::cout << "Press right" << std::endl;
		}

		if (ev.key.code == sf::Keyboard::Space)
		{
			m_controls["jump"] = true;
			std::cout << "Press jump" << std::endl;
		}
	}
	else if (ev.type == sf::Event::KeyReleased)
	{
		if (ev.key.code == sf::Keyboard::A)
		{
			std::cout << "Release left" << std::endl;
			m_controls["left"] = false;

		}
		else if (ev.key.code == sf::Keyboard::D)
		{
			m_controls["right"] = false;
			std::cout << "Release right" << std::endl;
		}

		if (ev.key.code == sf::Keyboard::Space)
		{
			m_controls["jump"] = false;
			std::cout << "Release jump" << std::endl;
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
			if (m_animationState != PLAYER_ANIMATION_STATES::JUMP)
			{

				m_animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
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

			std::cout << "Moving Left" << std::endl;
		}
		std::cout << "veloctiy x to left = " << getPlayerPosition().x << std::endl;
	}
	else if (m_controls["right"] == true)
	{
		//if (m_isGround)
		{
			if (m_animationState != PLAYER_ANIMATION_STATES::JUMP)
			{
				m_animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
				switchAnimation();
				m_isMoving = true;
			}
		}

		invertPlayerMovingSpriteScale(1);
		if (m_isMoving)
		{
			m_collider->applyMovement(m_moveSpeed , m_controls["right"], 1);
			auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
			m_playerSprite.setPosition(playerPosition);
			// m_playerSprite.move(m_playerPosition.x * m_moveSpeed, 0.f);
			std::cout << "Moving Right" << std::endl;
		}
		std::cout << "veloctiy x to right = " << getPlayerPosition().x << std::endl;
	}

	if (isNoControlActive() && m_animationState != PLAYER_ANIMATION_STATES::JUMP && m_animationState != PLAYER_ANIMATION_STATES::JUMP_RUNNING)
	{

		std::cout << "Idle" << std::endl;
		std::cout << m_animationState << std::endl;
		m_animationState = PLAYER_ANIMATION_STATES::IDLE;
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
	m_isGround = m_collider->m_contactListener->isPlayerOnGround;

	std::cout << "IS GROUND GROUND " << m_isGround<<std::endl;

	if (m_isGround == true && (m_playerAnimator->getAbstractAnimation()->getCurrentAnimIndex()) > 17)
	{
		if (m_animationState == PLAYER_ANIMATION_STATES::JUMP)
		{
			m_animationState = PLAYER_ANIMATION_STATES::IDLE;
		}
	}

	if (m_controls["jump"] == true && m_animationState != PLAYER_ANIMATION_STATES::JUMP && m_animationState != PLAYER_ANIMATION_STATES::JUMP_RUNNING && m_isGround)
	{
		if (m_animationState == PLAYER_ANIMATION_STATES::IDLE)
		{
			m_animationState = PLAYER_ANIMATION_STATES::JUMP;
			switchAnimation();
		}
	}

	if ((m_playerAnimator->getAbstractAnimation()->getCurrentAnimIndex()) < 17 && m_animationState == PLAYER_ANIMATION_STATES::JUMP)
	{
		m_isMoving = false;
	}
	else if ((m_playerAnimator->getAbstractAnimation()->getCurrentAnimIndex()) == 17 && m_animationState == PLAYER_ANIMATION_STATES::JUMP && m_isGround)
	{
		
		m_isMoving = true;
		m_collider->applyJump(m_jumpForce, m_isGround);
		std::cout << "JUMP JUMP " << std::endl;
		m_isGround = false;
		
		
	}
 	//m_playerSprite.move(0.f, m_yVelocity);

}

void Player::updateRunningJump()
{
	if (m_isGround == true && (m_playerAnimator->getAbstractAnimation()->getCurrentAnimIndex()) >= 16)
	{
		if (m_animationState == PLAYER_ANIMATION_STATES::JUMP_RUNNING)
		{
			m_animationState = PLAYER_ANIMATION_STATES::IDLE;
	
		}
		m_yVelocity = 0.f;
	}
	else
	{
		m_yVelocity += m_gravity;
	}
	
	
	
	if (m_controls["jump"] == true && m_animationState != PLAYER_ANIMATION_STATES::JUMP_RUNNING && m_animationState != PLAYER_ANIMATION_STATES::JUMP && m_isGround)
	{
		if (m_animationState == PLAYER_ANIMATION_STATES::MOVING_LEFT || m_animationState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
		{
			m_animationState = PLAYER_ANIMATION_STATES::JUMP_RUNNING;
			switchAnimation();
		}
		
			
	}
	
	if (m_animationState == PLAYER_ANIMATION_STATES::JUMP_RUNNING && m_isGround)
	{
			
		m_yVelocity = -m_jumpForce;
		std::cout << "JUMP JUMP " << std::endl;
		m_isGround = false;
	}

	m_playerSprite.move(0.f, m_yVelocity);

}


void Player::updateAnimations()
{
	m_playerAnimator->play(m_playerAnimator->getAbstractAnimation(), m_playerSprite);
}

void Player::updatePhysics()
{

	auto playerPosition = sf::Vector2f(m_collider->getBody()->GetPosition().x, m_collider->getBody()->GetPosition().y);
	m_playerSprite.setPosition(playerPosition);

	std::cout << m_playerSprite.getPosition().x << " , " << m_playerSprite.getPosition().y;
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
		case PLAYER_ANIMATION_STATES::IDLE:

			std::cout << "Player Runs idle Animation" << std::endl;
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->setAnimation(m_playerIdleAnimation);
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
			break;


		case PLAYER_ANIMATION_STATES::MOVING_LEFT:
			std::cout << "Player Runs left Animation" << std::endl;
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->setAnimation(m_playerRunningAnimation);
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
			break;

		case PLAYER_ANIMATION_STATES::MOVING_RIGHT:
			std::cout << "Player Runs right Animation" << std::endl;
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->setAnimation(m_playerRunningAnimation);
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
			break;
		case PLAYER_ANIMATION_STATES::JUMP:
			std::cout << "Player Jump Animation" << std::endl;
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->setAnimation(m_playerJumpAnimation);
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
			break;
		case PLAYER_ANIMATION_STATES::JUMP_RUNNING:
			std::cout << "Player Jump Animation" << std::endl;
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->setAnimation(m_playerJumpRunningAnimation);
			m_playerAnimator->resetAnimationTimer(m_playerAnimator->getAbstractAnimation());
			m_playerAnimator->resetAnimIndex(m_playerAnimator->getAbstractAnimation());
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
	if (m_animationState == PLAYER_ANIMATION_STATES::JUMP || m_animationState == PLAYER_ANIMATION_STATES::JUMP_RUNNING)
	{
		return true;
	}
	
	return false;
}

void Player::render(sf::RenderTarget& target)
{
	// DEBUG
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
	// DEBUG END

	target.draw(m_playerSprite);
}

Player::~Player()
{
	destroyPlayerAnimations();
	destroyPlayerPhysics();
	delete m_userData;
}

void Player::printSpriteColliderPositionPlayer()
{
	m_collider->printSpriteColliderPosition(m_playerSprite, DYNAMIC);
}


