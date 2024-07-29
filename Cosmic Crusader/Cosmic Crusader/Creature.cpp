#include "stdafx.h"
#include "Creature.h"

ratchet::Creature::Creature(CreatureConfig& config) : GameObject(config)
{
	m_faction = config.m_Faction;
	m_movementType = config.m_movementType;
	m_colliderType = config.m_colliderType;
	m_colliderShapeType = config.m_colliderShapeType;

	m_spawnposition = config.spawnPosition;
	m_spawnRotation = config.spawnRotation;
	m_spawnScale = config.spawnScale;

	m_movementSpeed = config.m_movingSpeed;
	m_fallingSpeed = config.m_fallingSpeed;
	m_jumpingSpeed = config.m_jumpingSpeed;
}

ratchet::Creature::~Creature()
{

}
