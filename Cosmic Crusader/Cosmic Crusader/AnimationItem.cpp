#include "stdafx.h"
#include "AnimationItem.h"

#include "ResourceManager.h"

namespace ratchet
{
	AnimationItem::AnimationItem(std::string& texturePath)
	{
		initVariables();

		m_animationFrames = addAnimationFrames(texturePath);
	}
	AnimationItem::~AnimationItem()
	{

	}
	void AnimationItem::playAnimation(sf::Sprite& sprite)
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

					m_currentFrameIndex = 0;

					if (m_repeatAnimation)
					{
						
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
	void AnimationItem::initVariables()
	{
		m_currentFrameIndex = 0;
		m_isAnimTransition = true;

		m_initialTexture = false;
		m_animationTimer.restart();
		m_repeatAnimation = false;

		m_endAnimation = false;
	}
	void AnimationItem::resetPlayerAnimTimer()
	{
		m_animationTimer.restart();
	}

	void AnimationItem::resetCurrentAnimIndex()
	{
		m_currentFrameIndex = 0;
	}

	void AnimationItem::resetAnimationFrame(sf::Sprite& sprite)
	{
		sf::Vector2u texSize = m_animationFrames[0].getSize();
		sprite.setTexture(m_animationFrames[0]);
		sprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
	}

	int AnimationItem::getCurrentAnimIndex()
	{
		return m_currentFrameIndex;
	}

	bool AnimationItem::isAnimationReachedEnd()
	{
		if (m_currentFrameIndex >= getAnimSize() - 1)
		{
			return true;
		}
		return false;
	}

	float AnimationItem::getAnimTimeLimit()
	{
		return m_animTimeLimit;
	}

	int AnimationItem::getAnimSize()
	{
		return m_animationFrames.size();
	}

	void AnimationItem::SetAnimTimeLimit(float value)
	{
		m_animTimeLimit = value;
	}

	std::vector<sf::Texture> AnimationItem::addAnimationFrames(std::string& texturePath)
	{
		auto resultList = std::vector<sf::Texture>();
		bool imageValid = false;
		do
		{
			int imgIndex = resultList.size();
			int strImgIndex = imgIndex + 1;

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