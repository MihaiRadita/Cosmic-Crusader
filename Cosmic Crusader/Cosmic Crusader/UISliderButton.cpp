#include "stdafx.h"
#include "UISliderButton.h"



namespace ratchet
{
	UISliderButton::UISliderButton(const UISliderButtonConfig& config) : UIButton(config),
					m_minusButton(config.m_minusButtonConfig),
					m_plusButton(config.m_plusButtonConfig),
					m_UITitle(config.m_UITitleConfig),
					m_UITextValue(config.m_UITextValueConfig)
	{
		m_currentSliderValue = config.m_currentSliderValue;
		m_sliderValueIncreasse = config.m_sliderValueIncreasse;
		m_sliderMaxValue = config.m_sliderMaxValue;

	}
	UISliderButton::~UISliderButton()
	{

	}
	void UISliderButton::update()
	{
		m_position;
		if (!m_activeGameObject)
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

		if (m_plusButton.m_isButtonEventTirggered)
		{
			m_plusButton.m_isButtonEventTirggered = false;
		}

		if (m_minusButton.m_isButtonEventTirggered)
		{
			m_minusButton.m_isButtonEventTirggered = false;
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

	void UISliderButton::Start()
	{
		m_UITitle.Start();
		m_minusButton.Start();
		m_plusButton.Start();
		m_UITextValue.Start();
	}

	void UISliderButton::handleButtonsEvent(sf::Event& event)
	{
		m_plusButton.handleUIEvent(event);
		m_minusButton.handleUIEvent(event);
	}


	bool UISliderButton::checkIsButtonActive()
	{
		if (this->m_activeGameObject && this->m_activeRenderer)
		{
			return true;
		}

		return false;
	}

	void UISliderButton::setButtonActive(bool active)
	{
		this->SetActiveObject(active);
		this->SetActiveRenderer(active);

		m_UITitle.SetActiveObject(active);
		m_UITitle.SetActiveRenderer(active);

		m_UITextValue.SetActiveObject(active);
		m_UITextValue.SetActiveRenderer(active);

		m_plusButton.SetActiveObject(active);
		m_plusButton.SetActiveRenderer(active);

		m_minusButton.SetActiveObject(active);
		m_minusButton.SetActiveRenderer(active);
	}

	float UISliderButton::getSliderValueModified()
	{
		{
			if (m_plusButton.m_isButtonEventTirggered)
			{
				m_currentSliderValue += m_sliderValueIncreasse;

				if (m_currentSliderValue > m_sliderMaxValue)
				{
					m_currentSliderValue = m_sliderMaxValue;
				}

				m_UITextValue.setNumberValue(m_currentSliderValue);
			}
			else if (m_minusButton.m_isButtonEventTirggered)
			{
				m_currentSliderValue -= m_sliderValueIncreasse;

				if (m_currentSliderValue < 0.0f)
				{
					m_currentSliderValue = 0.0f;
				}

				m_UITextValue.setNumberValue(m_currentSliderValue);
			}
		}

		return m_currentSliderValue;
	}
}