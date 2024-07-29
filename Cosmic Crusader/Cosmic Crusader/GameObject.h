#pragma once
#include "GameObjectConfig.h"

namespace ratchet
{
	class GameObject
	{
	public:
		//Constructor
		GameObject(const GameObjectConfig& config);

		//Destructor
		~GameObject();

		virtual void init();
		virtual void update();
		virtual void destroy();


	};

}

