#pragma once

#include "Physics.h"


class RectAngleCollider : public Physics
{
private:

	//Physics
	b2PolygonShape boxShape;
	b2FixtureDef fixtureDef;
	b2BodyDef bodyDef;
	b2Body* body = nullptr;
	b2Vec2 colliderOrigin;
	int bodyTypeState;

public:
	//Constructors
	RectAngleCollider(sf::Sprite& sprite, int bodyTypeState);
	void InitVariables(sf::Sprite& sprite, int bodyTypeState);

	//Destructors
	~RectAngleCollider();

	//Getters
	b2BodyDef GetBodyDef();
	b2Body* GetBody();
	b2PolygonShape GetColliderShape();
	b2FixtureDef GetFixtureDef();
	
	//Setters
	void SetColliderPosition(sf::Sprite& sprite);

	//Checks
	
};

