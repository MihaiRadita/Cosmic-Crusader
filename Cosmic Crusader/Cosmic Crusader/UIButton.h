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

		void handleUIEvent(sf::Event& event);

		bool checkUIButtonInteraction();

		bool m_isButtonInteracting = false;
		bool m_isButtonEventTirggered = false;

		ButtonNameState getButtonNameState();
		bool getIsButtonInteracting();
		bool getIsButtonEventTriggerd();

	protected:

		ButtonNameState m_nameState;
		ButtonNameState m_parentNameState;

	};
}

