#include "stdafx.h"

#include "Tile.h"



namespace ratchet
{
	Tile::Tile()
	{
		//m_userData = new UserData();
		//m_userData->type = TILE;

	}

	Tile::~Tile()
	{
		destroyCollider();
		//delete m_userData;
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
			TRACE_CHANNEL("RESOURCE_MANAGER", "ERROR::PLAYER COULD NOT LOAD THE TEXTURE SHEET");
		}
	}

	void Tile::initSprite()
	{
		m_tileSprite.setTexture(m_textureSheet);
		//tileSprite.setScale(tileScale);
	}

	void Tile::initPhysics()
	{
		//m_collider = new RectAngleCollider(m_tileSprite, STATIC, TILE);
		b2Vec2 tileBodyPosition = m_collider->getBody()->GetPosition();
		m_collider->setColliderPosition(m_tileSprite.getPosition().x, m_tileSprite.getPosition().y);
		//tileBodyPosition = m_collider->getBody()->GetPosition();
	}

	void Tile::init()
	{
		initTextures();
		initSprite();
	}

	void Tile::update()
	{
		TRACE_CHANNEL("RESOURCE_MANAGER", "Ground Sprite ", m_tileSprite.getPosition().x, " , ", m_tileSprite.getPosition().y);
		TRACE_CHANNEL("RESOURCE_MANAGER", "Ground Collider ", m_collider->getBody()->GetPosition().x, " , ", m_collider->getBody()->GetPosition().y);
	}

	void Tile::render(sf::RenderTarget& target)
	{
#ifdef IS_RATCHET_DEBUG
		m_collider->debugRender(target);
#endif

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

#ifdef IS_RATCHET_DEBUG
	void Tile::printSpriteColliderTilePosition()
	{
		m_collider->printSpriteColliderPosition(m_tileSprite, STATIC);
	}
#endif

	sf::Vector2f Tile::getBackGroundScale()
	{
		return m_spriteBackgroundScale;
	}
}