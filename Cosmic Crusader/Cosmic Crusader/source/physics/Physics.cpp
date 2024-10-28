#include "stdafx.h"
#include "Physics.h"

#include "GameObject.h"

namespace ratchet
{
	const double Physics::sc_fixedDeltaTime = 1.0 / 60.0;
	Physics::Physics()
	{
		if (!s_physicsWorld)
		{
			s_physicsWorld = new b2World(b2Vec2(0.0f, 9.81f));
		}
		m_timeStep = 1.0f / 60.0f;
		m_velocityIterations = 6;
		m_positionIterations  = 2;
		m_accumulator = 0.f;
	}

	Physics::~Physics()
	{
		s_physicsWorld = nullptr;
		delete s_physicsWorld;
#ifdef IS_RATCHET_DEBUG
		//std::cout << "Delete the physics world" << std::endl;
		//if (!s_physicsWorld)
		//{
		//	std::cout << "Physics World no longer exists!" << std::endl;
		//}
#endif
	}

	b2World* Physics::getPhysicsWorld()
	{
		return s_physicsWorld;
	}

	void Physics::simulatePhysics(float& deltaTime)
	{
		s_physicsWorld->Step(m_timeStep, m_velocityIterations, m_positionIterations);
	}

	void Physics::update(float& deltatime)
	{
		simulatePhysics(deltatime);
	}

	b2World* Physics::s_physicsWorld = nullptr;
	const float Physics::sc_metersScale = 20.f;
}