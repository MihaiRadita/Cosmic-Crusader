#include "stdafx.h"
#include "UIText.h"

namespace ratchet
{
	UIText::UIText(UITextConfig& config) : GameObject(config)
	{
		m_TextType = config.m_TextType;
		m_textSize = config.m_textSize;
		m_textColor = config.m_textColor;
		m_TextValue = config.m_TextValue;
		m_textFontPath = config.m_textFontPath;

		if (m_textFont.loadFromFile(m_textFontPath) == false)
		{
#ifdef IS_RATCHET_DEBUG
			TRACE_CHANNEL("GAMEOBJECT_INIT", "ERROR::TEXT COULD NOT LOAD THE FONT SHEET");
#endif
		}

		m_UIText.setFont(m_textFont);
		m_UIText.setCharacterSize(static_cast<int>(m_textSize));
		m_UIText.setFillColor(m_textColor);
		m_UIText.setString(m_TextValue);

	}
	UIText::~UIText()
	{

	}
	void UIText::update()
	{

	}
	void UIText::render(sf::RenderTarget& target)
	{
		if (!m_activeRenderer) return;

		target.draw(m_UIText);
	}
	bool UIText::checkNumberIfDifferent(float& value)
	{
		if (m_TextType != UITextType::Number)
			return false;

		float currentValue = 0.f;
		try
		{
			size_t pos = 0;
			currentValue = std::stof(m_TextValue, &pos);

			if (pos != m_TextValue.size())
			{
				return false;
			}
		}
		catch (...)
		{
			
			return false;
		}

		return value != currentValue;

	}
	void UIText::setNumberValue(float& value)
	{
		if (m_TextType != UITextType::Number)
		{
			return;
		}

		if (!checkNumberIfDifferent(value))
		{
			return;
		}

		std::ostringstream ss;
		ss << std::fixed << std::setprecision(1) << value;

		m_TextValue = ss.str();

		m_UIText.setString(m_TextValue);
	}
}