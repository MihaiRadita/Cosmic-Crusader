#include "stdafx.h"
#include "Player.h"
void Player::DestroyPlayerAnimations()
{
	delete this->playerAnimator;
	delete this->playerIdleAnimation;
	delete this->playerRunningAnimation;
	delete this->playerJumpAnimation;
	delete this->playerJumpRunningAnimation;
}

void Player::DestroyPlayerPhysics()
{
	this->playerCollider = nullptr;
	delete this->playerCollider;
}

Player::Player()
{
	this->initTexture();
	this->initVariables();
	this->initAnimations();
	this->initSprite();
	this->initPhysics();
}

void Player::initVariables()
{
	this->playerPosition = sf::Vector2f(1.f, 1.f);
	this->playerSpriteScale = sf::Vector2f(1.f, 1.f);
	this->IsPLayerEvent = false;
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;
	this->playerAnimSwitch = -1;
	this->moveSpeed = 2.3f;
	this->gravity = 0.090f;
	this->jumpForce = 9.f;
	this->isGround = false;
	this->isJumping = false;
	this->isMoving = false;
	this->isJumpStage = false;
	this->yVelocity = 0.0f;
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
	this->playerSprite.setTexture(this->textureSheet);
	this->playerSprite.setScale(this->playerSpriteScale);
}

void Player::initAnimations()
{
	this->playerAnimator = new Animator();
	this->playerIdleAnimation = new PlayerIdleAnimation();
	this->playerRunningAnimation = new PlayerRunningAnimation();
	this->playerJumpAnimation = new PlayerJumpAnimation();
	this->playerJumpRunningAnimation = new PlayerJumpRunningAnimation();
}

void Player::initPhysics()
{
	this->playerCollider = new RectAngleCollider(this->playerSprite, DYNAMIC);
}

const sf::FloatRect Player::getBounds() const
{
	return this->playerSprite.getGlobalBounds();
}

sf::Sprite Player::GetPlayerSprite()
{
	return this->playerSprite;
}

const sf::Vector2f Player::getPlayerPosition() const
{
	return this->playerSprite.getPosition();
}

sf::Vector2f Player::getPlayerScale()
{
	return this->playerSprite.getScale();
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

void Player::SetPlayerByColliderPos()
{
}

void Player::SetPosition(const float x, const float y)
{
	this->playerSprite.setPosition(x, y);
}

void Player::resetControls()
{
	for (auto& pair : this->controls)
	{
		pair.second = false;
	}
}

bool Player::isNoControlActive()
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
	this->updateRunningJump();
	this->updateAnimations();
	//this->updatePhysics();
}

void Player::updateMovement()
{
	if (this->controls["left"] == true)
	{
		if (this->isGround)
		{
			if (this->animationState != PLAYER_ANIMATION_STATES::JUMP)
			{

				this->animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
				this->SwitchAnimation();
				this->isMoving = true;
			}
		}

		this->InvertPlayerMovingSpriteScale(-1);
		if (this->isMoving)
		{
			this->playerSprite.move(this->playerPosition.x * -1.f * this->moveSpeed, 0.f);

		}
		std::cout << "Moving Left" << std::endl;
		std::cout << "veloctiy x to left = " << this->getPlayerPosition().x << std::endl;
	}
	else if (this->controls["right"] == true)
	{
		if (this->isGround)
		{
			if (this->animationState != PLAYER_ANIMATION_STATES::JUMP)
			{
				this->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
				this->SwitchAnimation();
				this->isMoving = true;
			}
		}

		this->InvertPlayerMovingSpriteScale(1);
		if (this->isMoving)
		{
			this->playerSprite.move(this->playerPosition.x * this->moveSpeed, 0.f);
		}
		std::cout << "Moving Right" << std::endl;
		std::cout << "veloctiy x to right = " << this->getPlayerPosition().x << std::endl;
	}

	if (this->isNoControlActive() && this->animationState != PLAYER_ANIMATION_STATES::JUMP && this->animationState != PLAYER_ANIMATION_STATES::JUMP_RUNNING)
	{
		std::cout << "Idle" << std::endl;
		std::cout << this->animationState << std::endl;
		this->animationState = PLAYER_ANIMATION_STATES::IDLE;
		this->isMoving = false;
		this->SwitchAnimation();
	}

}

