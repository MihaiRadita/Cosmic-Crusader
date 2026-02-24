#pragma once

#include "game/Player.h"
#include "game/Tile.h"

#include "GameObject.h"

#include "SceneManager.h"

#include "WeaponPickup.h"

#include "physics/Physics.h"

#include "WindowManager.h"

#include "PrefabAssets.h"

#include "SelfControlledCreature.h"

#include "Checkpoint.h"

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


		//Spawner
		void spawnObjects();

		void applySceneView();

		//Render functions
		void render();
	};
}