#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	enum class UITextType {
		None = 0, Text, Number 
	};

	enum class TextConnectedObject {
		None = 0, Play, NewGame, Continue, Resume, Options, Slider,
		Back_Value, Next_Value,
		Swicther_On, Switcher_Off,
		Back, Quit, Exit
	};

	enum class TextConnectedActionObject {
		None = 0, MusicVolume, SoundEffectVo1lume,
		Resolution
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

		TextConnectedActionObject m_textConnectedActionObject;

		UITextConfig();
		~UITextConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;
	};

}

