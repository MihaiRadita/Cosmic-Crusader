#include "stdafx.h"
#include "UISliderButton.h"

#include "SceneManager.h"

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
		auto& action = m_nameAction;

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



		switch (m_nameAction)
		{
		case ButtonNameAction::MusicVolume:
		{
			if (m_currentSliderValue != SceneManager::Get().GetMusicVolume())
			{
				m_currentSliderValue = SceneManager::Get().GetMusicVolume();
				m_UITextValue.setNumberValue(m_currentSliderValue);
			}

			if (m_plusButton.m_isButtonEventTirggered || m_minusButton.m_isButtonEventTirggered)
			{
				float& value = getSliderValueModified();

				auto& currentVolume = SceneManager::Get().GetMusicVolume();
				currentVolume = value;

				m_UITextValue.setNumberValue(currentVolume);
			}


			break;
		}

		case ButtonNameAction::Resolution:
		{
			if (m_currentSliderValue != static_cast<float>(SceneManager::Get().GetCurrentResolution()))
			{
				m_currentSliderValue = static_cast<float>(SceneManager::Get().GetCurrentResolution());
				m_UITextValue.setTextValue(
					SceneManager::Get().m_resolutions[SceneManager::Get().GetCurrentResolution()].name
				);
			}


			if (m_plusButton.m_isButtonEventTirggered || m_minusButton.m_isButtonEventTirggered)
			{
				float& value = getSliderValueModified();
				Resolution selectedResolution = static_cast<Resolution>((int)value);

				auto& currentResolution = SceneManager::Get().GetCurrentResolution();
				currentResolution = selectedResolution;

				m_UITextValue.setTextValue(
					SceneManager::Get().m_resolutions[selectedResolution].name
				);
			}

			break;
		}

		default:
		{
			break;
		}
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
		m_UITextValue.m_textConnetedToActionObject = m_nameAction;

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

	float& UISliderButton::getSliderValueModified()
	{
		{
			if (m_plusButton.m_isButtonEventTirggered)
			{
				m_currentSliderValue += m_sliderValueIncreasse;

				if (m_currentSliderValue > m_sliderMaxValue)
				{
					m_currentSliderValue = m_sliderMaxValue;
				}


			}
			else if (m_minusButton.m_isButtonEventTirggered)
			{
				m_currentSliderValue -= m_sliderValueIncreasse;

				if (m_currentSliderValue < 0.0f)
				{
					m_currentSliderValue = 0.0f;
				}

			}
		}

		return m_currentSliderValue;
	}
}