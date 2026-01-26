#include "stdafx.h"
#include "Timer.h"

namespace ratchet
{
	Timer::Timer()
	{
		m_clock.restart();
		m_accumulatedTime = sf::Time::Zero;
		m_isRunning = true;

	}

	Timer::~Timer()
	{

	}
	void Timer::Restart()
	{
		m_accumulatedTime = sf::Time::Zero;
		m_clock.restart();
		m_isRunning = true;
	}
	sf::Time Timer::GetElapsed() const
	{
		if (m_isRunning)
		{
			return m_accumulatedTime + m_clock.getElapsedTime();
		}

		return m_accumulatedTime;
	}
	void Timer::Freeze()
	{
		if (m_isRunning)
		{
			m_accumulatedTime += m_clock.getElapsedTime();
			m_isRunning = false;
		}
	}
	void Timer::Resume()
	{

		if (!m_isRunning)
		{
			m_clock.restart();
			m_isRunning = true;
		}
	}
}