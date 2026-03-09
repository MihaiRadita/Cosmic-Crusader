#include "stdafx.h"
#include "UIClickButton.h"

#include "WindowManager.h"

#include "SceneManager.h"

#include "UISliderButton.h"

namespace ratchet
{
	UIClickButton::UIClickButton(const UIButtonConfig& config) : UIButton(config)
	{
		std::cout << "Button Created of type: "<<static_cast<int>(config.m_nameState) << std::endl;

		s_gameObjects;
	}
	UIClickButton::~UIClickButton()
	{

	}

	void UIClickButton::update()
	{
		if (!m_activeGameObject)
		{
			return;
		}

		UIButton::update();

		if (m_isButtonEventTirggered)
		{
			switch (m_nameState)
			{
			case ButtonNameState::Play:
				setButtonsSectionActive(true);
				break;

			case ButtonNameState::Continue:
				WindowManager::Get()->clear(sf::Color::Black);
				WindowManager::Get()->display();

				m_isButtonInteracting = false;
				m_isButtonEventTirggered = false;

				SceneManager::Get().LoadNextScene();
				break;

			case ButtonNameState::NewGame:
				WindowManager::Get()->clear(sf::Color::Black);
				WindowManager::Get()->display();

				m_isButtonInteracting = false;
				m_isButtonEventTirggered = false;

				SceneManager::Get().SetNewGame();

				SceneManager::Get().LoadNextScene();
				break;

			case ButtonNameState::Exit:
				WindowManager::Get()->close();
				break;

			case ButtonNameState::Options:
				setButtonsSectionActive(true);
				break;
			case ButtonNameState::Resume:
				SceneManager::Get().SetGameScenePauseState();
				if (!SceneManager::Get().m_isPaused)
				{
					WindowManager::Get()->setKeyRepeatEnabled(true);
				}
				m_isButtonInteracting = false;
				m_isButtonEventTirggered = false;
				break;

			case ButtonNameState::Back:
				setButtonsSectionActive(false);
				break;

			case ButtonNameState::Next_Value:
				std::cout << "Plus Button!" << std::endl;
				break;

			case ButtonNameState::Back_Value:
				std::cout << "Minus Button!" << std::endl;
				break;

			case ButtonNameState::Quit:
				m_isButtonInteracting = false;
				m_isButtonEventTirggered = false;
				SceneManager::Get().m_characters_destroyed_ID.clear();
				SceneManager::Get().m_characters_destroyed_index.clear();
				SceneManager::Get().LoadNextScene();
			}
		}
	}

	void UIClickButton::render(sf::RenderTarget& target)
	{
		UIButton::render(target);
	}


	void UIClickButton::setButtonsSectionActive(bool active)
	{
		if (active == this->checkIsButtonActive())
		{
			m_isEventAllreadyActive = !active;
			m_isButtonInteracting = !active;
			this->setButtonActive(!active);
			m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, 150));
		}
		else if(active != this->checkIsButtonActive())
		{
			m_isEventAllreadyActive = active;
			m_isButtonInteracting = active;
			this->setButtonActive(active);
			m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, 150));
		}

		for (auto& obj : s_gameObjects)
		{
			if (auto uiText = dynamic_cast<UIText*>(obj))
			{
				if ((int)uiText->m_textConnectedObject == (int)this->m_nameState)
				{
					uiText->setUITextActive(active);
				}
				else if ((int)uiText->m_textConnectedObject == (int)this->m_parentNameState)
				{
					uiText->setUITextActive(active);
				}
			}

			if (obj->m_objectType == ObjectType::UI)
			{
				if (obj == this)
				{
					continue;
				}
				if (auto* ui = dynamic_cast<UIClickButton*>(obj))
				{
					if (active)
					{
						if (ui->m_nameSection == m_nameSection)
						{
							m_isButtonInteracting = !active;
							m_isEventAllreadyActive = !active;
							ui->setButtonActive(!active);
						}
						else if (ui->m_nameSection == m_NextNameSection)
						{
							m_isEventAllreadyActive = active;
							m_isButtonInteracting = active;
							ui->setButtonActive(active);

						}
					}
					else
					{
						
						if (ui->m_nameSection == m_nameSection)
						{
							m_isButtonInteracting = active;
							m_isEventAllreadyActive = active;
							ui->setButtonActive(active);
						}
						else if (ui->m_nameSection == m_BackNameSection)
						{
							m_isEventAllreadyActive = !active;
							m_isButtonInteracting = !active;
							ui->setButtonActive(!active);

						}
					}
	
				}
				else if (auto* ui = dynamic_cast<UISliderButton*>(obj))
				{
					if (active)
					{
						if (ui->m_nameSection == m_nameSection)
						{
							m_isButtonInteracting = !active;
							m_isEventAllreadyActive = !active;
							ui->setButtonActive(!active);
						}
						else if (ui->m_nameSection == m_NextNameSection)
						{
							m_isEventAllreadyActive = active;
							m_isButtonInteracting = active;
							ui->setButtonActive(active);

						}
					}
					else
					{

						if (ui->m_nameSection == m_nameSection)
						{
							m_isButtonInteracting = active;
							m_isEventAllreadyActive = active;
							ui->setButtonActive(active);
						}
						else if (ui->m_nameSection == m_BackNameSection)
						{
							m_isEventAllreadyActive = !active;
							m_isButtonInteracting = !active;
							ui->setButtonActive(!active);

						}
					}
				}
			}
		}
	}

	void UIClickButton::setButtonActive(bool active)
	{
		this->SetActiveObject(active);
		this->SetActiveRenderer(active);
	}

	void UIClickButton::setAllButtonsActive(bool active)
	{

	}

	bool UIClickButton::checkIsButtonActive()
	{
		if (this->m_activeGameObject && this->m_activeRenderer)
		{
			return true;
		}

		return false;
	}

}