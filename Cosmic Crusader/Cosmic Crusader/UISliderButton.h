#pragma once

#include "UIButton.h"
#include "UIClickButton.h"
#include "UIText.h"

namespace ratchet
{
	class UISliderButton : public UIButton
	{
	public:
		UISliderButton(UISliderButtonConfig& config);
		~UISliderButton();

		ButtonNameAction m_buttonNameAction;
		ButtonNameState m_buttonNameState;
		ButtonNameState m_buttonParentNameState;

		float m_currentSliderValue;
		float m_sliderValueIncreasse;
		float m_sliderMaxValue;

		void update() override;
		void render(sf::RenderTarget& target) override;

		UIClickButton m_minusButton;
		UIClickButton m_plusButton;

		UIText m_UITitle;
		UIText m_UITextValue;

		float getSliderValueModified();

	private:

	};
}

