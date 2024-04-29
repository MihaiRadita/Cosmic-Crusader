#pragma once

#include "Player.h"
#include "Physics.h"

class Game {

private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;
	Physics* physics;


public:
	//Constructors
	Game();

	//Destructors
	~Game();

	//Init functions
	void initWindow();
	void initPlayer();
	void initPhysics();
	//Geters
	const sf::RenderWindow& GetWindow() const;

	void handleEvents();

	//Update functions
	void update();
	void updatePlayer();
	void updatePhysics();
	void updateCollision();
	void updatePlayerCollision();

	//Render functions
	void render();
	void renderPlayer();

};