#include "stdafx.h"
#include "UIBar.h"

#include "SceneManager.h"

namespace ratchet
{
	UIBar::UIBar(const UIBarConfig& config) : GameObject(config)
	{
		m_barSizeX = config.m_barSizeX;
		m_barSizeY = config.m_barSizeY;
		m_barOffsetX = config.m_barOffsetX;
		m_barOffsetY = config.m_barOffsetY;
		m_rColor = config.m_rColor;
		m_gColor = config.m_gColor;
		m_bColor = config.m_bColor;
		m_rBackColor = config.m_rBackColor;
		m_gBackColor = config.m_gBackColor;
		m_bBackColor = config.m_bBackColor;
		m_spriteBarOffsetX = config.m_spriteBarOffsetX;
		m_spriteBarOffsetY = config.m_spriteBarOffsetY;
		m_barSpriteTexturePath = config.m_barSpriteTexturePath;
		m_hudBarTargetId = config.m_hudBarTargetId;

		
	}
	UIBar::~UIBar()
	{

	}
	void UIBar::update()
	{

	}

	void UIBar::render(sf::RenderTarget& target)
	{
		target.draw(m_hudBackBar);
		target.draw(m_hudBar);
		target.draw(m_hudBarSprite);
	}

	void UIBar::setBarValueX(float& currentValue, float& maxValue)
	{
		m_maxValueX = maxValue;
		m_currentValueX = currentValue;

		if (m_currentValueX < 0.0f)
		{
			m_currentValueX = 0.0f;
		}

		if (m_currentValueX > m_maxValueX)
		{
			m_currentValueX = m_maxValueX;
		}

		float ratio = m_currentValueX / m_maxValueX;

		float newWidth = ratio * m_barSizeX;

		m_hudBar.setSize(sf::Vector2f(newWidth, m_barSizeY));

	}

	void UIBar::resetValueX(float& maxValue)
	{

		m_currentValueX = maxValue;
		m_maxValueX = maxValue;

		if (m_maxValueX <= 0.0f)
		{
			m_hudBar.setSize(sf::Vector2f(0.0f, m_barSizeY));
			return;
		}

		m_hudBar.setSize(sf::Vector2f(m_barSizeX, m_barSizeY));
	}

	void UIBar::Start()
	{
	
		m_hudBar.setFillColor(sf::Color(
			static_cast<sf::Uint8>(m_rColor),
			static_cast<sf::Uint8>(m_gColor),
			static_cast<sf::Uint8>(m_bColor)));
		m_hudBar.setSize(sf::Vector2f(m_barSizeX, m_barSizeY));
		m_hudBar.setScale(m_scale.x, m_scale.y);

		m_hudBar.setPosition(SceneManager::Get().GetHUDView().getCenter().x + m_barOffsetX,
							 SceneManager::Get().GetHUDView().getCenter().y + m_barOffsetY);
		m_hudBar.setRotation(m_hudBar.getRotation());


		m_hudBackBar.setFillColor(sf::Color(
			static_cast<sf::Uint8>(m_rBackColor),
			static_cast<sf::Uint8>(m_gBackColor),
			static_cast<sf::Uint8>(m_bBackColor)));
		m_hudBackBar.setSize(sf::Vector2f(m_barSizeX, m_barSizeY));
		m_hudBackBar.setScale(m_scale.x, m_scale.y);

		m_hudBackBar.setPosition(m_hudBar.getPosition().x ,
								m_hudBar.getPosition().y );
		m_hudBackBar.setRotation(m_hudBackBar.getRotation());

		if (m_barSpriteTexture.loadFromFile(m_barSpriteTexturePath))
		{
			m_hudBarSprite.setTexture(m_barSpriteTexture);
			m_hudBarSprite.setPosition(m_hudBar.getPosition().x + m_spriteBarOffsetX, m_hudBar.getPosition().y + m_spriteBarOffsetY);
			m_hudBarSprite.setRotation(m_rotation);
			m_hudBarSprite.setScale(m_scale.x, m_scale.y);

		}

	}
}