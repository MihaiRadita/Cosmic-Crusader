#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

void Player::initVariables()
{
	this->playerPosition = sf::Vector2f(1.f, 1.f);
	this->IsPLayerEvent = false;
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;
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
	this->sprite.setScale(0.05f, 0.05f);
}

void Player::initAnimations()
{
}

void Player::initIdleAnimation()
{
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

void Player::SetBOOLEvent(bool isEv)
{
	this->IsPLayerEvent = isEv;
}

void Player::handleEvent(const sf::Event& ev)
{
	std::cout << ev.type<<std::endl;
	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::A)
		{
			std::cout << "Press left"<<std::endl;
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
	this->updateInput();
	this->updateMovement();
	this->updateJump();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::updateInput()
{
	
	
}

void Player::updateMovement()
{
	if (this->controls["left"] == true)
	{
		if (this->animationState != PLAYER_ANIMATION_STATES::MOVING_LEFT)
		{
			this->animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
		}
		this->sprite.move(this->playerPosition.x * -1.f * this->moveSpeed, 0.f);
		std::cout << "Moving Left" << std::endl;
		std::cout << "veloctiy x to left = " << this->getPlayerPosition().x << std::endl;
	}
	else if (this->controls["right"] == true)
	{
		if (this->animationState != PLAYER_ANIMATION_STATES::MOVING_RIGHT)
		{
			this->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;

		}
			this->sprite.move(this->playerPosition.x  * this->moveSpeed, 0.f);
			std::cout << "Moving Right" << std::endl;
			std::cout << "veloctiy x to right = " << this->getPlayerPosition().x << std::endl;
	}


	if (this->isAnyControlActive())
	{
		std::cout << "Idle"<<std::endl;
		std::cout << this->animationState << std::endl;
		if (this->animationState != PLAYER_ANIMATION_STATES::IDLE)
		{
			this->animationState = PLAYER_ANIMATION_STATES::IDLE;
		}
	}
	
}

void Player::updateAnimations()
{
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
		this->animationState = PLAYER_ANIMATION_STATES::IDLE;
	}
	else
	{
		this->yVelocity += this->gravity;
		std::cout << "veloctiy y = " << this->yVelocity << std::endl;
	}

  	if (this->controls["jump"] == true && this->isGround == true)
	{
		if (this->animationState != PLAYER_ANIMATION_STATES::JUMP && !this->isJumping)
		{
			this->isJumping = true;
			this->animationState = PLAYER_ANIMATION_STATES::JUMP;
			this->yVelocity = -jumpSpeed;
			std::cout << "Y velocity = " << this->yVelocity << std::endl;
			std::cout<<"naimtion state = " << this->animationState << std::endl;
		}

		this->isGround = false;
	}
	this->sprite.move(0.f, this->yVelocity);
}

void Player::setIsOnGround(bool isGround)
{
	this->isGround = isGround;
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
