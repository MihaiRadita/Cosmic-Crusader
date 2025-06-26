#pragma once

#include "game/Player.h"
#include "game/Tile.h"

#include "GameObject.h"

#include "WeaponPickup.h"

#include "physics/Physics.h"

#include "WindowManager.h"

#include "PrefabAssets.h"

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
		void initMap();
		void initWeaponManager();
		//Geters
		const sf::RenderWindow& getWindow() const;

		void handleEvents();

		//Update functions
		void update();
		void updatePlayer();
		void updatePhysics();
		
		


		//Spawners
		void spawnObjects();

		//Render functions
		void render();
		void renderPlayer();
		void renderTile();
	};
}