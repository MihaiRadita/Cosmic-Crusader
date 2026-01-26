#pragma once

namespace ratchet
{
	class Timer
	{
	public:

		Timer();

		~Timer();

		sf::Clock m_clock;
		sf::Time m_accumulatedTime = sf::Time::Zero;

		sf::Time time;

		bool m_isRunning;

		void Restart();

		sf::Time GetElapsed() const;

		void Freeze();
		void Resume();

	private:
	};

}


