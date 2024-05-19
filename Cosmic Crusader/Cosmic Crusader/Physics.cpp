#include "stdafx.h"
#include "Physics.h"

Physics::Physics()
{
	if (!Physics::s_physicsWorld)
	{
		Physics::s_physicsWorld = new b2World(b2Vec2(0.96f, 0.0f));
	}
	this->m_timeStep = 1.0f / 80.0f;
	this->m_velocityIterations = 6;
	this->m_positionIterations = 2;
}

Physics::~Physics()
{
	this->s_physicsWorld = nullptr;
	delete this->s_physicsWorld;
	std::cout << "Delete the physics world" << std::endl;
	if (!this->s_physicsWorld)
	{
		std::cout << "Physics World no longer exists!" << std::endl;
	}
}

b2World* Physics::getPhysicsWorld()
{
	return this->s_physicsWorld;
}

void Physics::simulatePhysics()
{
	for (int i = 0; i < 60; ++i)
	{
		this->s_physicsWorld->Step(this->m_timeStep, this->m_velocityIterations, this->m_positionIterations);
	}
}

void Physics::update()
{
	this->simulatePhysics();
}

b2World* Physics::s_physicsWorld = nullptr;
const float Physics::sc_metersScale = 20.f;
