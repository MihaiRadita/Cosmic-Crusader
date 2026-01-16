#pragma once
#include "GameObject.h"

#include "PrefabAssets.h"


namespace ratchet
{
	class UIButton : public GameObject
	{
	public:

		UIButton(UIButtonConfig& config);
		~UIButton();

		void update() override;
		void render(sf::RenderTarget& target) override;

		void handleUIEvent(sf::Event& event);

		bool checkUIButtonInteraction();

		bool m_isButtonInteracting = false;
		bool m_isButtonEventTirggered = false;

		ButtonNameState getButtonNameState();
		ButtonNameState getParentButtonNameState();
		ButtonNameAction getButtonNameAction();
		bool getIsButtonInteracting();
		bool getIsButtonEventTriggerd();

	protected:

		ButtonNameState m_nameState;
		ButtonNameState m_parentNameState;
		ButtonNameAction m_nameAction;

	};
}

