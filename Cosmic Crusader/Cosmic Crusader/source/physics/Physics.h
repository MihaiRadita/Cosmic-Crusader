#pragma once

namespace ratchet
{
	enum BodyType {
		DYNAMIC = 0,
		STATIC
	};

	class Physics
	{
	private:

	public:
		Physics();
		~Physics();

		//Getters
		b2World* getPhysicsWorld();

		//Simulation Physics
		void simulatePhysics();

		//Update Function
		void update();

	protected:
		static b2World* s_physicsWorld;
		float m_timeStep;
		int32 m_velocityIterations;
		int32 m_positionIterations;
		static const float sc_metersScale;

	};
}
