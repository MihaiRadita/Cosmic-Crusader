#pragma once

#include "Player.h"

class Game {

private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;

public:
	//Constructors
	Game();

	//Destructors
	~Game();

	//Init functions
	void initWindow();
	void initPlayer();

	//Geters
	const sf::RenderWindow& GetWindow() const;

	//Update functions
	void update();
	void updatePlayer();
	void updateCollision();

	//Render functions
	void render();
	void renderPlayer();

};