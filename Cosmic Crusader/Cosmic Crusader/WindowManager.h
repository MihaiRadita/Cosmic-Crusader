#pragma once

namespace ratchet
{
	class WindowManager
	{
	public:

		static void create(sf::RenderWindow* window);
		static sf::RenderWindow* Get();
		static void clear();

		static void DestroyWindow();

		static void SetFullScreen(const bool& fullScreen);

		static bool getFullScreen();

	private:
		static sf::RenderWindow* m_window;
		static bool m_fullscreen;
	};
}

