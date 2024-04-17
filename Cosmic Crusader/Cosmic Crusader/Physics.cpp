#include "stdafx.h"
#include "Physics.h"

Physics::Physics()
{
	if (!Physics::physicsWorld)
	{
		Physics::physicsWorld = new b2World(b2Vec2(0.0f, 9.8f));
	}
}

Physics::~Physics()
{
	delete this->physicsWorld;
}

b2World* Physics::GetPhysicsWorld()
{
	return this->physicsWorld;
}

b2World* Physics::physicsWorld = nullptr;