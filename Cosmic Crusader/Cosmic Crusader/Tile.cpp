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
	if (this->textureSheet.loadFromFile("Textures/Levels/Level1/Tileset/Platform.png") == false)
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
	std::cout << "Ground Sprite " << this->tileSprite.getPosition().x << " , " << this->tileSprite.getPosition().y << std::endl;
	std::cout<<"Ground Collider " <<this->tileSprite.getPosition().y << " , "<< this->tileCollider->GetBody()->GetPosition().y<<std::endl;
}

void Tile::render(sf::RenderTarget& target)
{
	// DEBUG START
	// DRAW COLLIDER BEGIN AND END
	auto colliderOutline = sf::RectangleShape(sf::Vector2f(
		tileCollider->GetColliderScale()->x * 2.0f,
		tileCollider->GetColliderScale()->y * 2.0f)
	);
	colliderOutline.setFillColor(sf::Color::Transparent);
	colliderOutline.setOutlineColor(sf::Color::Blue);
	colliderOutline.setOutlineThickness(3.0f);
	colliderOutline.setPosition(
		tileCollider->GetBody()->GetTransform().p.x,
		tileCollider->GetBody()->GetTransform().p.y);
	target.draw(colliderOutline);

	// DRAW SPRITE BEGIN AND END
	auto spriteOutline = sf::RectangleShape(sf::Vector2f(
		tileSprite.getGlobalBounds().width,
		tileSprite.getGlobalBounds().height)
	);
	spriteOutline.setFillColor(sf::Color::Transparent);
	spriteOutline.setOutlineColor(sf::Color::Red);
	spriteOutline.setOutlineThickness(1.0f);
	spriteOutline.setPosition(
		tileSprite.getPosition().x,
		tileSprite.getPosition().y);
	target.draw(spriteOutline);
	// DEBUG END

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

void Tile::PrintSpriteColliderTilePosition()
{
	this->tileCollider->PrintSpriteColliderPosition(this->tileSprite, STATIC);
}

sf::Vector2f Tile::GetBackGroundScale()
{
	return this->spriteBackgroundScale;
}



