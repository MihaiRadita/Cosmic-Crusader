#pragma once

#include "game/Player.h"
#include "game/Tile.h"

#include "GameObject.h"

#include "WeaponPickup.h"

#include "physics/Physics.h"

namespace ratchet
{
	class Game {
	private:
		sf::RenderWindow m_window;

		Physics* m_physics;

		sf::Clock gameTime;
		float timeLastFrame = 0;

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