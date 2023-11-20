#pragma once

class Game {

private:
	sf::RenderWindow window;
	sf::Event ev;

public:
	Game();

	//Init functions
	void initWindow();

	//Geters
	const sf::RenderWindow& GetWindow() const;

	//Update functions
	void update();

	//Render functions
	void render();

};