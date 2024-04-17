#pragma once
class Physics
{
private:

public:
	Physics();
	~Physics();

	//Getters
	b2World* GetPhysicsWorld();

protected:
	static b2World* physicsWorld;
};

