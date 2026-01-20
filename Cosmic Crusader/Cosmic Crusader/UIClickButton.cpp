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
			auto state = m_nameState;
			if (m_nameState == ButtonNameState::Play)
			{
				WindowManager::Get()->clear(sf::Color::Black);
				WindowManager::Get()->display();

				m_isButtonInteracting = false;
				m_isButtonEventTirggered = false;

				SceneManager::Get().LoadNextScene();
			}
			else if (m_nameState == ButtonNameState::Exit)
			{
				WindowManager::Get()->close();
			}

			else if (m_nameState == ButtonNameState::Options)
			{
				setButtonsSectionActive(true);
			}

			else if (m_nameState == ButtonNameState::Back)
			{
				setButtonsSectionActive(false);
			}

			else if (m_nameState == ButtonNameState::Next_Value)
			{
				std::cout << "MInus Button!" << std::endl;
				//m_isButtonEventTirggered = true;
			}

			else if (m_nameState == ButtonNameState::Back_Value)
			{
				std::cout << "PLus Button!" << std::endl;
				//m_isButtonEventTirggered = true;
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
		}
		else if(active != this->checkIsButtonActive())
		{
			m_isEventAllreadyActive = active;
			m_isButtonInteracting = active;
			this->setButtonActive(active);
		}

		for (auto& obj : s_gameObjects)
		{
			if (obj->m_objectType == ObjectType::UI)
			{
				if (obj == this)
				{
					continue;
				}
				if (auto* ui = dynamic_cast<UIClickButton*>(obj))
				{
					if (ui->m_parentNameState != m_nameState)
					{

						if (active == true)
						{
							m_isEventAllreadyActive = !active;
							m_isButtonInteracting = !active;

						}
						else
						{
							m_isEventAllreadyActive = active;
							m_isButtonInteracting = active;
						}

						ui->setButtonActive(!active);

					}
					else if(ui->m_parentNameState == m_nameState)
					{
						if (ui->checkIsButtonActive() == checkIsButtonActive())
						{
							if (active == true)
							{
								m_isEventAllreadyActive = !active;
								m_isButtonInteracting = !active;

							}
							else
							{
								m_isEventAllreadyActive = active;
								m_isButtonInteracting = active;
							}
							ui->setButtonActive(active);

						}
					}
				}
				else if (auto* ui = dynamic_cast<UISliderButton*>(obj))
				{
					if (ui->getParentButtonNameState() != m_nameState)
					{
						if (active == true)
						{
							m_isEventAllreadyActive = !active;

							m_isButtonInteracting = !active;
						}
						else
						{
							m_isEventAllreadyActive = active;
						}
						m_isButtonInteracting = active;

						ui->setButtonActive(active);
					}
					else if (ui->getParentButtonNameState() == m_nameState)
					{
						if (ui->checkIsButtonActive() == checkIsButtonActive())
						{

							if (active == true)
							{
								m_isEventAllreadyActive = !active;
								m_isButtonInteracting = !active;

							}
							else
							{
								m_isEventAllreadyActive = active;
								m_isButtonInteracting = active;
							}
							ui->setButtonActive(active);
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

	bool UIClickButton::checkIsButtonActive()
	{
		if (this->m_activeGameObject && this->m_activeRenderer)
		{
			return true;
		}

		return false;
	}

}