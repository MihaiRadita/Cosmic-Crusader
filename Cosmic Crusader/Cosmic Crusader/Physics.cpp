#include "stdafx.h"
#include "Physics.h"

Physics::Physics()
{
	if (!Physics::physicsWorld)
	{
		Physics::physicsWorld = new b2World(b2Vec2(0.0f, 9.8f));
	}
	this->timeStep = 1.f / 60.f;
	this->velocityIterations = 6;
	this->positionIterations = 2;
}

Physics::~Physics()
{
	this->physicsWorld = nullptr;
	delete this->physicsWorld;
	std::cout << "Delete the physics world" << std::endl;
	if (!this->physicsWorld)
	{
		std::cout << "Physics World no longer exists!" << std::endl;
	}
}

b2World* Physics::GetPhysicsWorld()
{
	return this->physicsWorld;
}

void Physics::SimulatePhysics()
{
	for (int i = 0; i < 60; ++i)
	{
		this->physicsWorld->Step(this->timeStep, this->velocityIterations, this->positionIterations);
	}
}

void Physics::update()
{
	this->SimulatePhysics();
}

b2World* Physics::physicsWorld = nullptr;
const float Physics::metersScale = 30.f;
