#include "stdafx.h"
#include "Physics.h"

#include "GameObject.h"

#include "ContactListener.h"

#include "ColliderBase.h"


namespace ratchet
{
	const double Physics::sc_fixedDeltaTime = 1.0 / 60.0;
	const float Physics::sc_timeStep = 1.0f / 60.0f;
	const int32 Physics::sc_velocityIterations = 6;
	const int32 Physics::sc_positionIterations  = 2;


	Physics::~Physics()
	{
		TRACE_CHANNEL("PHYSICS", "Delete the physics world");
		if (!s_physicsWorld)
		{
			TRACE_CHANNEL("PHYSICS", "Physics World no longer exists!");
		}
	}

	b2World* Physics::getPhysicsWorld()
	{
		return s_physicsWorld;
	}

	void Physics::DestroyPhysicsInstance()
	{
		delete s_contactListener;
		s_contactListener = nullptr;

		delete s_physicsWorld;
		s_physicsWorld = nullptr;
	}

	void Physics::simulatePhysics(float deltaTime)
	{
		if (!s_physicsWorld || !s_simulationEnabled)
			return;

		m_accumulator += deltaTime;

		while (m_accumulator >= sc_timeStep)
		{
			s_physicsWorld->Step(sc_timeStep, sc_velocityIterations, sc_positionIterations);
			m_accumulator -= sc_timeStep;
		}
	}

	void Physics::SetSimulationEnabled(bool enabled)
	{
		s_simulationEnabled = enabled;
	}

	bool Physics::IsSimulationEnabled()
	{
		return s_simulationEnabled;
	}

	void Physics::initPhysics()
	{
		if (!s_physicsWorld)
		{
			s_physicsWorld = new b2World(b2Vec2(0.0f, 9.81f));
		}
		m_accumulator = 0.f;

		if (!s_contactListener)
		{
			s_contactListener = new ContactListener();

		}

		if (!m_contactFilter)
		{
			m_contactFilter = new ContactFilter();
		}
		s_physicsWorld->SetContactListener(s_contactListener);

		s_physicsWorld->SetContactFilter(m_contactFilter);
	}


	void Physics::update(float deltatime)
	{
		simulatePhysics(deltatime);
	}

	b2World* Physics::s_physicsWorld = nullptr;
	const float Physics::sc_metersScale = 20.f;


	ContactListener* Physics::s_contactListener;
	ContactFilter* Physics::m_contactFilter;
	bool Physics::s_simulationEnabled = false;
	float Physics::m_accumulator = 0.0f;
}