#include "stdafx.h"
#include "PlayerJumpRunningAnimation.h"

//Construcotrs
PlayerJumpRunningAnimation::PlayerJumpRunningAnimation() : c_animTimeLimit(0.02f), m_currentFrameIndex(0), c_animTimeJumpLimit(0.089f), c_jumpAnimFrameIndex(1), m_isAnimTransition(true)
{
	this->initVariables();
	this->addAnimationFrames();
}

//Init functions
void PlayerJumpRunningAnimation::initVariables()
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

//Add animation frames images
void PlayerJumpRunningAnimation::addAnimationFrames()
{
	bool imageValid = false;
	do
	{
		int imgIndex = PlayerJumpRunningAnimation::s_animFrameImg->size();
		int strImgIndex = imgIndex + 1;

		// Build string
		std::stringstream ss;
		ss << "Textures/PlayerTextures/Player1Textures/JumpRunningTextures/";
		ss << "JumpRunning";
		ss << strImgIndex;
		ss << ".png";
		std::string path = ss.str();
		ss.clear();

		// Load Texture
		sf::Texture texture;
		imageValid = texture.loadFromFile(path);
		if (imageValid)
		{
			PlayerJumpRunningAnimation::s_animFrameImg->push_back(texture);
		}

	} while (imageValid);
}

//Play player animation frames
void PlayerJumpRunningAnimation::playAnimation(sf::Sprite& sprite)
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
PlayerJumpRunningAnimation::~PlayerJumpRunningAnimation()
{
	this->destroyTextureFrames();
}

void PlayerJumpRunningAnimation::destroyTextureFrames()
{
	delete this->s_animFrameImg;
}

//Other functions
void PlayerJumpRunningAnimation::resetCurrentAnimIndex()
{
	this->m_currentFrameIndex = 0;
}

void PlayerJumpRunningAnimation::resetPlayerAnimTimer()
{
	this->m_animationTimer.restart();
	this->m_animationSwitch = true;
}

void PlayerJumpRunningAnimation::setAnimationSwitch(bool animSwitch)
{
	this->m_animationSwitch = m_animationSwitch;
}

//Getters Functions
int PlayerJumpRunningAnimation::getAnimSize()
{
	return this->PlayerJumpRunningAnimation::s_animFrameImg->size();
}

int PlayerJumpRunningAnimation::getCurrentAnimIndex()
{
	return this->m_currentFrameIndex;
}

bool PlayerJumpRunningAnimation::getAnimationSwitch()
{
	bool anim_switch = this->m_animationSwitch;

	if (this->m_animationSwitch)
	{
		this->m_animationSwitch = false;
	}

	return anim_switch;
}

bool PlayerJumpRunningAnimation::isCurrentAnimationIndexValue()
{
	if (this->m_currentFrameIndex == this->c_jumpAnimFrameIndex)
	{
		return  false;
		std::cout << "image number action " << this->c_jumpAnimFrameIndex << " happended!" << std::endl;
	}

	return true;
}

std::vector<sf::Texture>* PlayerJumpRunningAnimation::s_animFrameImg;