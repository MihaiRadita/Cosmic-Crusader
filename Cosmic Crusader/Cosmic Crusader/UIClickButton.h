#pragma once
#include "UIButton.h"

namespace ratchet
{
	class UIClickButton : public UIButton
	{
	public:

		UIClickButton(UIButtonConfig& config);

		~UIClickButton();

		void update() override;
		void render(sf::RenderTarget& target) override;

	private:

	};
}

