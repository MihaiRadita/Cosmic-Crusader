#include "stdafx.h"
#include "AnimationJumpRun.h"

namespace ratchet
{
	//Construcotrs
	AnimationJumpRun::AnimationJumpRun()
	{
		initVariables();
		addAnimationFrames();
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

		if (s_animFrameImg == nullptr)
		{
			s_animFrameImg = new std::vector<sf::Texture>();
			addAnimationFrames();
		}
	}

	//Add animation frames images
	void AnimationJumpRun::addAnimationFrames()
	{
		bool imageValid = false;
		do
		{
			int imgIndex = AnimationJumpRun::s_animFrameImg->size();
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
				AnimationJumpRun::s_animFrameImg->push_back(texture);
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
				sprite.setTexture((*s_animFrameImg)[m_currentFrameIndex]);
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
				sprite.setTexture((*s_animFrameImg)[m_currentFrameIndex]);
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
		destroyTextureFrames();
	}

	void AnimationJumpRun::destroyTextureFrames()
	{
		delete s_animFrameImg;
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
		return AnimationJumpRun::s_animFrameImg->size();
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

	std::vector<sf::Texture>* AnimationJumpRun::s_animFrameImg;
}