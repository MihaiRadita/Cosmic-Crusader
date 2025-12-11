#include "stdafx.h"
#include "UIButton.h"


namespace ratchet
{
	UIButton::UIButton(UIButtonConfig& config) : GameObject(config)
	{
		m_nameState = config.m_nameState;
		m_parentNameState = config.m_parentNameState;
	}

	UIButton::~UIButton()
	{

	}

}