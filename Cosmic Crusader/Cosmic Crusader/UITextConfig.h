#pragma once

#include "GameObjectConfig.h"

namespace ratchet
{
	enum class UITextType {
		None = 0, Text, Number 
	};

	struct UITextConfig : public GameObjectConfig
	{
		UITextType m_TextType;
		float m_textSize;
		sf::Color m_textColor;
		std::string m_TextValue;
		std::string m_textFontPath;

		UITextConfig();
		~UITextConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;
	};

}

