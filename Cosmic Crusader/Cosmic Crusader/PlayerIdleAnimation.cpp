#include "stdafx.h"
#include "PlayerIdleAnimation.h"



//Constructor functions
PlayerIdleAnimation::PlayerIdleAnimation() : c_animTimeLimit(0.5f), m_currentFrameIndex(0), m_isAnimTransition(true)
{
	this->initVariables();
	this->addAnimationFrames();
}

void PlayerIdleAnimation::initVariables()
{
	this->m_initialTexture = false;
	this->m_animationTimer.restart();
	this->m_animationSwitch = true;

	if (s_animFrameImg == nullptr)
	{
		this->s_animFrameImg = new std::vector<sf::Texture>();
		this->addAnimationFrames();
	}
}

void PlayerIdleAnimation::addAnimationFrames()
{
	bool imageValid = false;
	do
	{
		int imgIndex = PlayerIdleAnimation::s_animFrameImg->size();
		int strImgIndex = imgIndex + 1;

		// Build string
		std::stringstream ss;
		ss << "Textures/PlayerTextures/Player1Textures/IdleTextures/";
		ss << "Idle";
		ss << strImgIndex;
		ss << ".png";
		std::string path = ss.str();
		ss.clear();

		// Load Texture
		sf::Texture texture;
		imageValid = texture.loadFromFile(path);
		if (imageValid)
		{
			PlayerIdleAnimation::s_animFrameImg->push_back(texture);
		}

	} while (imageValid);
}

//Play player animation frames
void PlayerIdleAnimation::playAnimation(sf::Sprite& sprite)
{
	if (!this->m_initialTexture)
	{
		this->m_currentFrameIndex++;
		this->m_initialTexture = true;
	}
	if (this->m_currentFrameIndex == 0)
	{
		if (this->m_isAnimTransition)
		{
			this->m_isAnimTransition = false;
			sprite.setTexture((*this->s_animFrameImg)[m_currentFrameIndex]);
			std::cout << "PLayer Idle image " << m_currentFrameIndex<<std::endl;

		}
		if (this->m_animationTimer.getElapsedTime().asSeconds() >= this->c_animTimeLimit || this->getAnimationSwitch())
		{
			this->m_isAnimTransition = true;
			this->m_currentFrameIndex++;
			this->m_animationTimer.restart();
		}
	}
	else if (this->m_currentFrameIndex > 0)
	{
		if (this->m_isAnimTransition)
		{
			this->m_isAnimTransition = false;
			sprite.setTexture((*this->s_animFrameImg)[m_currentFrameIndex]);
			std::cout << "PLayer Idle image " << m_currentFrameIndex << std::endl;
		}
		if (this->m_animationTimer.getElapsedTime().asSeconds() >= this->c_animTimeLimit || this->getAnimationSwitch())
		{
			this->m_isAnimTransition = true;
			this->m_currentFrameIndex++;
			if (this->m_currentFrameIndex >= this->getAnimSize())
			{
				this->m_currentFrameIndex = 0;
			}
			this->m_animationTimer.restart();
		}
	}
}

//Destroy functions
PlayerIdleAnimation::~PlayerIdleAnimation()
{
	this->destroyTextureFrames();
}

void PlayerIdleAnimation::destroyTextureFrames()
{
	delete this->s_animFrameImg;
}

void PlayerIdleAnimation::resetCurrentAnimIndex()
{
	this->m_currentFrameIndex = 0;
}

void PlayerIdleAnimation::resetPlayerAnimTimer()
{
	this->m_animationTimer.restart();
	this->m_animationSwitch = true;
}

void PlayerIdleAnimation::setAnimationSwitch(bool animSwitch)
{
	this->m_animationSwitch = animSwitch;
}

//Getters Functions
int PlayerIdleAnimation::getAnimSize() 
{
	return this->PlayerIdleAnimation::s_animFrameImg->size();
}

int PlayerIdleAnimation::getCurrentAnimIndex()
{
	return this->m_currentFrameIndex;
}

bool PlayerIdleAnimation::getAnimationSwitch()
{
	bool anim_switch = this->m_animationSwitch;

	if (this->m_animationSwitch)
	{
		this->m_animationSwitch = false;
	}

	return anim_switch;
}

sf::Clock PlayerIdleAnimation::getPlayerAnimTimer()
{
	return this->m_animationTimer;
}

std::vector<sf::Texture>* PlayerIdleAnimation::s_animFrameImg;
