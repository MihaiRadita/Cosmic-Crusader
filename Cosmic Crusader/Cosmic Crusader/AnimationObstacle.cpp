#include "stdafx.h"
#include "AnimationObstacle.h"

#include "ResourceManager.h"

namespace ratchet
{
	AnimationObstacle::AnimationObstacle(std::string& texturePath)
	{
		initVariables();

		m_animationFrames = addAnimationFrames(texturePath);

	}

	AnimationObstacle::~AnimationObstacle()
	{

	}

	void AnimationObstacle::playAnimation(sf::Sprite& sprite)
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

				sf::Vector2u texSize = m_animationFrames[m_currentFrameIndex].getSize();
				sprite.setTexture(m_animationFrames[m_currentFrameIndex]);
				sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
			}

			if (m_animationTimer.getElapsedTime().asSeconds() >= m_animTimeLimit)
			{
				m_isAnimTransition = true;

				bool increaseFrameIndex = true;

				if (m_currentFrameIndex >= getAnimSize() - 1)
				{
					increaseFrameIndex = false;
					if (m_repeatAnimation)
					{
						m_currentFrameIndex = 0;
					}
				}
				if (increaseFrameIndex)
				{
					m_currentFrameIndex++;
				}

				m_animationTimer.restart();
			}
		}
		else if (m_currentFrameIndex > 0)
		{
			if (m_isAnimTransition)
			{
				m_isAnimTransition = false;

				sf::Vector2u texSize = m_animationFrames[m_currentFrameIndex].getSize();
				sprite.setTexture(m_animationFrames[m_currentFrameIndex]);
				sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
			}
			if (m_animationTimer.getElapsedTime().asSeconds() >= m_animTimeLimit)
			{
				m_isAnimTransition = true;

				bool increaseFrameIndex = true;

				if (m_currentFrameIndex >= getAnimSize() - 1)
				{
					increaseFrameIndex = false;

					if (m_repeatAnimation)
					{
						if (m_frameIndexContinueAnimationFrom != 0)
						{
							m_currentFrameIndex = m_frameIndexContinueAnimationFrom;
						}
						else
						{
							m_currentFrameIndex = 0;

						}
					}
				}

				if (increaseFrameIndex)
				{
					m_currentFrameIndex++;
				}
				m_animationTimer.restart();
			}
		}
	}

	void AnimationObstacle::initVariables()
	{
		m_animTimeLimit = 0.1f;

		m_currentFrameIndex = 0;
		m_isAnimTransition = true;

		m_initialTexture = false;
		m_animationTimer.restart();
		m_repeatAnimation = true;

		m_endAnimation = false;
	}

	void AnimationObstacle::resetPlayerAnimTimer()
	{
		m_animationTimer.restart();
	}

	void AnimationObstacle::resetCurrentAnimIndex()
	{
		m_currentFrameIndex = 0;
	}

	void AnimationObstacle::resetAnimationFrame(sf::Sprite& sprite)
	{
		sf::Vector2u texSize = m_animationFrames[0].getSize();
		sprite.setTexture(m_animationFrames[0]);
		sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
	}

	int AnimationObstacle::getAnimSize()
	{
		return m_animationFrames.size();
	}

	int AnimationObstacle::getCurrentAnimIndex()
	{
		return m_currentFrameIndex;
	}

	bool AnimationObstacle::isAnimationReachedEnd()
	{
		if (m_currentFrameIndex >= getAnimSize() - 1)
		{
			return true;
		}
	}

	std::vector<sf::Texture> AnimationObstacle::addAnimationFrames(std::string& texturePath)
	{
		auto resultList = std::vector<sf::Texture>();
		bool imageValid = false;
		do
		{
			int imgIndex = resultList.size();
			int strImgIndex = imgIndex + 1;

			// Build string
			std::stringstream ss;
			ss << texturePath;
			ss << strImgIndex;
			ss << ".png";
			std::string path = ss.str();
			ss.clear();

			// Load Texture
			const auto* texture = ResourceManager::getInstance()->findOrFetchTexture(path);
			imageValid = texture != nullptr;
			if (imageValid)
			{
				resultList.push_back(*texture);
			}

		} while (imageValid);

		return resultList;
	}
}