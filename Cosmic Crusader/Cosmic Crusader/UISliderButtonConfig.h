#pragma once

#include "UIButtonConfig.h"
#include "UITextConfig.h"

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

		float m_currentSliderValue;
		float m_sliderValueIncreasse;

		UIButtonConfig m_minusButtonConfig;
		UIButtonConfig m_plusButtonConfig;

		UITextConfig m_UITitleConfig;
		UITextConfig m_UITextValueConfig;

	};
}


