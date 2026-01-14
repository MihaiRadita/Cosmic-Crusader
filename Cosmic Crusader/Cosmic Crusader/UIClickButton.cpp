#include "stdafx.h"
#include "UIClickButton.h"

#include "WindowManager.h"

#include "SceneManager.h"

namespace ratchet
{
	UIClickButton::UIClickButton(UIButtonConfig& config) : UIButton(config)
	{
		std::cout << "Button Created of type: "<<static_cast<int>(config.m_nameState) << std::endl;

		s_gameObjects;
	}
	UIClickButton::~UIClickButton()
	{

	}

	void UIClickButton::update()
	{
		UIButton::update();

		if (m_isButtonEventTirggered)
		{
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
		}
	}

}