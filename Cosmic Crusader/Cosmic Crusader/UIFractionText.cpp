#include "stdafx.h"
#include "UIFractionText.h"

namespace ratchet
{
	UIFractionText::UIFractionText(UIFractionTextConfig& config) : GameObject(config),
		m_currentValue(config.m_currentValueConfig),
		m_maxValue(config.m_maxValueConfig),
		m_fractionSeparator(config.m_fractionSeparator)
	{

	}

	UIFractionText::~UIFractionText()
	{

	}

	void UIFractionText::SetMaxValue(int value)
	{
		m_maxValue.setNumberIntegerValue(value);
	}

	void UIFractionText::update()
	{

	}

	void UIFractionText::render(sf::RenderTarget& target)
	{
		if (m_activeRenderer)
		{
			m_currentValue.render(target);
			m_fractionSeparator.render(target);
			m_maxValue.render(target);
		}

	}

	void UIFractionText::Start()
	{

		m_currentValue.Start();
		m_fractionSeparator.Start();
		m_maxValue.Start();
	}

	void UIFractionText::SetCurrentValue(int value)
	{
		m_currentValue.setNumberIntegerValue(value);
	}
}