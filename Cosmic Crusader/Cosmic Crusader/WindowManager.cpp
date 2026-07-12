#include "stdafx.h"
#include "WindowManager.h"

namespace ratchet
{
	void WindowManager::create(sf::RenderWindow* window)
	{
		m_window = window;
		m_window->setVerticalSyncEnabled(true);
		m_window->setFramerateLimit(60);
	}
	sf::RenderWindow* WindowManager::Get()
	{
		return m_window;
	}
	void WindowManager::clear()
	{
		m_window = nullptr;
	}

	void WindowManager::DestroyWindow()
	{
		m_window = nullptr;
	}

	void WindowManager::SetFullScreen(const bool& fullScreen)
	{
		m_fullscreen = fullScreen;
	}

	bool WindowManager::getFullScreen()
	{
		return m_fullscreen;
	}

	sf::RenderWindow* WindowManager::m_window;
	bool WindowManager::m_fullscreen = false;
}