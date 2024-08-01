#include "stdafx.h"
#include "Creature.h"

ratchet::Creature::Creature(CreatureConfig& config) : GameObject(config)
{
	//Character States
	m_faction = GameObject::m_faction;
	m_colliderType = GameObject::m_colliderType;
	m_colliderShapeType = GameObject::m_colliderShapeType;
	//Character Transforms
	m_spawnposition = config.spawnPosition;
	m_spawnRotation = config.spawnRotation;
	m_spawnScale = config.spawnScale;

	//Character Features
	m_movementSpeed = config.m_movingSpeed;
	m_fallingSpeed = config.m_fallingSpeed;
	m_jumpingSpeed = config.m_jumpingSpeed;
}

ratchet::Creature::~Creature()
{

}

void ratchet::Creature::updateInput()
{
}
