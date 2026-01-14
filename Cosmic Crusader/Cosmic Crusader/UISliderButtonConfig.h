#pragma once

#include "UIButtonConfig.h"

namespace ratchet
{
	struct UISliderButtonConfig : public UIButtonConfig
	{
		UISliderButtonConfig();

		~UISliderButtonConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;

		ButtonNameAction m_buttonNameAction;
		ButtonNameState m_buttonNameState;
		ButtonNameState m_buttonParentNameState;

		int m_currentSliderValue;
		int m_sliderValueIncreasse;

		UIButtonConfig m_minusButton;
		UIButtonConfig m_plusButton;


	};
}


