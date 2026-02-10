#pragma once

#include "GameObject.h"

#include "PrefabAssets.h"

namespace ratchet
{
	class UIText : public GameObject 
	{
	public:
		UITextType m_TextType;
		float m_textSize;
		sf::Color m_textColor;
		std::string m_TextValue;
		std::string m_textFontPath;
		sf::Font m_textFont;

		TextConnectedObject m_textConnectedObject;


		sf::Text m_UIText;

		UIText() = default;
		UIText(const UITextConfig& config);
		~UIText();

		void Start() override;

		void update() override;
		void render(sf::RenderTarget& target) override;
		void setUITextActive(bool active);

		bool checkNumberIfDifferent(float& value);

		void setNumberValue(float& value);

		float m_uiTextOffsetX;
		float m_uiTextOffsetY;

	private:
	};
}

