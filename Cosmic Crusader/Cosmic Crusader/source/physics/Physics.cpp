#include "stdafx.h"
#include "Physics.h"

namespace ratchet
{
	const double Physics::sc_fixedDeltaTime = 1.0 / 60.0;
	Physics::Physics()
	{
		if (!Physics::s_physicsWorld)
		{
			Physics::s_physicsWorld = new b2World(b2Vec2(0.0f, 1000.5f));
		}
		m_timeStep = 1.0f / 190;
		m_velocityIterations = 6;
		m_positionIterations = 2;
		m_accumulator = 0.f;
		int32_t subSteps = 10;
	}

	Physics::~Physics()
	{
		s_physicsWorld = nullptr;
		delete s_physicsWorld;
#ifdef IS_RATCHET_DEBUG
		std::cout << "Delete the physics world" << std::endl;
		if (!s_physicsWorld)
		{
			std::cout << "Physics World no longer exists!" << std::endl;
		}
#endif
	}

	b2World* Physics::getPhysicsWorld()
	{
		return s_physicsWorld;
	}

	void Physics::simulatePhysics(float& deltaTime)
	{
		/*for (int i = 0; i < 60; ++i)
		{
			s_physicsWorld->Step(m_timeStep, m_velocityIterations, m_positionIterations);

		}*/

		if (deltaTime > sc_fixedDeltaTime) {
			deltaTime = sc_fixedDeltaTime;
		}

		m_accumulator += deltaTime;

		while (m_accumulator >= m_timeStep)
		{
			s_physicsWorld->Step(m_timeStep, m_velocityIterations, m_positionIterations);
			m_accumulator -= m_timeStep;
		}

		if (m_accumulator < 0.f)
		{
			m_accumulator = 0.f;
		}
	}

	void Physics::update(float& deltatime)
	{
		simulatePhysics(deltatime);
	}

	b2World* Physics::s_physicsWorld = nullptr;
	const float Physics::sc_metersScale = 20.f;
}