#pragma once
#include "GameObject.h"

#include "PrefabAssets.h"


namespace ratchet
{
	class UIButton : public GameObject
	{
	public:

		UIButton(const UIButtonConfig& config);
		~UIButton();

		void update() override;
		void render(sf::RenderTarget& target) override;

		void handleUIEvent(sf::Event& event);

		bool checkUIButtonInteraction();

		virtual void setButtonsSectionActive(bool active);
		virtual void setButtonActive(bool active);


		virtual bool checkIsButtonActive();

		bool m_isButtonInteracting = false;
		bool m_isButtonEventTirggered = false;

		ButtonNameState getButtonNameState();
		ButtonNameState getParentButtonNameState();
		ButtonNameAction getButtonNameAction();
		bool getIsButtonInteracting();
		bool getIsButtonEventTriggerd();

		ButtonNameState m_nameState;
		ButtonNameState m_parentNameState;
		ButtonNameAction m_nameAction;

		bool m_isEventAllreadyActive = false;

	protected:


	};
}

