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


		sf::Text m_UIText;

		UIText(UITextConfig& config);
		~UIText();

		void update() override;
		void render(sf::RenderTarget& target) override;

		bool checkNumberIfDifferent(float& value);

		void setNumberValue(float& value);

	private:
	};
}

