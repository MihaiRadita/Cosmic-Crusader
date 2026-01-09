#include "stdafx.h"
#include "UIButton.h"

#include "WindowManager.h"

namespace ratchet
{
	UIButton::UIButton(UIButtonConfig& config) : GameObject(config)
	{
		m_nameState = config.m_nameState;
		m_parentNameState = config.m_parentNameState;
		m_isButtonInteracting = false;
		m_isButtonEventTirggered = false;
	}

	UIButton::~UIButton()
	{

	}

	void UIButton::update()
	{

	}

	void UIButton::handleUIEvent(sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (m_isButtonInteracting)
				{
					m_isButtonEventTirggered = true;
				}
			}
		}
		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_isButtonEventTirggered = false;
			}
		}
		default:
			break;
		}

		if (event.MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (m_isButtonInteracting)
				{
					m_isButtonEventTirggered = true;
				}
				else
				{
					m_isButtonEventTirggered = false;
				}
			}
		}
		else if(event.MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_isButtonEventTirggered = false;
			}
		}
	}

	bool UIButton::checkUIButtonInteraction()
	{
		auto mousePosition = sf::Mouse::getPosition(*WindowManager::Get());
		auto mouseWorldPosition = WindowManager::Get()->mapPixelToCoords(mousePosition);

		if ((mouseWorldPosition.x >= m_sprite.getPosition().x && mouseWorldPosition.x <= (m_sprite.getPosition().x + m_sprite.getGlobalBounds().width))
			&& (mouseWorldPosition.y >= m_sprite.getPosition().y && mouseWorldPosition.y <= (m_sprite.getPosition().y + m_sprite.getGlobalBounds().height)))
		{
			return true;
		}

		return false;
	}

	ButtonNameState UIButton::getButtonNameState()
	{
		return m_nameState;
	}

	bool UIButton::getIsButtonInteracting()
	{
		return m_isButtonInteracting;
	}

	bool UIButton::getIsButtonEventTriggerd()
	{
		return m_isButtonEventTirggered;
	}

}