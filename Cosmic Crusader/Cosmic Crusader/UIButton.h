#pragma once
#include "GameObject.h"

#include "PrefabAssets.h"


namespace ratchet
{
	class UIButton : public GameObject
	{
	public:

		UIButton(UIButtonConfig& config);
		~UIButton();

	private:

		ButtonNameState m_nameState;
		ButtonNameState m_parentNameState;

	};
}

