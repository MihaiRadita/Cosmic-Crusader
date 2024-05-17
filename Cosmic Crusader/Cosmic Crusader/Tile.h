#pragma once

#include "RectAngleCollider.h"

class Tile
{
private:
	sf::Sprite tileSprite;
	sf::Texture textureSheet;

	sf::Vector2f tilePosition;
	sf::Vector2f tileScale;
	sf::Vector2f spriteBackgroundScale;
	sf::Vector2f spriteBackGroundPosition;


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
	void Init();

	//Update
	void update();

	//Render
	void render(sf::RenderTarget& target);

	//Getters
	sf::Sprite GetTileSprite();

	RectAngleCollider* GetTileCollider();

	//Setters
	void SetPosition(float x, float y);
	void SetScale(float x, float y);

	void PrintSpriteColliderTilePosition();

	sf::Vector2f GetBackGroundScale();
};

