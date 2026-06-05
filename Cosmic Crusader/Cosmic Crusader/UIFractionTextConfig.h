#pragma once

#include "UITextConfig.h"

namespace ratchet
{
	struct UIFractionTextConfig : public GameObjectConfig
	{
		UIFractionTextConfig();
		~UIFractionTextConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;

		float m_currentSliderValue;
		float m_sliderValueIncreasse;
		float m_sliderMaxValue;

		UITextConfig m_currentValueConfig;
		UITextConfig m_maxValueConfig;
		UITextConfig m_fractionSeparator;

		
	};
}


