#pragma once

namespace ratchet
{
	class ContactListener; 
	//class b2World;

	enum BodyType {
		//DYNAMIC = 0,
		//STATIC
	};

	class GameObject;

	class Physics
	{
	private:

	public:
		Physics();
		~Physics();
		bool isSimulatingPhysics = false;

		//Getters
		static b2World* getPhysicsWorld();

		static void DestroyPhysicsInstance();

		//Simulation Physics
		static void simulatePhysics(float& deltaTime);

		static void SetSimulationEnabled(bool enabled);

		static bool IsSimulationEnabled();

		//Update Function
		static void update(float& deltaTime);

		//bool shouldSkipRaycastThisFrame(); 

		bool m_skipRaycastThisFrame = false;
		static bool s_simulationEnabled;
	protected:
		static b2World* s_physicsWorld;
		static ContactListener* s_contactListener;

		static const float sc_timeStep;
		static const int32 sc_velocityIterations;
		static const int32 sc_positionIterations;
		static const float sc_metersScale;


		double m_accumulator;  // Acumulator pentru timpul scurs dintre pa?ii de simulare

		static const double sc_fixedDeltaTime;
	};
}
