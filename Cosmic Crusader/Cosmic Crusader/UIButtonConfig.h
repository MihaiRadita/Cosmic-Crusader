#pragma once
#include "GameObjectConfig.h"

namespace ratchet
{
	enum class ButtonNameState {
		None = 0, Play, Options,
		Back_Value,Next_Value,
		Swicther_On, Switcher_Off,
		Back, Exit
	};

	struct UIButtonConfig : public GameObjectConfig
	{
	public:
		UIButtonConfig();
		~UIButtonConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;


	private:
		ButtonNameState m_nameState;
		ButtonNameState m_parentNameState;
		
	};

}


