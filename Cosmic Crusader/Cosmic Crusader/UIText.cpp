#include "stdafx.h"
#include "UIText.h"

#include "SceneManager.h"

namespace ratchet
{
	UIText::UIText(const UITextConfig& config) : GameObject(config)
	{
		m_TextType = config.m_TextType;
		m_textSize = config.m_textSize;
		m_textColor = config.m_textColor;
		m_TextValue = config.m_TextValue;
		m_textFontPath = config.m_textFontPath;
		m_textConnectedObject = config.m_textConnectedObject;

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


		sf::FloatRect bounds = m_UIText.getLocalBounds();
		m_UIText.setOrigin(
			bounds.left + bounds.width / 2.f,
			bounds.top + bounds.height / 2.f
		);

		m_UIText.setPosition(m_position.x, m_position.y);
		m_UIText.setRotation(m_rotation);
		m_UIText.setScale(m_scale.x, m_scale.y);

		m_uiTextOffsetX = config.m_uiTextOffsetX;
		m_uiTextOffsetY = config.m_uiTextOffsetY;

	}
	UIText::~UIText()
	{

	}
	void UIText::Start()
	{
		sf::View view = SceneManager::Get().GetUIView();
		sf::Vector2f center = view.getCenter();

		sf::Vector2f bouns = sf::Vector2f(m_UIText.getLocalBounds().width, m_UIText.getLocalBounds().height);

		sf::Vector2f textOrgin = sf::Vector2f(m_UIText.getLocalBounds().width / 2.0f,
											   m_UIText.getLocalBounds().height /2.0f);
		m_UIText.setOrigin(textOrgin);
		m_UIText.setPosition(sf::Vector2f(SceneManager::Get().GetUIView().getCenter().x + m_uiTextOffsetX,
										  SceneManager::Get().GetUIView().getCenter().y + m_uiTextOffsetY));
	}
	void UIText::update()
	{
	}
	void UIText::render(sf::RenderTarget& target)
	{
		if (!m_activeRenderer) return;

		target.draw(m_UIText);
	}
	void UIText::setUITextActive(bool active)
	{
		this->SetActiveObject(active);
		this->SetActiveRenderer(active);
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
	void UIText::setTextValue(std::string& value)
	{
		std::ostringstream ss;

		ss << value;
		m_TextValue = ss.str();

		m_UIText.setString(m_TextValue);
	}
}