#include "stdafx.h"
#include "Background.h"

#include "game/Game.h"

namespace ratchet
{
	Background::Background(BackgroundConfig& config) : GameObject(config)
	{
		m_backgroundId = config.m_backgroundId;
		m_backgroundSpeed = config.m_backgroundSpeed;
		m_minOffset = sf::Vector2f(-m_sprite.getGlobalBounds().width, -m_sprite.getGlobalBounds().height) * 2.0f;
		m_maxOffset = sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height) * 2.0f;
		m_offset = m_sprite.getPosition() + sf::Vector2f(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f);
	}

	Background::~Background()
	{
	}

	void Background::Start()
	{
		const auto& currentCameraCenter = SceneManager::Get().GetWorldView().getCenter();
		m_prevCameraCenter = currentCameraCenter;
	}

	void Background::update()
	{
		// Calculate new offset.
        const auto& currentCameraCenter = SceneManager::Get().GetWorldView().getCenter();
		const auto cameraDelta = currentCameraCenter - m_prevCameraCenter;

		if (cameraDelta != sf::Vector2f(0.0f, 0.0f))
		{
			m_offset += (-cameraDelta) * m_backgroundSpeed;

			// Ensure the new offset is still within bounds.
			if (m_offset.x < m_minOffset.x)
			{
				m_offset.x = m_maxOffset.x - (m_minOffset.x - m_offset.x);
			}
			if (m_offset.x > m_maxOffset.x)
			{
				m_offset.x = m_minOffset.x + (m_offset.x - m_maxOffset.x);
			}
			if (m_offset.y < m_minOffset.y)
			{
				m_offset.y = m_maxOffset.y - (m_minOffset.y - m_offset.y);
			}
			if (m_offset.y > m_maxOffset.y)
			{
				m_offset.y = m_minOffset.y + (m_offset.y - m_maxOffset.y);
			}

			// Update new position
			/*const auto& currentPosition = m_sprite.getPosition();*/
			sf::Vector2f newPosition = currentCameraCenter + m_offset;
			m_sprite.setPosition(newPosition.x, newPosition.y);
		}
		// Keep track of camera position.
		m_prevCameraCenter = currentCameraCenter;
	}

	void Background::render(sf::RenderTarget& target)
	{
		target.draw(m_sprite);
	}
}