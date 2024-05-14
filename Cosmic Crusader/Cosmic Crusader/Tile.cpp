#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
	this->DestroyCollider();
}

void Tile::DestroyCollider()
{
	this->tileCollider = nullptr;
	delete this->tileCollider;
}

void Tile::InitVariables()
{
	this->tileScale = sf::Vector2f(1.f, 1.f);
}

void Tile::InitTextures()
{
	if (this->textureSheet.loadFromFile("Textures/Levels/Level1/Tileset/Tile7.png") == false)
	{
		std::cout << "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET" << std::endl;
	}
}

void Tile::InitSprite()
{
	this->tileSprite.setTexture(this->textureSheet);
	//this->tileSprite.setScale(this->tileScale);
}

void Tile::InitPhysics()
{
	this->tileCollider = new RectAngleCollider(this->tileSprite, STATIC);

	this->tileCollider->SetColliderPosition(this->tileSprite);
}

void Tile::Init()
{
	this->InitTextures();
	this->InitSprite();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tileSprite);
}

sf::Sprite Tile::GetTileSprite()
{
	return this->tileSprite;
}

RectAngleCollider* Tile::GetTileCollider()
{
	return this->tileCollider;
}

void Tile::SetPosition(float x, float y)
{
	this->tileSprite.setPosition(x, y);
}

void Tile::SetScale(float x, float y)
{
	this->tileSprite.setScale(x, y);
}

