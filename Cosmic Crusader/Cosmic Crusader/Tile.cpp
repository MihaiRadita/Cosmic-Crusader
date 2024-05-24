#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	m_userData = new UserData();
	m_userData->type = TILE;

}

Tile::~Tile()
{
	destroyCollider();
	delete m_userData;
}

void Tile::destroyCollider()
{
	m_collider = nullptr;
	delete m_collider;
}

void Tile::initVariables()
{
	m_tileScale = sf::Vector2f(1.f, 1.f);

}

void Tile::initTextures()
{
	if (m_textureSheet.loadFromFile("Textures/Levels/Level1/Tileset/Platform.png") == false)
	{
		std::cout << "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET" << std::endl;
	}
}

void Tile::initSprite()
{
	m_tileSprite.setTexture(m_textureSheet);
	//tileSprite.setScale(tileScale);
}

void Tile::initPhysics()
{
	m_collider = new RectAngleCollider(m_tileSprite, STATIC);
	m_collider->setColliderPosition(m_tileSprite.getPosition().x, m_tileSprite.getPosition().y);
}

void Tile::init()
{
	initTextures();
	initSprite();
}

void Tile::update()
{
	std::cout << "Ground Sprite " << m_tileSprite.getPosition().x << " , " << m_tileSprite.getPosition().y << std::endl;
	std::cout << "Ground Collider " << m_collider->getBody()->GetPosition().x << " , "<< m_collider->getBody()->GetPosition().y <<std::endl;
}

void Tile::render(sf::RenderTarget& target)
{
	// DEBUG START
	m_collider->debugRender(target);

	// DRAW SPRITE BEGIN AND END
	auto spriteOutline = sf::RectangleShape(sf::Vector2f(
		m_tileSprite.getGlobalBounds().width,
		m_tileSprite.getGlobalBounds().height)
	);
	spriteOutline.setFillColor(sf::Color::Transparent);
	spriteOutline.setOutlineColor(sf::Color::Red);
	spriteOutline.setOutlineThickness(1.0f);
	spriteOutline.setPosition(
		m_tileSprite.getPosition().x,
		m_tileSprite.getPosition().y);
	target.draw(spriteOutline);
	// DEBUG END

	target.draw(m_tileSprite);
}

sf::Sprite Tile::getTileSprite()
{
	return m_tileSprite;
}

RectAngleCollider* Tile::getTileCollider()
{
	return m_collider;
}

void Tile::setPosition(float x, float y)
{
	m_tileSprite.setPosition(x, y);
}

void Tile::setScale(float x, float y)
{
	m_tileSprite.setScale(x, y);
}

void Tile::printSpriteColliderTilePosition()
{
	m_collider->printSpriteColliderPosition(m_tileSprite, STATIC);
}

sf::Vector2f Tile::getBackGroundScale()
{
	return m_spriteBackgroundScale;
}



