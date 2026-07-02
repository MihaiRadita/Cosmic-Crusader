#include "stdafx.h"
#include "Background.h"

namespace ratchet
{
	Background::Background(BackgroundConfig& config) : GameObject(config)
	{
		m_backgroundId = config.m_backgroundId;
	}

	Background::~Background()
	{

	}

	void Background::update()
	{

	}

	void Background::render(sf::RenderTarget& target)
	{
		target.draw(m_sprite);
	}
}