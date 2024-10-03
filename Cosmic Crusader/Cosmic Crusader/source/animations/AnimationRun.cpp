#include "stdafx.h"
#include "AnimationRun.h"
#include "ResourceManager.h"


namespace ratchet
{
	//Constructors
	AnimationRun::AnimationRun(std::string& texturePath)
	{
		initVariables();
		addAnimationFrames(texturePath);
	}

	//Init Functions
	void AnimationRun::initVariables()
	{
		m_animTimeLimit = 0.035f;
		m_currentFrameIndex = 0;
		m_isAnimTransition = true;

		m_initialTexture = false;
		m_animationTimer.restart();
		m_animationSwitch = true;
	}

	//Add animation frames images
	void AnimationRun::addAnimationFrames(std::string& texturePath)
	{
		bool imageValid = false;
		do
		{
			int imgIndex = s_animFrameImg.size();
			int strImgIndex = imgIndex + 1;

			// Build string
			std::stringstream ss;
			ss << texturePath;
			ss << "RunTextures/";
			ss << "Run";
			ss << strImgIndex;
			ss << ".png";
			std::string path = ss.str();
			ss.clear();

			// Load Texture
			const auto* texture = ResourceManager::getInstance()->findOrFetchTexture(path);
			imageValid = texture != nullptr;
			if (imageValid)
			{
				s_animFrameImg.push_back(*texture);
			}

		} while (imageValid);
	}

	//Play player animation frames
	void AnimationRun::playAnimation(sf::Sprite& sprite)
	{
		if (m_currentFrameIndex == 0)
		{
			if (m_isAnimTransition)
			{
				m_isAnimTransition = false;
				sprite.setTexture((s_animFrameImg)[m_currentFrameIndex]);
#ifdef IS_RATCHET_DEBUG
				std::cout << "PLayer Idle image " << m_currentFrameIndex << std::endl;
#endif

			}
			if (m_animationTimer.getElapsedTime().asSeconds() >= m_animTimeLimit || getAnimationSwitch())
			{
				m_isAnimTransition = true;
				m_currentFrameIndex++;
				m_animationTimer.restart();
			}
		}
		else if (m_currentFrameIndex > 0)
		{
			if (m_isAnimTransition)
			{
				m_isAnimTransition = false;
				sprite.setTexture((s_animFrameImg)[m_currentFrameIndex]);
#ifdef IS_RATCHET_DEBUG
				std::cout << "PLayer Idle image " << m_currentFrameIndex << std::endl;
#endif
			}
			if (m_animationTimer.getElapsedTime().asSeconds() >= m_animTimeLimit || getAnimationSwitch())
			{
				m_isAnimTransition = true;
				m_currentFrameIndex++;
				if (m_currentFrameIndex >= getAnimSize())
				{
					m_currentFrameIndex = 0;
				}
				m_animationTimer.restart();
			}
		}
	}

	//Destroy functions
	AnimationRun::~AnimationRun()
	{
	}

	//Other Functions
	void AnimationRun::resetCurrentAnimIndex()
	{
		m_currentFrameIndex = 0;
	}

	void AnimationRun::resetPlayerAnimTimer()
	{
		m_animationTimer.restart();
		m_animationSwitch = true;
	}

	void AnimationRun::setAnimationSwitch(bool animSwitch)
	{
		m_animationSwitch = m_animationSwitch;
	}

	//Getters Functions
	int AnimationRun::getAnimSize()
	{
		return s_animFrameImg.size();
	}
	int AnimationRun::getCurrentAnimIndex()
	{
		return m_currentFrameIndex;
	}

	bool AnimationRun::getAnimationSwitch()
	{
		bool anim_switch = m_animationSwitch;

		if (m_animationSwitch)
		{
			m_animationSwitch = false;
		}

		return anim_switch;
	}

}