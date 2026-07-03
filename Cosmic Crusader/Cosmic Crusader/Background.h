#pragma once

#include "GameObject.h"

namespace ratchet
{
	class Background : public GameObject
	{
	public:

		Background(BackgroundConfig& config);

		~Background();

		int m_backgroundId = -1;
		float m_backgroundSpeed = 0.0f;

		void Start() override;
		void update() override;
		void render(sf::RenderTarget& target)override;

		sf::Vector2f m_prevCameraCenter = sf::Vector2f(0.0f, 0.0f);

		sf::Vector2f m_offset = sf::Vector2f(0.0f, 0.0f);
		sf::Vector2f m_minOffset = sf::Vector2f(0.0f, 0.0f);
		sf::Vector2f m_maxOffset = sf::Vector2f(0.0f, 0.0f);
	};

}

