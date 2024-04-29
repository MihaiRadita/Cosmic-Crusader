#pragma once

enum BodyType{DYNAMIC =0, STATIC};
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

	//Update Function
	void update();

protected:
	static b2World* physicsWorld;
	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	static const float metersScale;

};

