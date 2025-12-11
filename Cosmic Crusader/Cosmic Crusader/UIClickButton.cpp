#include "stdafx.h"
#include "UIClickButton.h"

namespace ratchet
{
	UIClickButton::UIClickButton(UIButtonConfig& config) : UIButton(config)
	{
		std::cout << "Button Created of type: "<<static_cast<int>(config.m_nameState) << std::endl;
	}
	UIClickButton::~UIClickButton()
	{

	}

}