#pragma once

#include "UIButton.h"
#include "UIClickButton.h"
#include "UIText.h"

namespace ratchet
{
	class UISliderButton : public UIButton
	{
	public:
		UISliderButton(const UISliderButtonConfig& config);
		~UISliderButton();

		float m_currentSliderValue;
		float m_sliderValueIncreasse;
		float m_sliderMaxValue;

		void update() override;
		void render(sf::RenderTarget& target) override;

		void handleButtonsEvent(sf::Event& event);

		bool checkIsButtonActive() override;

		void setButtonActive(bool active) override;

		UIClickButton m_minusButton;
		UIClickButton m_plusButton;

		UIText m_UITitle;
		UIText m_UITextValue;
		//ButtonNameAction m_nameAction;

		float getSliderValueModified();

	private:

	};
}

