#include "stdafx.h"
#include "ContactListener.h"
#include "GameObject.h"


namespace ratchet
{
	void ratchet::ContactListener::BeginContact(b2Contact* contact)
    	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		b2Body* bodyA = fixtureA->GetBody();
		b2Body* bodyB = fixtureB->GetBody();

		if (auto* gameObjectA = GameObject::findGameObjectByBody(bodyA))
		{
			if (auto* gameObjectB = GameObject::findGameObjectByBody(bodyB))
			{
				if (fixtureA->IsSensor() != fixtureB->IsSensor())
				{
					if (gameObjectB)
					{

						gameObjectA->OnSensorEnter(gameObjectB);
					}
					else if (gameObjectA)
					{
						gameObjectB->OnSensorEnter(gameObjectA);

					}
				}
				else if (fixtureA->IsSensor() == false && fixtureB->IsSensor() == false)
				{
					gameObjectA->OnCollisionEnter(gameObjectB);
					gameObjectB->OnCollisionEnter(gameObjectA);
				}
			}
		}
	}

	void ratchet::ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		b2Body* bodyA = fixtureA->GetBody();
		b2Body* bodyB = fixtureB->GetBody();

		if (auto* gameObjectA = GameObject::findGameObjectByBody(bodyA))
		{
			if (auto* gameObjectB = GameObject::findGameObjectByBody(bodyB))
			{
				if (fixtureA->IsSensor() != fixtureB->IsSensor())
				{
					gameObjectA->OnSensorExit(gameObjectB);
					gameObjectB->OnSensorExit(gameObjectA);
				}
				else if (fixtureA->IsSensor() == false && fixtureB->IsSensor() == false)
				{
					gameObjectA->OnCollisionExit(gameObjectB);
					gameObjectB->OnCollisionExit(gameObjectA);
				}
			}
		}
	}

}

