#pragma once
#include "UIButton.h"

namespace ratchet
{
	class UIClickButton : public UIButton
	{
	public:

		UIClickButton() = default;

		UIClickButton(const UIButtonConfig& config);

		~UIClickButton();

		void update() override;
		void render(sf::RenderTarget& target) override;

		void setButtonsSectionActive(bool active) override;
		void setButtonActive(bool active) override;

		bool checkIsButtonActive() override;

	private:

	};
}

