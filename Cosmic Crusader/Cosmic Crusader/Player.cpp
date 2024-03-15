#include "stdafx.h"
#include "Player.h"

void Player::DestroyPlayerAnimations()
{
	delete this->playerAnimator;
	delete this->playerIdleAnimation;
	delete this->playerRunningAnimation;
	delete this->playerJumpAnimation;
}

Player::Player()
{
	this->initTexture();
	this->initVariables();
	this->initAnimations();
	this->initSprite();
}

void Player::initVariables()
{
	this->playerPosition = sf::Vector2f(1.f, 1.f);
	this->playerSpriteScale = sf::Vector2f(1.f, 1.f);
	this->IsPLayerEvent = false;
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;
	this->playerAnimSwitch = -1;

	//this->playerAnimator->SetAnimation(this->playerIdelAnimation);

	//this->updateAnimations();

	this->moveSpeed = 2.3f;
	this->gravity = 1.2f;


	this->isGround = false;
	this->isJumping = false;
	this->yVelocity = 0.0f;
	this->jumpSpeed = 30.7f;
}

void Player::initTexture()
{
	if (this->textureSheet.loadFromFile("Textures/PlayerTextures/Player1Textures/IdleTextures/Idle1.png") == false)
	{
		std::cout << "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET" << std::endl;
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->sprite.setScale(this->playerSpriteScale);
}

void Player::initAnimations()
{
	this->playerAnimator = new Animator();
	this->playerIdleAnimation = new PlayerIdleAnimation();
	this->playerRunningAnimation = new PlayerRunningAnimation();
	this->playerJumpAnimation = new PlayerJumpAnimation();
}

void Player::initPhysics()
{
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

sf::Sprite Player::GetPlayerSprite()
{
	return this->sprite;
}

const sf::Vector2f Player::getPlayerPosition() const
{
	return this->sprite.getPosition();
}

sf::Vector2f Player::getPlayerScale()
{
	return this->sprite.getScale();
}

bool Player::CheckEvent()
{
	return this->IsPLayerEvent;
}

void Player::SetBoolEvent(bool isEv)
{
	this->IsPLayerEvent = isEv;
}

void Player::handleEvent(const sf::Event& ev)
{
	std::cout << ev.type << std::endl;
	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::A)
		{
			std::cout << "Press left" << std::endl;
			controls["left"] = true;

		}
		else if (ev.key.code == sf::Keyboard::D)
		{
			controls["right"] = true;
			std::cout << "Press right" << std::endl;
		}

		if (ev.key.code == sf::Keyboard::Space)
		{
			controls["jump"] = true;
			std::cout << "Press jump" << std::endl;
		}
	}
	else if (ev.type == sf::Event::KeyReleased)
	{
		if (ev.key.code == sf::Keyboard::A)
		{
			std::cout << "Release left" << std::endl;
			controls["left"] = false;

		}
		else if (ev.key.code == sf::Keyboard::D)
		{
			controls["right"] = false;
			std::cout << "Release right" << std::endl;
		}

		if (ev.key.code == sf::Keyboard::Space)
		{
			controls["jump"] = false;
			std::cout << "Release jump" << std::endl;
		}
	}
}

void Player::SetPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetControls()
{
	for (auto& pair : this->controls)
	{
		pair.second = false;
	}
}

