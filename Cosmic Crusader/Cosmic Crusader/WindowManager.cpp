#include "stdafx.h"
#include "WindowManager.h"

namespace ratchet
{
	void WindowManager::create(sf::RenderWindow* window)
	{
		m_window = window;
	}
	sf::RenderWindow* WindowManager::Get()
	{
		return m_window;
	}
	void WindowManager::clear()
	{
		m_window = nullptr;
	}

	sf::RenderWindow* WindowManager::m_window;
}