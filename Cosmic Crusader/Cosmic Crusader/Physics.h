#pragma once
class Physics
{
private:

public:
	Physics();
	~Physics();

	//Getters
	b2World* GetPhysicsWorld();

	//Simulation Function
	void SimulatePhysics();

protected:
	static b2World* physicsWorld;
	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	static const float metersScale;

};

