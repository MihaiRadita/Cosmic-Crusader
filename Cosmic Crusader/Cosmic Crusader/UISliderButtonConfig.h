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

		float m_currentSliderValue;
		float m_sliderValueIncreasse;
		float m_sliderMaxValue;

		UIButtonConfig m_minusButtonConfig;
		UIButtonConfig m_plusButtonConfig;

		UITextConfig m_UITitleConfig;
		UITextConfig m_UITextValueConfig;

	};
}


