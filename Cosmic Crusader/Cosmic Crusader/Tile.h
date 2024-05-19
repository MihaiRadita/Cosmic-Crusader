#pragma once

#include "RectAngleCollider.h"

class Tile
{
private:
	sf::Sprite m_tileSprite;
	sf::Texture m_textureSheet;

	sf::Vector2f m_tileScale;
	sf::Vector2f m_spriteBackgroundScale;
	sf::Vector2f m_spriteBackGroundPosition;


	RectAngleCollider* m_collider;

public:
	
	//Constructors
	Tile();

	//Destructors
	~Tile();
	void destroyCollider();

	//Init functions
	void initVariables();
	void initTextures();
	void initSprite();
	void initPhysics();
	void init();

	//Update
	void update();

	//Render
	void render(sf::RenderTarget& target);

	//Getters
	sf::Sprite getTileSprite();

	RectAngleCollider* getTileCollider();

	//Setters
	void setPosition(float x, float y);
	void setScale(float x, float y);

	void printSpriteColliderTilePosition();

	sf::Vector2f getBackGroundScale();
};

