#pragma once

#include "game/Player.h"
#include "game/Tile.h"

#include "GameObject.h"

#include "physics/Physics.h"

namespace ratchet
{
	class Game {
	private:
		sf::RenderWindow m_window;
		sf::Event m_ev;

		Physics* m_physics;
		std::vector<GameObject*> m_gameObjects;

		sf::Clock gameTime;
		sf::Int32 timeLastFrame = 0;

	public:
		//Constructors
		Game();

		//Destructors
		~Game();

		//Init functions
		void initWindow();
		void initPhysics();
		void initMap();
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