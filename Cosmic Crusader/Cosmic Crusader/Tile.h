#pragma once

#include "RectAngleCollider.h"

class Tile
{
private:
	sf::Sprite tileSprite;
	sf::Texture tileTextures;

	sf::Vector2f tilePosition;
	sf::Vector2f tileScale;
public:
	
	//Constructors
	Tile();

	//Destructors
	~Tile();

	//Init functions
	void InitVariables();
	void InitTextures();
	void InitSprite();
	void InitPhysics();

	//Update
	void update();

	//Render
	void render();

	//Getters
	

};