void Player::updateJump()
{

	if (this->isGround == true && (this->playerAnimator->GetAbstractAnimation()->GetCurrentAnimIndex()) > 17)
	{
		if (this->animationState == PLAYER_ANIMATION_STATES::JUMP)
		{
			this->animationState = PLAYER_ANIMATION_STATES::IDLE;
		}
		this->yVelocity = 0.f;
	}
	else
	{
		this->yVelocity += this->gravity;	
	}

	if (this->controls["jump"] == true && this->animationState != PLAYER_ANIMATION_STATES::JUMP && this->animationState != PLAYER_ANIMATION_STATES::JUMP_RUNNING && this->isGround)
	{
		if (this->animationState == PLAYER_ANIMATION_STATES::IDLE)
		{
			this->animationState = PLAYER_ANIMATION_STATES::JUMP;
			this->SwitchAnimation();
		}
	}

	if ((this->playerAnimator->GetAbstractAnimation()->GetCurrentAnimIndex()) < 17 && this->animationState == PLAYER_ANIMATION_STATES::JUMP)
	{
		this->isMoving = false;
		this->yVelocity = 0;
	}
	else if ((this->playerAnimator->GetAbstractAnimation()->GetCurrentAnimIndex()) == 17 && this->animationState == PLAYER_ANIMATION_STATES::JUMP && this->isGround)
	{
		
		this->isMoving = true;
		this->yVelocity = -jumpForce;
		std::cout << "JUMP JUMP " << std::endl;
		this->isGround = false;
		
		
	}
 	this->playerSprite.move(0.f, this->yVelocity);

}

void Player::updateRunningJump()
{
	if (this->isGround == true && (this->playerAnimator->GetAbstractAnimation()->GetCurrentAnimIndex()) >= 16)
	{
		if (this->animationState == PLAYER_ANIMATION_STATES::JUMP_RUNNING)
		{
			this->animationState = PLAYER_ANIMATION_STATES::IDLE;
	
		}
		this->yVelocity = 0.f;
	}
	else
	{
		this->yVelocity += gravity;
	}
	
	
	
	if (this->controls["jump"] == true && this->animationState != PLAYER_ANIMATION_STATES::JUMP_RUNNING && this->animationState != PLAYER_ANIMATION_STATES::JUMP && this->isGround)
	{
		if (this->animationState == PLAYER_ANIMATION_STATES::MOVING_LEFT || this->animationState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
		{
			this->animationState = PLAYER_ANIMATION_STATES::JUMP_RUNNING;
			this->SwitchAnimation();
		}
		
			
	}
	
	if (this->animationState == PLAYER_ANIMATION_STATES::JUMP_RUNNING && this->isGround)
	{
			
		this->yVelocity = -jumpForce;
		std::cout << "JUMP JUMP " << std::endl;
		this->isGround = false;
	}

	this->playerSprite.move(0.f, this->yVelocity);

}


void Player::updateAnimations()
{
	this->playerAnimator->Play(this->playerAnimator->GetAbstractAnimation(), this->playerSprite);
}

void Player::updatePhysics()
{
	this->playerPosition = sf::Vector2f(this->playerCollider->GetBody()->GetPosition().x, this->playerCollider->GetBody()->GetPosition().y);
}


void Player::setIsOnGround(bool isGround)
{
	this->isGround = isGround;
}

void Player::InvertPlayerMovingSpriteScale(int direction)
{
	this->playerSprite.setScale(this->playerSpriteScale.x * (float)direction, this->playerSpriteScale.y);
	if (direction < 0)
	{
		this->playerSprite.setOrigin(this->getBounds().width / this->playerSpriteScale.x, 0.f);
	}
	else
	{
		this->playerSprite.setOrigin(0.f, 0.f);
	}
}

void Player::SwitchAnimation()
{
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
		case PLAYER_ANIMATION_STATES::JUMP_RUNNING:
			std::cout << "Player Jump Animation" << std::endl;
			this->playerAnimator->ResetAnimationTimer(playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			this->playerAnimator->SetAnimation(this->playerJumpRunningAnimation);
			this->playerAnimator->ResetAnimationTimer(playerAnimator->GetAbstractAnimation());
			this->playerAnimator->ResetAnimIndex(this->playerAnimator->GetAbstractAnimation());
			break;

		default:
			break;
		}
		// salveaza stare curenta in stare anterioara
		this->playerAnimSwitch = this->animationState;
	}
}

bool Player::IsJumping()
{
	if (this->animationState == PLAYER_ANIMATION_STATES::JUMP || this->animationState == PLAYER_ANIMATION_STATES::JUMP_RUNNING)
	{
		return true;
	}
	
	return false;
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}

Player::~Player()
{
	this->DestroyPlayerAnimations();
	this->DestroyPlayerPhysics();
}


