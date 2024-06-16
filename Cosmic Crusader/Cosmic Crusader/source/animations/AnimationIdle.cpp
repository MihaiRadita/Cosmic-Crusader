#include "stdafx.h"
#include "AnimationIdle.h"

namespace ratchet
{
	//Constructor functions
	AnimationIdle::AnimationIdle()
	{
		initVariables();
		addAnimationFrames();
	}

	void AnimationIdle::initVariables()
	{
		m_animTimeLimit = 0.5f;

		m_currentFrameIndex = 0;
		m_isAnimTransition = true;

		m_initialTexture = false;
		m_animationTimer.restart();
		m_animationSwitch = true;

		if (s_animFrameImg == nullptr)
		{
			s_animFrameImg = new std::vector<sf::Texture>();
			addAnimationFrames();
		}
	}

	void AnimationIdle::addAnimationFrames()
	{
		bool imageValid = false;
		do
		{
			int imgIndex = AnimationIdle::s_animFrameImg->size();
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
				AnimationIdle::s_animFrameImg->push_back(texture);
			}

		} while (imageValid);
	}

	//Play player animation frames
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
				sprite.setTexture((*s_animFrameImg)[m_currentFrameIndex]);
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
				sprite.setTexture((*s_animFrameImg)[m_currentFrameIndex]);
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
		destroyTextureFrames();
	}

	void AnimationIdle::destroyTextureFrames()
	{
		delete s_animFrameImg;
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
		return AnimationIdle::s_animFrameImg->size();
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

	sf::Clock AnimationIdle::getPlayerAnimTimer()
	{
		return m_animationTimer;
	}

	std::vector<sf::Texture>* AnimationIdle::s_animFrameImg;
}