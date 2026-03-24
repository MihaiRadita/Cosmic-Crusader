#include "stdafx.h"
#include "UIButton.h"

#include "WindowManager.h"

#include "SceneManager.h"

namespace ratchet
{
	UIButton::UIButton(const UIButtonConfig& config) : GameObject(config)
	{
		m_nameState = config.m_nameState;
		m_parentNameState = config.m_parentNameState;
		m_nameAction = config.m_nameAction;
		m_nameSection = config.m_nameSection;
		m_BackNameSection = config.m_BackNameSection;
		m_NextNameSection = config.m_NextNameSection;
		m_isButtonInteracting = false;
		m_isButtonEventTirggered = false;

		m_isEventAllreadyActive = false;

		m_uiButtonOffsetX = config.m_uiButtonOffsetX;
		m_uiButtonOffsetY = config.m_uiButtonOffsetY;

		m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, 150));

		m_uiButtonInteractSoundPath = config.m_uiButtonInteractSoundPath;
		m_uiButtonPressedSoundPath = config.m_uiButtonPressedSoundPath;

	}

	UIButton::~UIButton()
	{

	}

	void UIButton::update()
	{

		wasButtonIteracting = m_isButtonInteracting;
		m_isButtonInteracting = checkUIButtonInteraction();

		if (m_isButtonInteracting)
		{

			auto& name = m_nameState;
			m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, 255));
			if (m_skipInteractionThisFrame)
			{
				m_skipInteractionThisFrame = false;
				return;
			}
			else if(!m_skipInteractionThisFrame)
			{
				if (wasButtonIteracting != m_isButtonInteracting)
				{
					m_uiButtonInteractSound.play();
				}
			}
		}
		else
		{
			m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, 150));
		}
		
	}

	void UIButton::render(sf::RenderTarget& target)
	{
		GameObject::render(target);
	}

	void UIButton::handleUIEvent(sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
		{
			if (!m_isEventAllreadyActive)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_isButtonInteracting)
					{
						m_isEventAllreadyActive = true;
						m_isButtonEventTirggered = true;
					}
				}
			}

			break;
		}
		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_isButtonEventTirggered = false;
				m_isEventAllreadyActive = false;
			}

			break;
		}
		default:
			break;
		}

	}

	bool UIButton::checkUIButtonInteraction()
	{
		if (!checkIsButtonActive())
		{
			return false;
		}

		return checkUIButtonInteractionRaw();
	}

	bool UIButton::checkUIButtonInteractionRaw()
	{
		auto mousePosition = sf::Mouse::getPosition(*WindowManager::Get());
		auto mouseWorldPosition = WindowManager::Get()->mapPixelToCoords(
			mousePosition,
			SceneManager::Get().GetUIView()
		);

		return (
			mouseWorldPosition.x >= m_sprite.getPosition().x &&
			mouseWorldPosition.x <= (m_sprite.getPosition().x + m_sprite.getGlobalBounds().width) &&
			mouseWorldPosition.y >= m_sprite.getPosition().y &&
			mouseWorldPosition.y <= (m_sprite.getPosition().y + m_sprite.getGlobalBounds().height)
			);

	}


	void UIButton::setButtonsSectionActive(bool active)
	{

	}

	void UIButton::setButtonActive(bool active)
	{

	}

	void UIButton::setAllButtonsActive(bool active)
	{

	}

	void UIButton::Start()
	{
		auto& name = m_nameState;
		sf::View view = SceneManager::Get().GetUIView();
		sf::Vector2f center = view.getCenter();
		m_sprite.setPosition(sf::Vector2f(SceneManager::Get().GetUIView().getCenter().x + m_uiButtonOffsetX,
							 SceneManager::Get().GetUIView().getCenter().y + m_uiButtonOffsetY));

		if (!m_uiButtonInteractSoundBuffer.loadFromFile(m_uiButtonInteractSoundPath))
		{
			std::cout << "Sound not loaded!" << std::endl;
		}


		if (!m_uiButtonPressedSoundBuffer.loadFromFile(m_uiButtonPressedSoundPath))
		{
			std::cout << "Sound not loaded!" << std::endl;
		}

		m_uiButtonInteractSound = sf::Sound();
		m_uiButtonInteractSound.setBuffer(m_uiButtonInteractSoundBuffer);
		m_uiButtonInteractSound.setLoop(false);
		m_uiButtonInteractSound.setVolume(5.f);

		m_uiButtonPressedSound = sf::Sound();
		m_uiButtonPressedSound.setBuffer(m_uiButtonPressedSoundBuffer);
		m_uiButtonPressedSound.setLoop(false);
		m_uiButtonPressedSound.setVolume(5.f);
	}

	bool UIButton::checkIsButtonActive()
	{
		return false;
	}

	ButtonNameState UIButton::getButtonNameState()
	{
		return m_nameState;
	}

	ButtonNameState UIButton::getParentButtonNameState()
	{
		return m_parentNameState;
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