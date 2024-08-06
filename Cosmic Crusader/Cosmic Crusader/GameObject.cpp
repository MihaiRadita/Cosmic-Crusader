#include "stdafx.h"
#include "GameObject.h"

ratchet::GameObject::GameObject(const GameObjectConfig& config)
{
	//States
	m_faction = config.m_Faction;
	m_colliderType = config.m_colliderType;
	m_colliderShapeType = config.m_colliderShapeType;


	//Transforms
	m_spawnPosition = config.spawnPosition;
	m_spawnRotation = config.spawnRotation;
	m_spawnScale = config.spawnScale;


	//Graphics
	m_spritePath = config.spritePath;
	m_sprite = config.objSprite;
	m_spriteTexture = config.spriteTexture;

	//Physics
	m_colliderScaleMultipier = config.colliderScaleMultiplier;

	if (config.m_colliderShapeType == ColliderShapeType::RECTANGLE)
	{
		m_collider = new ratchet::RectAngleCollider(m_sprite, m_colliderType, m_faction);
	}

	m_sprite.setPosition(sf::Vector2f(config.spawnPosition.x, config.spawnPosition.y));
	m_sprite.setRotation(config.spawnRotation);

}

ratchet::GameObject::~GameObject()
{
}

void ratchet::GameObject::init()
{
	initGraphics();
	initPhyics();
}

void ratchet::GameObject::initGraphics()
{
}

void ratchet::GameObject::initPhyics()
{
}

void ratchet::GameObject::update()
{
}

void ratchet::GameObject::destroy()
{
}

void ratchet::GameObject::updateInput()
{
	
}

void ratchet::GameObject::Ipput::resetMovement()
{
	x = 0;
	y = 0;
}

void ratchet::GameObject::Ipput::resetJump()
{
	isJump = false;
}
