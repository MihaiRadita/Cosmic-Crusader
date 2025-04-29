#pragma once

namespace ratchet
{
	class WindowManager
	{
	public:

		static void create(sf::RenderWindow* window);
		static sf::RenderWindow* Get();
		static void clear();

	private:
		static sf::RenderWindow* m_window;
	};
}

