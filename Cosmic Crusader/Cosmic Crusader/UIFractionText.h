#pragma once

#include "UIText.h"

#include "PrefabAssets.h"

namespace ratchet
{
	class UIFractionText : public GameObject
	{
	public:
		UIFractionText(UIFractionTextConfig& config);

		~UIFractionText();

		UIText m_currentValue;
		UIText m_maxValue;
		UIText m_fractionSeparator;

		void SetCurrentValue(int value);
		void SetMaxValue(int value);

		void update() override;
		void render(sf::RenderTarget& target) override;
		

		void Start() override;

	private:
	};
}



