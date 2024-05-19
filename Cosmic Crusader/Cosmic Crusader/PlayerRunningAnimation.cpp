#include "stdafx.h"
#include "PlayerRunningAnimation.h"

//Constructors
PlayerRunningAnimation::PlayerRunningAnimation() : c_animTimeLimit(0.1f), m_currentFrameIndex(0), m_isAnimTransition(true)
{
	this->initVariables();
	this->addAnimationFrames();
}

//Init Functions
void PlayerRunningAnimation::initVariables()
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

//Add animation frames images
void PlayerRunningAnimation::addAnimationFrames()
{
	bool imageValid = false;
	do
	{
		int imgIndex = PlayerRunningAnimation::s_animFrameImg->size();
		int strImgIndex = imgIndex + 1;

		// Build string
		std::stringstream ss;
		ss << "Textures/PlayerTextures/Player1Textures/RunTextures/";
		ss << "Run";
		ss << strImgIndex;
		ss << ".png";
		std::string path = ss.str();
		ss.clear();

		// Load Texture
		sf::Texture texture;
		imageValid = texture.loadFromFile(path);
		if (imageValid)
		{
			PlayerRunningAnimation::s_animFrameImg->push_back(texture);
		}

	} while (imageValid);
}

//Play player animation frames
void PlayerRunningAnimation::playAnimation(sf::Sprite& sprite)
{
	if (this->m_currentFrameIndex == 0)
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
PlayerRunningAnimation::~PlayerRunningAnimation()
{
	this->destroyTextureFrames();
}

void PlayerRunningAnimation::destroyTextureFrames()
{
	delete this->s_animFrameImg;
}

//Other Functions
void PlayerRunningAnimation::resetCurrentAnimIndex()
{
	this->m_currentFrameIndex = 0;
}

void PlayerRunningAnimation::resetPlayerAnimTimer()
{
	this->m_animationTimer.restart();
	this->m_animationSwitch = true;
}

void PlayerRunningAnimation::setAnimationSwitch(bool animSwitch)
{
	this->m_animationSwitch = m_animationSwitch;
}

//Getters Functions
int PlayerRunningAnimation::getAnimSize()
{
	return this->PlayerRunningAnimation::s_animFrameImg->size();
}
int PlayerRunningAnimation::getCurrentAnimIndex()
{
	return this->m_currentFrameIndex;
}

bool PlayerRunningAnimation::getAnimationSwitch()
{
	bool anim_switch = this->m_animationSwitch;

	if (this->m_animationSwitch)
	{
		this->m_animationSwitch = false;
	}

	return anim_switch;
}

std::vector<sf::Texture>* PlayerRunningAnimation::s_animFrameImg;