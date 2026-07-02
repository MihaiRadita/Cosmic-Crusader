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

		void update() override;
		void render(sf::RenderTarget& target)override;

	private:
	};

}

