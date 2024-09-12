#include "stdafx.h"
#include "AnimationIdle.h"
#include "ResourceManager.h"


namespace ratchet
{
	//Constructor functions
	AnimationIdle::AnimationIdle(std::string& texturePath)
	{
		initVariables();
		addAnimationFrames(texturePath);
	}

	void AnimationIdle::initVariables()
	{
		m_animTimeLimit = 0.5f;

		m_currentFrameIndex = 0;
		m_isAnimTransition = true;

		m_initialTexture = false;
		m_animationTimer.restart();
		m_animationSwitch = true;
		
	}

	void AnimationIdle::addAnimationFrames(std::string& texturePath)
	{
		bool imageValid = false;
		do
		{
			int imgIndex = m_animFrameImg.size();
			int strImgIndex = imgIndex + 1;

			// Build string
			std::stringstream ss;
			ss << texturePath;
			ss << "IdleTextures/";
			ss << "Idle";
			ss << strImgIndex;
			ss << ".png";
			std::string path = ss.str();
			ss.clear();

			// Load Texture
			const auto* texture = ResourceManager::getInstance()->findOrFetchTexture(path);
			imageValid = texture != nullptr;
			if (imageValid)
			{
				m_animFrameImg.push_back(*texture);
			}

		} while (imageValid);
	}

	void AnimationIdle::playAnimation(sf::Sprite& sprite)
	{
		if (!m_initialTexture)
		{
			m_currentFrameIndex++;
			m_initialTexture = true;
		}
		if (m_currentFrameIndex == 0)
		{
			if (m_isAnimTransition)
			{
				m_isAnimTransition = false;
				sprite.setTexture((m_animFrameImg)[m_currentFrameIndex]);
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
				sprite.setTexture((m_animFrameImg)[m_currentFrameIndex]);
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
	AnimationIdle::~AnimationIdle()
	{

	}


	void AnimationIdle::resetCurrentAnimIndex()
	{
		m_currentFrameIndex = 0;
	}

	void AnimationIdle::resetPlayerAnimTimer()
	{
		m_animationTimer.restart();
		m_animationSwitch = true;
	}

	void AnimationIdle::setAnimationSwitch(bool animSwitch)
	{
		m_animationSwitch = animSwitch;
	}

	//Getters Functions
	int AnimationIdle::getAnimSize()
	{
		return m_animFrameImg.size();
	}

	int AnimationIdle::getCurrentAnimIndex()
	{
		return m_currentFrameIndex;
	}

	bool AnimationIdle::getAnimationSwitch()
	{
		bool anim_switch = m_animationSwitch;

		if (m_animationSwitch)
		{
			m_animationSwitch = false;
		}

		return anim_switch;
	}

}