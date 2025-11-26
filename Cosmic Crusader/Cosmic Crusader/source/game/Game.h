#pragma once

#include "game/Player.h"
#include "game/Tile.h"

#include "GameObject.h"

#include "WeaponPickup.h"

#include "physics/Physics.h"

#include "WindowManager.h"

#include "PrefabAssets.h"

#include "SelfControlledCreature.h"

namespace ratchet
{
	class Game {
	private:
		sf::RenderWindow m_window;

		sf::Clock gameTime;
		float timeLastFrame = 0;

		sf::Vector2i currenmousePosition = sf::Vector2i(0,0);

	public:
		//Constructors
		Game();

		//Destructors
		~Game();

		//Init functions
		void initWindow();
		void initPhysics();
		void initWeaponManager();
		//Geters
		const sf::RenderWindow& getWindow() const;

		void handleEvents();

		//Update functions
		void update();
		void updatePhysics();
		
		void awake();
		void start();


		//Spawners
		void spawnObjects();

		//Render functions
		void render();

		inline static const float sc_tiledToGameScale = 0.01;
		inline static const float sc_defaultZoom = 2.0f * sc_tiledToGameScale;;
	};
}