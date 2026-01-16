#include "stdafx.h"
#include "UISliderButton.h"



namespace ratchet
{
	UISliderButton::UISliderButton(UISliderButtonConfig& config) : UIButton(config),
					m_minusButton(config.m_minusButtonConfig),
					m_plusButton(config.m_plusButtonConfig),
					m_UITitle(config.m_UITitleConfig),
					m_UITextValue(config.m_UITextValueConfig)
	{
		m_nameState = config.m_nameState;
		m_parentNameState = config.m_parentNameState;
		m_buttonNameAction = config.m_buttonNameAction;

		m_currentSliderValue = config.m_currentSliderValue;
		m_sliderValueIncreasse = config.m_sliderValueIncreasse;

	}
	UISliderButton::~UISliderButton()
	{

	}
	void UISliderButton::update()
	{
		if (m_activeGameObject)
		{
			return;
		}
		
		m_UITitle.update();
		m_minusButton.update();
		m_plusButton.update();
		m_UITextValue.update();

		float volume;

		switch (m_nameAction)
		{
		case ButtonNameAction::MusicVolume:
			volume = getSliderValueModified();
			break;

		default:
			break;

		}
		
	}
	void UISliderButton::render(sf::RenderTarget& target)
	{
		if (!m_activeRenderer)
		{
			return;
		}

		m_UITitle.render(target);
		m_UITextValue.render(target);

		m_plusButton.render(target);
		m_minusButton.render(target);
	}

	float UISliderButton::getSliderValueModified()
	{
		if (m_nameAction == m_plusButton.getButtonNameAction())
		{
			if (m_plusButton.m_isButtonEventTirggered)
			{
				m_currentSliderValue += m_sliderValueIncreasse;

				m_UITextValue.setNumberValue(m_currentSliderValue);
			}
			else if (m_minusButton.m_isButtonEventTirggered)
			{
				m_currentSliderValue -= m_sliderValueIncreasse;

				m_UITextValue.setNumberValue(m_currentSliderValue);
			}
		}

		return m_currentSliderValue;
	}
}