#include "stdafx.h"
#include "AnimationJumpRun.h"
#include "ResourceManager.h"

namespace ratchet
{
	//Construcotrs
	AnimationJumpRun::AnimationJumpRun(std::string& texturePath)
	{
		initVariables();
		addAnimationFrames(texturePath);
	}

	//Init functions
	void AnimationJumpRun::initVariables()
	{
		m_animTimeLimit = 0.02f;
		m_currentFrameIndex = 0;
		m_animTimeJumpLimit = 0.089f;
		m_jumpAnimFrameIndex = 1;
		m_isAnimTransition = true;

		m_initialTexture = false;
		m_animationTimer.restart();
		m_animationSwitch = true;
		m_currentJumpTimeLimit = m_animTimeLimit;
	}

	//Add animation frames images
	void AnimationJumpRun::addAnimationFrames(std::string& texturePath)
	{
		bool imageValid = false;
		do
		{
			int imgIndex = s_animFrameImg.size();
			int strImgIndex = imgIndex + 1;

			// Build string
			std::stringstream ss;
			ss << texturePath;
			ss << "JumpRunningTextures/";
			ss << "JumpRunning";
			ss << strImgIndex;
			ss << ".png";
			std::string path = ss.str();
			ss.clear();

			// Load Texture
			auto* texture = ResourceManager::getInstance()->findOrFetchTexture(path);
			imageValid = texture != nullptr;
			if (imageValid)
			{
				s_animFrameImg.push_back(*texture);
			}

		} while (imageValid);
	}

	//Play player animation frames
	void AnimationJumpRun::playAnimation(sf::Sprite& sprite)
	{
		if (m_currentFrameIndex == 0)
		{
			if (m_isAnimTransition)
			{
				m_isAnimTransition = false;
				sprite.setTexture((s_animFrameImg)[m_currentFrameIndex]);
#ifdef IS_RATCHET_DEBUG
				std::cout << "PLayer Jump image " << m_currentFrameIndex << std::endl;
#endif

			}
			if (m_animationTimer.getElapsedTime().asSeconds() >= m_currentJumpTimeLimit || getAnimationSwitch())
			{
				m_isAnimTransition = true;
				m_currentFrameIndex++;
				m_animationTimer.restart();
			}
		}
		else if (m_currentFrameIndex > 0)
		{


			if (m_currentFrameIndex >= getAnimSize())
			{
				return;
			}
			if (m_isAnimTransition)
			{
				m_isAnimTransition = false;
				sprite.setTexture((s_animFrameImg)[m_currentFrameIndex]);
#ifdef IS_RATCHET_DEBUG
				std::cout << "PLayer Jump image " << m_currentFrameIndex << std::endl;
#endif
			}
			if (m_animationTimer.getElapsedTime().asSeconds() >= m_currentJumpTimeLimit || getAnimationSwitch())
			{
				m_isAnimTransition = true;
				m_currentFrameIndex++;

				if (m_currentFrameIndex == m_jumpAnimFrameIndex)
				{
					m_currentJumpTimeLimit = m_animTimeJumpLimit;
				}
				m_animationTimer.restart();
			}
		}
	}

	//Destroy functions
	AnimationJumpRun::~AnimationJumpRun()
	{
	}

	//Other functions
	void AnimationJumpRun::resetCurrentAnimIndex()
	{
		m_currentFrameIndex = 0;
	}

	void AnimationJumpRun::resetPlayerAnimTimer()
	{
		m_animationTimer.restart();
		m_animationSwitch = true;
	}

	void AnimationJumpRun::setAnimationSwitch(bool animSwitch)
	{
		m_animationSwitch = m_animationSwitch;
	}

	//Getters Functions
	int AnimationJumpRun::getAnimSize()
	{
		return s_animFrameImg.size();
	}

	int AnimationJumpRun::getCurrentAnimIndex()
	{
		return m_currentFrameIndex;
	}

	bool AnimationJumpRun::getAnimationSwitch()
	{
		bool anim_switch = m_animationSwitch;

		if (m_animationSwitch)
		{
			m_animationSwitch = false;
		}

		return anim_switch;
	}

	bool AnimationJumpRun::isCurrentAnimationIndexValue()
	{
		if (m_currentFrameIndex == m_jumpAnimFrameIndex)
		{
			return  false;
#ifdef IS_RATCHET_DEBUG
			std::cout << "image number action " << m_jumpAnimFrameIndex << " happended!" << std::endl;
#endif
		}

		return true;
	}

}