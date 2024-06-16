#include "stdafx.h"
#include "AnimationJump.h"

namespace ratchet
{
	//Consturctors
	AnimationJump::AnimationJump()
	{
		initVariables();
		addAnimationFrames();
	}

	// Init Functions
	void AnimationJump::initVariables()
	{
		m_animTimeLimit = 0.028f;
		m_currentFrameIndex = 0;
		m_animTimeJumpLimit = 0.015f;
		m_jumpAnimFrameIndex = 17;
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

	//Geters
	int AnimationJump::getAnimSize()
	{
		return AnimationJump::s_animFrameImg->size();
	}

	void AnimationJump::addAnimationFrames()
	{
		bool imageValid = false;
		do
		{
			int imgIndex = AnimationJump::s_animFrameImg->size();
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
				AnimationJump::s_animFrameImg->push_back(texture);
			}

		} while (imageValid);
	}

	//Play player animation frames
	void AnimationJump::playAnimation(sf::Sprite& sprite)
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
	AnimationJump::~AnimationJump()
	{
		destroyTextureFrames();
	}

	void AnimationJump::destroyTextureFrames()
	{
		delete s_animFrameImg;
	}

	//Other Functions
	void AnimationJump::resetCurrentAnimIndex()
	{
		m_currentFrameIndex = 0;
	}

	void AnimationJump::resetPlayerAnimTimer()
	{
		m_animationTimer.restart();
		m_animationSwitch = true;
	}

	void AnimationJump::setAnimationSwitch(bool animSwitch)
	{
		m_animationSwitch = m_animationSwitch;
	}

	int AnimationJump::getCurrentAnimIndex()
	{
		return m_currentFrameIndex;
	}

	bool AnimationJump::getAnimationSwitch()
	{
		bool anim_switch = m_animationSwitch;

		if (m_animationSwitch)
		{
			m_animationSwitch = false;
		}

		return anim_switch;
	}

	bool AnimationJump::isCurrentAnimationIndexValue()
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

	std::vector<sf::Texture>* AnimationJump::s_animFrameImg;
}