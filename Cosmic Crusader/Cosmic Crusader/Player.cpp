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
	this->IsPLayerEvent = false;
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;
	this->playerSpeed = 1.87f;
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
	this, sprite.setScale(0.05f, 0.05f);
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
	return sf::Sprite();
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
			std::cout << "Sebi left"<<std::endl;
			controls["left"] = true;
			
		}
		else if (ev.key.code == sf::Keyboard::D)
		{
			controls["right"] = true;
		}
		
		if (ev.key.code == sf::Keyboard::W)
		{
			/*this->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
			std::cout << "Moving Right" << std::endl;*/
			controls["up"] = true;
		}
		else if (ev.key.code == sf::Keyboard::S)
		{
			controls["down"] = true;
		}

		/*else
		{

			this->animationState = PLAYER_ANIMATION_STATES::IDLE;
			std::cout << "Idle";
		}*/
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
		if (pair.second == false)
		{
			return true;
		}
	}

	return false;
}

void Player::update()
{
	this->updateInput();
	this->updateMovement();
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
		this->sprite.move(sf::Vector2f(-1.f, 0.f) * this->playerSpeed);
		std::cout << "Moving Left" << std::endl;
	}
	else if (this->controls["right"] == true)
	{
		if (this->animationState != PLAYER_ANIMATION_STATES::MOVING_RIGHT)
		{
			this->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;

		}
			this->sprite.move(sf::Vector2f(1.f, 0.f) * this->playerSpeed);
			std::cout << "Moving Left" << std::endl;
	}
	if (this->controls["up"] == true)
	{
		if (this->animationState != PLAYER_ANIMATION_STATES::MOVING_UP)
		{
			this->animationState = PLAYER_ANIMATION_STATES::MOVING_UP;
		}
			std::cout << "Moving Up" << std::endl;
			this->sprite.move(sf::Vector2f(0.f, -1.f) * this->playerSpeed);
	}

	else if (this->controls["down"] == true)
	{
		if (this->animationState != PLAYER_ANIMATION_STATES::MOVING_DOWN)
		{
			this->animationState = PLAYER_ANIMATION_STATES::MOVING_DOWN;

		}
			this->sprite.move(sf::Vector2f(0.f, 1.f) * this->playerSpeed);
			std::cout << "Moving Left" << std::endl;
	}

	if (!this->isAnyControlActive())
	{
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

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
