#pragma once

#include "Player.h"
#include "Physics.h"
#include "Tile.h"

class Game {

private:
	sf::RenderWindow m_window;
	sf::Event m_ev;

	Player* m_player;
	Physics* m_physics;
	Tile* m_ground;

public:
	//Constructors
	Game();

	//Destructors
	~Game();

	//Init functions
	void initWindow();
	void initPlayer();
	void initPhysics();
	void initMap();
	//Geters
	const sf::RenderWindow& getWindow() const;

	void handleEvents();

	//Update functions
	void update();
	void updatePlayer();
	void updatePhysics();
	void updateCollision();
	void updatePlayerCollision();
	void updateTile();


	//Render functions
	void render();
	void renderPlayer();
	void renderTile();

};