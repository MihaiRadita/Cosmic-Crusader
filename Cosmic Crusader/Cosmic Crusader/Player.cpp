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

void Player::SetPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::updateMovement()
{
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->sprite.move(sf::Vector2f(-1.f, 0.f) * this->playerSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->sprite.move(sf::Vector2f(1.f, 0.f) * this->playerSpeed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		this->sprite.move(sf::Vector2f(0.f, -1.f) * this->playerSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		this->sprite.move(sf::Vector2f(0.f, 1.f) * this->playerSpeed);
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
