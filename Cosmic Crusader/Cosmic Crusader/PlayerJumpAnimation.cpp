#include "stdafx.h"
#include "PlayerJumpAnimation.h"

//Consturctors
PlayerJumpAnimation::PlayerJumpAnimation() : c_animTimeLimit(0.028f), m_currentFrameIndex(0),c_animTimeJumpLimit(0.015f),c_jumpAnimFrameIndex(17), m_isAnimTransition(true)
{
	this->initVariables();
	this->addAnimationFrames();
}

// Init Functions
void PlayerJumpAnimation::initVariables()
{
	this->m_initialTexture = false;
	this->m_animationTimer.restart();
	this->m_animationSwitch = true;
	this->m_currentJumpTimeLimit = this->c_animTimeLimit;

	if (s_animFrameImg == nullptr)
	{
		this->s_animFrameImg = new std::vector<sf::Texture>();
		this->addAnimationFrames();
	}
}

//Geters
int PlayerJumpAnimation::getAnimSize()
{
	return this->PlayerJumpAnimation::s_animFrameImg->size();
}

void PlayerJumpAnimation::addAnimationFrames()
{
	bool imageValid = false;
	do
	{
		int imgIndex = PlayerJumpAnimation::s_animFrameImg->size();
		int strImgIndex = imgIndex + 1;

		// Build string
		std::stringstream ss;
		ss << "Textures/PlayerTextures/Player1Textures/JumpTextures/";
		ss << "Jump";
		ss << strImgIndex;
		ss << ".png";
		std::string path = ss.str();
		ss.clear();

		// Load Texture
		sf::Texture texture;
		imageValid = texture.loadFromFile(path);
		if (imageValid)
		{
			PlayerJumpAnimation::s_animFrameImg->push_back(texture);
		}

	} while (imageValid);
}

//Play player animation frames
void PlayerJumpAnimation::playAnimation(sf::Sprite& sprite)
{
	if (this->m_currentFrameIndex == 0)
	{
		if (this->m_isAnimTransition)
		{
			this->m_isAnimTransition = false;
			sprite.setTexture((*this->s_animFrameImg)[m_currentFrameIndex]);
			std::cout << "PLayer Jump image " << m_currentFrameIndex << std::endl;

		}
		if (this->m_animationTimer.getElapsedTime().asSeconds() >= this->m_currentJumpTimeLimit || this->getAnimationSwitch())
		{
			this->m_isAnimTransition = true;
			this->m_currentFrameIndex++;
			this->m_animationTimer.restart();
		}
	}
	else if (this->m_currentFrameIndex > 0)
	{
		if (this->m_currentFrameIndex >= this->getAnimSize())
		{
			return;
		}
		if (this->m_isAnimTransition)
		{
			this->m_isAnimTransition = false;
			sprite.setTexture((*this->s_animFrameImg)[m_currentFrameIndex]);
			std::cout << "PLayer Jump image " << m_currentFrameIndex << std::endl;
		}
		if (this->m_animationTimer.getElapsedTime().asSeconds() >= this->m_currentJumpTimeLimit || this->getAnimationSwitch())
		{
			this->m_isAnimTransition = true;
			this->m_currentFrameIndex++;

			if (this->m_currentFrameIndex == this->c_jumpAnimFrameIndex)
			{
				this->m_currentJumpTimeLimit = this->c_animTimeJumpLimit;
			}
			this->m_animationTimer.restart();
		}
	}
}

//Destroy functions
PlayerJumpAnimation::~PlayerJumpAnimation()
{
	this->destroyTextureFrames();
}

void PlayerJumpAnimation::destroyTextureFrames()
{
	delete this->s_animFrameImg;
}

//Other Functions
void PlayerJumpAnimation::resetCurrentAnimIndex()
{
	this->m_currentFrameIndex = 0;
}

void PlayerJumpAnimation::resetPlayerAnimTimer()
{
	this->m_animationTimer.restart();
	this->m_animationSwitch = true;
}

void PlayerJumpAnimation::setAnimationSwitch(bool animSwitch)
{
	this->m_animationSwitch = m_animationSwitch;
}

int PlayerJumpAnimation::getCurrentAnimIndex()
{
	return this->m_currentFrameIndex;
}

bool PlayerJumpAnimation::getAnimationSwitch()
{
	bool anim_switch = this->m_animationSwitch;

	if (this->m_animationSwitch)
	{
		this->m_animationSwitch = false;
	}

	return anim_switch;
}

bool PlayerJumpAnimation::isCurrentAnimationIndexValue()
{
	if (this->m_currentFrameIndex == this->c_jumpAnimFrameIndex)
	{
		return  false;
		std::cout << "image number action " << this->c_jumpAnimFrameIndex << " happended!" << std::endl;
	}

	return true;
}

std::vector<sf::Texture>* PlayerJumpAnimation::s_animFrameImg;