#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	enum class UITextType {
		None = 0, Text, Number 
	};

	enum class TextConnectedObject {
		None = 0, Play, Resume, Options, Slider,
		Back_Value, Next_Value,
		Swicther_On, Switcher_Off,
		Back, Quit, Exit
	};

	struct UITextConfig : public GameObjectConfig
	{
		UITextType m_TextType;
		float m_textSize;
		sf::Color m_textColor;
		std::string m_TextValue;
		std::string m_textFontPath;

		TextConnectedObject m_textConnectedObject;

		float m_XUnit = 64.f;
		float m_YUnit = 64.f;

		float m_uiTextOffsetX;
		float m_uiTextOffsetY;

		UITextConfig();
		~UITextConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;
	};

}

