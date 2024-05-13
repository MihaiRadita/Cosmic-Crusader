#pragma once

#include "RectAngleCollider.h"

class Tile
{
private:
	sf::Sprite tileSprite;
	sf::Texture textureSheet;

	sf::Vector2f tilePosition;
	sf::Vector2f tileScale;

	RectAngleCollider* tileCollider;
public:
	
	//Constructors
	Tile();

	//Destructors
	~Tile();
	void DestroyCollider();

	//Init functions
	void InitVariables();
	void InitTextures();
	void InitSprite();
	void InitPhysics();

	//Update
	void update();

	//Render
	void render(sf::RenderTarget& target);

	//Getters
	sf::Sprite GetTileSprite();
	
	//Setters
	void SetPosition(float x, float y);
	void SetScale(float x, float y);
};

