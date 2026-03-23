#pragma once
#include "GameObjectConfig.h"

namespace ratchet
{
	enum class ButtonNameState {
		None = 0, Play,NewGame,Continue,Resume, Options,Slider,
		Back_Value,Next_Value,
		Swicther_On, Switcher_Off,
		Back,Quit, Exit
	};

	enum class ButtonNameSection
	{
		None = 0,MainSection, PlaySection,OptionSection
	};

	enum class ButtonNameAction
	{
		None = 0, MusicVolume, SoundEffectVolume, 
		Resolution
	};

	struct UIButtonConfig : public GameObjectConfig
	{
		UIButtonConfig();
		~UIButtonConfig();

		virtual bool serialise(nlohmann::json& jsonFile) override;
		virtual bool deserialise(const nlohmann::json& jsonFile) override;

		ButtonNameState m_nameState;
		ButtonNameState m_parentNameState;
		ButtonNameAction m_nameAction;

		ButtonNameSection m_BackNameSection;
		ButtonNameSection m_nameSection;
		ButtonNameSection m_NextNameSection;

		float m_uiButtonOffsetX;
		float m_uiButtonOffsetY;

		std::string m_uiButtonInteractSoundPath;
		std::string m_uiButtonPressedSoundPath;
		
	};

}