bool Player::isAnyControlActive()
{
	for (auto& pair : this->controls)
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
	this->updateMovement();
	this->updateJump();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::updateMovement()
{
	if (this->controls["left"] == true)
	{
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
		this->InvertPlayerMovingSpriteScale(-1);
		this->sprite.move(this->playerPosition.x * -1.f * this->moveSpeed, 0.f);
		std::cout << "Moving Left" << std::endl;
		std::cout << "veloctiy x to left = " << this->getPlayerPosition().x << std::endl;
	}
	else if (this->controls["right"] == true)
	{
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		this->InvertPlayerMovingSpriteScale(1);
		this->sprite.move(this->playerPosition.x * this->moveSpeed, 0.f);
		std::cout << "Moving Right" << std::endl;
		std::cout << "veloctiy x to right = " << this->getPlayerPosition().x << std::endl;
	}


	if (this->isAnyControlActive() && this->isGround)
	{
		std::cout << "Idle" << std::endl;
		std::cout << this->animationState << std::endl;
		this->animationState = PLAYER_ANIMATION_STATES::IDLE;
	}

}

void Player::updateAnimations()
{

	//std::cout << "Player Runs: " << this->animationState  << std::endl;
	//daca starea curenta != starea anterioara
	if (this->animationState != this->playerAnimSwitch) {

		//	aplica modificare
		switch (this->animationState)
		{
		case PLAYER_ANIMATION_STATES::IDLE:

			std::cout << "Player Runs idle Animation" << std::endl;
			this->playerAnimator->ResetAnimationTimer(playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			this->playerAnimator->SetAnimation(this->playerIdleAnimation);
			this->playerAnimator->ResetAnimationTimer(playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			break;


		case PLAYER_ANIMATION_STATES::MOVING_LEFT:
			std::cout << "Player Runs left Animation" << std::endl;
			this->playerAnimator->ResetAnimationTimer(this->playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			this->playerAnimator->SetAnimation(this->playerRunningAnimation);
			this->playerAnimator->ResetAnimationTimer(playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			break;

		case PLAYER_ANIMATION_STATES::MOVING_RIGHT:
			std::cout << "Player Runs right Animation" << std::endl;
			this->playerAnimator->ResetAnimationTimer(playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			this->playerAnimator->SetAnimation(this->playerRunningAnimation);
			this->playerAnimator->ResetAnimationTimer(playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			break;
		case PLAYER_ANIMATION_STATES::JUMP:
			std::cout << "Player Jump Animation" << std::endl;
			this->playerAnimator->ResetAnimationTimer(playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			this->playerAnimator->SetAnimation(this->playerJumpAnimation);
			this->playerAnimator->ResetAnimationTimer(playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			
			break;

		default:
			break;
		}
		// salveaza stare curenta in stare anterioara
		this->playerAnimSwitch = this->animationState;
	}

	this->playerAnimator->Play(this->playerAnimator->GetAbstractAnimation(), this->sprite);

}

void Player::updatePhysics()
{
}

void Player::updateJump()
{
	if (this->isGround == true)
	{
		this->isJumping = false;
		this->yVelocity = 0.f;
		//std::cout << "veloctiy y = " << this->yVelocity << std::endl;
		//this->animationState = PLAYER_ANIMATION_STATES::IDLE;
	}
	else
	{
		this->yVelocity += this->gravity;
		std::cout << "veloctiy y = " << this->yVelocity << std::endl;
	}

	if (this->controls["jump"] == true)
	{
		if (this->animationState != PLAYER_ANIMATION_STATES::JUMP && !this->isJumping)
		{
			this->isJumping = true;
			this->animationState = PLAYER_ANIMATION_STATES::JUMP;
			this->yVelocity = -jumpSpeed;
			std::cout << "Y velocity = " << this->yVelocity << std::endl;
			std::cout << "naimtion state = " << this->animationState << std::endl;
		}
		this->isGround = false;

	}
	this->sprite.move(0.f, this->yVelocity);
}

void Player::setIsOnGround(bool isGround)
{
	this->isGround = isGround;
}

void Player::InvertPlayerMovingSpriteScale(int direction)
{
	this->sprite.setScale(this->playerSpriteScale.x * (float)direction, this->playerSpriteScale.y);
	if (direction < 0)
	{
		this->sprite.setOrigin(this->getBounds().width / this->playerSpriteScale.x, 0.f);
	}
	else
	{
		this->sprite.setOrigin(0.f, 0.f);
	}
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

Player::~Player()
{
	this->DestroyPlayerAnimations();
}


